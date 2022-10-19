//
// Created by panukov.a on 01.04.2021.
//

#include <MLDR187_iso7816.h>
#include <MLDR187_uart.h>
#include <MLDR187_gpio.h>

#include <init.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define RST_PORT MDR_PORTD
#define RST_PIN pin0

#define CLK_PORT MDR_PORTD
#define CLK_PIN pin12

// NOTE: You will need a pullup resistor on TX pin
#define TX_PORT MDR_PORTD
#define TX_PIN pin10

#define BAUD_RATE 9600
#define CLK_PER_BIT 372

uint32_t PRESCALER;

struct ATR {
    uint8_t TS;
    uint8_t T0;
    struct {uint8_t TAi, TBi, TCi, TDi;} TABCDi[8];
    uint8_t Ti[15];
};


void init();
void waitCycles(uint32_t cycles);
void activate();
void deactivate();
bool readNext(uint8_t * buf);
bool receiveATR(struct ATR * atr);
ssize_t send_msg_recv_resp(uint8_t * cmd, size_t cmd_n, uint8_t * res);


// GET DATA command
uint8_t cmd[] = {
        0x80, 0xCA, 0x9F, 0x7F, 0x2D
};

int main() {
    init();

    struct ATR atr;
    uint8_t buf[256];

    while (true) {
        activate();

        receiveATR(&atr);

        ssize_t res_n = send_msg_recv_resp(cmd, sizeof(cmd), buf);
        for (int i = 0; i < res_n; i++)
            putchar(buf[i]);

        deactivate();

        fflush(stdout);
    }

    return 0;
}


ssize_t send_msg_recv_resp(uint8_t *cmd, size_t cmd_n, uint8_t *res) {
    // Wait until TX buffer is empty
    while (!(ISO7816_GetFlags() & ISO7816_SR_TXE));
    ISO7816_GetLast();

    // Send command
    for (size_t i = 0; i < cmd_n; i++) {
        // Send next char
        ISO7816_PutNext(cmd[i]);
        // As we are in half-duplex mode, we can check for collisions by
        // reading a char from the bus and comparing to the sent one
        uint8_t sent;
        readNext(&sent);
        if (sent != cmd[i])
            return -1;
    }

    // Read response until timeout
    size_t res_n = 0;
    while (readNext(res + res_n++));
    res_n--;

    return res_n;
}

bool receiveATR(struct ATR *atr) {
    // Read TS and T0
    if (!readNext(&atr->TS)) goto error;
    if (!readNext(&atr->T0)) goto error;

    bool hasA = atr->T0 >> 4 & 1;
    bool hasB = atr->T0 >> 5 & 1;
    bool hasC = atr->T0 >> 6 & 1;
    bool hasD = atr->T0 >> 7 & 1;
    int n_Ti = atr->T0 & 0b1111;

    // Read T[A,B,C,D]i
    for (int i = 0; i < 8 && (hasA || hasB || hasC || hasD); i++) {
        atr->TABCDi[i].TDi &= ~0xf;

        if (hasA && !readNext(&atr->TABCDi[i].TAi)) goto error;
        if (hasB && !readNext(&atr->TABCDi[i].TBi)) goto error;
        if (hasC && !readNext(&atr->TABCDi[i].TCi)) goto error;
        if (hasD && !readNext(&atr->TABCDi[i].TDi)) goto error;

        hasA = atr->TABCDi[i].TDi >> 4 & 1;
        hasB = atr->TABCDi[i].TDi >> 5 & 1;
        hasC = atr->TABCDi[i].TDi >> 6 & 1;
        hasD = atr->TABCDi[i].TDi >> 7 & 1;
    }

    // Read historical bytes
    for (int i = 0; i < n_Ti; i++) {
        if(!readNext(&atr->Ti[i])) goto error;
    }

    return true;
    error:
    return false;
}

bool readNext(uint8_t *buf) {
    // Wait until RX buffer is not empty or until timeout occurs
    // Timeout is set in CPU clock cycles

    register uint32_t cycle asm("t0");
    asm("csrr t0, mcycle");
    uint32_t start = cycle;

    // 2 * 40000 of card CLK pulses
    uint32_t cycles = 2 * 40000 * PRESCALER * (RST_CLK_CpuSpeed / RST_CLK_HclkSpeed);

    while (cycle - start < cycles) {
        asm("csrr t0, mcycle");
        // Try to read from RX buffer if any data is available
        if (ISO7816_GetFlags() & ISO7816_SR_RXNE) {
            *buf = ISO7816_GetLast();
            return true;
        }
    }

    return false;
}

void deactivate() {
    PORT_SetReset(RST_PORT, RST_PIN, RESET);
    ISO7816_Cmd(DISABLE);
}

void activate() {
    PORT_SetReset(RST_PORT, RST_PIN, RESET);
    ISO7816_Cmd(ENABLE);

    // 40000 of card CLK pulses
    waitCycles(40000 * PRESCALER * (RST_CLK_CpuSpeed / RST_CLK_HclkSpeed));

    PORT_SetReset(RST_PORT, RST_PIN, SET);
}

void waitCycles(uint32_t cycles) {
    // Wait for timeout
    // Timeout is set in CPU clock cycles
    register uint32_t cycle asm("t0");
    asm("csrr t0, mcycle");
    uint32_t start = cycle;
    while (cycle - start < cycles)
            asm("csrr t0, mcycle");
}

void init() {
    init_clock();
    init_uart();

    // Init GPIO: CLK, I/O
    PORT_InitTypeDef portInit;
    portInit.PORT_OE = PORT_OE_OUT;
    portInit.PORT_FUNC = PORT_FUNC_MAIN;
    portInit.PORT_MODE = PORT_MODE_DIGITAL;
    portInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    portInit.PORT_SPEED = PORT_SPEED_FAST_2mA;
    PORT_Init(CLK_PORT, CLK_PIN, &portInit);
    PORT_Init(TX_PORT, TX_PIN, &portInit);

    // Init GPIO: RST
    portInit.PORT_FUNC = PORT_FUNC_PORT;
    PORT_SetReset(RST_PORT, RST_PIN, RESET);
    PORT_Init(RST_PORT, RST_PIN, &portInit);

    // Calculate prescaler to get card CLK from HCLK
    // Card CLK = HCLK / PRESCALER, and it must be from 1 to 5 MHz
    PRESCALER = round((float)RST_CLK_HclkSpeed / (CLK_PER_BIT * BAUD_RATE));
    uint32_t baud_rate_real = RST_CLK_HclkSpeed / PRESCALER / CLK_PER_BIT;

    // Init ISO7816 USART in Smartcard mode
    ISO7816_InitTypeDef initStruct;
    ISO7816_StructInitDefault(&initStruct);

    initStruct.baudRate = baud_rate_real;
    initStruct.prescaler = PRESCALER;

    initStruct.smartCardMode = ENABLE;
    initStruct.smartCardNack = ENABLE;
    initStruct.clkEn = ENABLE;
    initStruct.halfDuplex = DISABLE;

    initStruct.wl9bit = ENABLE;
    initStruct.parity = iso7816parityEven;
    initStruct.stopCnt = iso7816stop1_5;
    initStruct.guardTime = 1;

    ISO7816_Init(&initStruct);
}

