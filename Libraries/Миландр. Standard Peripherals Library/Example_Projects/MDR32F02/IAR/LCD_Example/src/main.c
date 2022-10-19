/**
  ******************************************************************************
  * @file    LCD_Example/src/main.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    22/11/2020
  * @brief   Main program body.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Includes ------------------------------------------------------------------*/
#include <intrinsics.h>
#include <stdio.h>
#include <LowLevelIOInterface.h>
#include "csr.h"
#include "MLDR187_lib.h"
#include "MLDR187.h"
#include "MLDR187_gpio.h"
#include "MLDR187_rst_clk.h"
#include "MLDR187_eeprom.h"
#include "MLDR187_bkp.h"
#include "MLDR187_uart.h"

#include "interrupt.h"
#include "lcd.h"
#include "text.h"
#include "Logo.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define	LED_PORT 	MDR_PORTD
#define	LED_PORT_CLK 	RST_CLK_PORTD
#define LED_PIN_0	PORT_Pin_0
#define LED_PIN_1	PORT_Pin_1
#define LED_PIN_2	PORT_Pin_2
#define LED_PIN_3	PORT_Pin_3

#define	KEY_PORT 	MDR_PORTA
#define	KEY_PORT_CLK 	RST_CLK_PORTA
#define KEY_PIN_0	PORT_Pin_0
#define KEY_PIN_1	PORT_Pin_1
#define KEY_PIN_2	PORT_Pin_2
#define KEY_PIN_3	PORT_Pin_3

#define UART_MODULE     MDR_UART1
#define UART_PORT       MDR_PORTB
#define UART_PORT_CLK   RST_CLK_PORTA
#define UART_TX_PIN     PORT_Pin_0
#define UART_RX_PIN     PORT_Pin_1
            
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef        PORT_InitStructure;
UART_InitTypeDef        UART_InitStructure;
RST_CLK_CpuSpeed_InitTypeDef    RST_CLK_CpuSpeed_InitStructure;

uint32_t DelayCnt = 0;
uint8_t TickTock = 0;
         
/* Private function prototypes -----------------------------------------------*/
void Setup_LED_Port(void);
void Setup_CPU_Clock(void);
void Setup_UART(void);
void Setup_Interrupts(void);
void Setup_Key(void);

/* Private functions ---------------------------------------------------------*/

/* --- */
void SysTick_Handler(void)
{
    // Set up time for next interrupt 
    MDR_CLIC_MTIMECMP_Reg = MDR_CLIC_MTIME_Reg + 32768;
    
    if (TickTock)
    {
        TickTock = 0;
    }
    else
    {
        TickTock = 1;
    }
    
}

/* Main Function */
int main()
{

    Setup_CPU_Clock();
    Setup_Interrupts();
    Setup_LED_Port();
    Setup_Key();
    Setup_UART();
           
    LCD_INIT();
    LCD_CLS();
    LCD_CurrentMethod = MET_AND;
    LCD_PUT_PICT(8, 0, 112, 32, Logotip);
    LCD_PUTS(54, 28, "K1986BK025");
    LCD_PUTS(54, 38, "MDR32F02FI");
    LCD_PUTC(24, 44, 0x04); // •
       
    printf(" K1986BK025 Init end!\n");
    
    while (1)
    {
        LCD_CurrentMethod = MET_AND;
        
        /* Key down*/
        if (PORT_ReadPin(KEY_PORT, KEY_PIN_0)) 
            LCD_PUTC(24, 52, 0);
        else
            LCD_PUTC(24, 52, 0x19);
        
        /* Key left*/
        if (PORT_ReadPin(KEY_PORT, KEY_PIN_1)) 
            LCD_PUTC(16, 44, 0);
        else
            LCD_PUTC(16, 44, 0x1B);
        
        /* Key right*/
        if (PORT_ReadPin(KEY_PORT, KEY_PIN_2)) 
            LCD_PUTC(32, 44, 0);
        else
            LCD_PUTC(32, 44, 0x1A);
        
        /* Key up*/
        if (PORT_ReadPin(KEY_PORT, KEY_PIN_3)) 
            LCD_PUTC(24, 37, 0);
        else
            LCD_PUTC(24, 37, 0x18);

        /* 1 second */
        if (TickTock) 
        {
            LCD_PUTC(80, 52, 0x5C);
            PORT_SetReset(LED_PORT, LED_PIN_3, RESET);
        }
        else
        {
            LCD_PUTC(80, 52, 0x2F);       
            PORT_SetReset(LED_PORT, LED_PIN_3, SET);
        }
        
        /* Program delay */
        if (DelayCnt++ >= 0x00000100)
        {
            DelayCnt = 0;
            if (PORT_ReadPin(LED_PORT, LED_PIN_0) != 0)
                PORT_SetReset(LED_PORT, LED_PIN_0, RESET);
            else
                PORT_SetReset(LED_PORT, LED_PIN_0, SET);           
        }

    }
}

/* --- */
void Setup_Interrupts(void)
{
    /* Global interrupt-enable */
    __enable_machine_interrupt();
    /* Set up  to point to the interrupt function */
    __write_csr(_CSR_MTVEC, (((unsigned int) IRQHandler) & 0xFFFFFFFC ));

    /* Disable SysTick interrupt */
    disable_SysTick_Handler();
    /* Safely set up SysTick cmp value */
    MDR_CLIC_MSIP_Reg = 0;
    MDR_CLIC_MTIMECMP_Reg = MDR_CLIC_MTIMECMP_Reg + 32768;
    /* Enable SysTick interrupt */
    enable_SysTick_Handler();
    RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
    MDR_BKP->WPR = 0x8555AAA1;
    MDR_BKP->CLK |= 0x00000003;
    
}

/* Frequencies setup */
void Setup_CPU_Clock(void)
{
    MDR_RST_CLK->CPU_CLOCK &= RST_CLK_CPU_CLOCK_HCLKSEL_Msk;    // HCLK = HSI
    
    RST_CLK_EnablePeripheralClock(RST_CLK_EEPROM, RST_CLK_Div1);
    EEPROM_SetLatency(flashCoreSpeedUpTo60MHz);
    
    RST_CLK_CpuSpeed_InitStructure.hseState = RST_CLK_HseOscillator;
    RST_CLK_CpuSpeed_InitStructure.hseSpeed = 8000000;
    RST_CLK_CpuSpeed_InitStructure.cpuC1Src = RST_CLK_CpuC1SelHse;
    RST_CLK_CpuSpeed_InitStructure.pllState = RST_CLK_PllFromHse;
    RST_CLK_CpuSpeed_InitStructure.pllMult = 6;
    RST_CLK_CpuSpeed_InitStructure.cpuC2Src = RST_CLK_CpuC2SelPllCpu;
    RST_CLK_CpuSpeed_InitStructure.cpuC3Div = RST_CLK_Div1;
    RST_CLK_CpuSpeed_InitStructure.hclkSrc = RST_CLK_HclkSelCpuC3;
    RST_CLK_SetupCpuSpeed(&RST_CLK_CpuSpeed_InitStructure);
    RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_PER1_C2, RST_CLK_ClkSrc_PLLCPU);
}

/* --- */
void Setup_UART(void)
{
    RST_CLK_EnablePeripheralClock(UART_PORT_CLK, RST_CLK_Div1);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_MAIN;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST_2mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(UART_PORT, (UART_TX_PIN | UART_RX_PIN), &PORT_InitStructure);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_Init(UART_PORT, (UART_TX_PIN), &PORT_InitStructure);
    
    UART_StructInitDefault(&UART_InitStructure);
    UART_DeInit(UART_MODULE);

    UART_InitStructure.clkDivisor = RST_CLK_Div1;
    UART_InitStructure.baudRate = 115200;
    UART_InitStructure.wordLength = UART_WordLength8b;
    UART_InitStructure.stopBits = UART_StopBits1;
    UART_InitStructure.parity = UART_ParityNone;
    UART_InitStructure.fifoEn = ENABLE;
    UART_Init(UART_MODULE, &UART_InitStructure);
    UART_Cmd(UART_MODULE, ENABLE);
}

/* --- */
void Setup_Key(void)
{
    RST_CLK_EnablePeripheralClock(KEY_PORT_CLK, RST_CLK_Div1);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(KEY_PORT, (KEY_PIN_0 | KEY_PIN_1 | KEY_PIN_2 | KEY_PIN_3), &PORT_InitStructure);   
}

/* --- */
void Setup_LED_Port(void)
{
    RST_CLK_EnablePeripheralClock(LED_PORT_CLK, RST_CLK_Div1);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(LED_PORT, (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3), &PORT_InitStructure);
    PORT_SetReset(LED_PORT, LED_PIN_0, SET);
    PORT_SetReset(LED_PORT, LED_PIN_1, SET);
    PORT_SetReset(LED_PORT, LED_PIN_2, SET);
    PORT_SetReset(LED_PORT, LED_PIN_3, SET);
}

/* retarget the C library printf function to the UART */
size_t __write(int handle, const unsigned char *buf, size_t bufSize)
{
    size_t nChars = 0;

    if (handle == -1)
    {
        return 0;
    }

    for (; bufSize > 0; --bufSize)
    {
        UART_Send(UART_MODULE, (uint8_t) *buf );
        while ( UART_GetFlagStatus(UART_MODULE, UART_FLAG_TXFE)== RESET){}
        ++buf;
        ++nChars;
    }

    return nChars;
}

