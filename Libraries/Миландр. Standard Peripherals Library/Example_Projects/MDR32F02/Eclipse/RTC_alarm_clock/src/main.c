

/*
 * This example shows how to implement an alarm clock
 * Every second it prints current time to UART
 * At startup it sets an alarm after 10 seconds
 * When alarm is triggered, you need to press a button to postpone it
 */


#include <stdio.h>

#include <MLDR187_bkp.h>
#include <MLDR187_it.h>
#include <MLDR187_gpio.h>

#include <init.h>
#include <stdbool.h>


struct {MDR_GPIO_TypeDef* port; uint16_t pin; bool state;}
LED_PINS[] = {
        {MDR_PORTD, pin0, false},
        {MDR_PORTD, pin1, false}
};

RTC_DateTime INIT_DATE = {
        .year = 21, .month = 3, .day = 22,
        .hours = 14, .minutes = 13, .seconds = 0
};

#define ALARM_POST_MINUTES 0
#define ALARM_POST_SECONDS 10

#define LSE_FREQUENCY 32768


bool alarm_triggered = false;

void setAlarm(uint32_t minutes_after, uint32_t seconds_after);
void toggle_led(int i);
void set_led(int i, BitStatus state);
void init_leds();

void BACKUP_IRQHandler() {
    uint32_t bkp_flags = BKP_GetFlags();

    if (bkp_flags & bkpAlarmAFlag) {
        // Alarm triggered

        // Disable alarm. It will be set again when button is pressed
        BKP_SetItNewState(bkpAlarmAIE, DISABLE);
        BKP_SetAlarmNewState(bkpAlarmAEN, DISABLE);

        printf(" !! WAKE UP !! \n");

        alarm_triggered = true;
        set_led(0, RESET);
        set_led(1, SET);
    }

    if ((MDR_BKP->TAFCR & BKP_RTC_TAFCR_TSIE) && ((BKP_GetTamperEventState() & bkpEventWakeup1) != 0)) {
        // Button pressed

        printf("Button pressed\n");

        // Disable button until new tick
        BKP_SetItNewState(bkpTSIE, DISABLE);

        if (alarm_triggered) {
            // Exit "alarm triggered" state (led now blinks green again)
            alarm_triggered = false;
            set_led(0, SET);
            set_led(1, RESET);

            // Set new alarm
            setAlarm(ALARM_POST_MINUTES, ALARM_POST_SECONDS);
        }
    }

    if (bkp_flags & bkpSecCntEnFlag) {
        // Every second tick

        // Reset flags and enable button event
        BKP_SetItNewState(bkpSecondIE | bkpTSIE, ENABLE);

        // Print current time
        RTC_DateTime dateTime;
        BKP_GetDateTimeBCD(&dateTime);
        BKP_ConvertToBINFormat(&dateTime);

        printf("%.2u:%.2u:%.2u %.2u.%.2u.20%.2u",
               dateTime.hours, dateTime.minutes, dateTime.seconds,
               dateTime.day, dateTime.month, dateTime.year
        );

        // Blink led and print alarm message
        if (alarm_triggered) {
            printf(" ... please wake up and press the button ...");
            toggle_led(1);
        } else {
            toggle_led(0);
        }

        printf("\n");

    }
}


void setAlarm(uint32_t minutes_after, uint32_t seconds_after) {
    RTC_DateTime dateTime;
    BKP_GetDateTimeBCD(&dateTime);
    BKP_ConvertToBINFormat(&dateTime);

    dateTime.seconds = dateTime.seconds + seconds_after;
    dateTime.minutes += dateTime.seconds / 60;
    dateTime.seconds %= 60;
    dateTime.minutes = dateTime.minutes + minutes_after;
    dateTime.hours += dateTime.minutes / 60;
    dateTime.minutes %= 60;

    BKP_AlarmInitTypeDef bkpAlarm = {
            .enHours = ENABLE,
            .enWeekDay = DISABLE,
            .enDateEn = DISABLE,
            .enMinutes = ENABLE,
            .enSeconds = ENABLE
    };

    BKP_ConvertToBCDFormat(&dateTime);
    bkpAlarm.minutes = dateTime.minutes;
    bkpAlarm.seconds = dateTime.seconds;
    bkpAlarm.hours = dateTime.hours;
    bkpAlarm.day = dateTime.day;

    BKP_SetAlarm(bkpAlarmAEN, &bkpAlarm);
    BKP_SetAlarmNewState(bkpAlarmAEN, ENABLE);

    // Print alarm time
    BKP_ConvertToBINFormat(&dateTime);
    printf("Alarm set to --> %.2u:%.2u:%.2u\n",
           dateTime.hours, dateTime.minutes, dateTime.seconds
    );
}


void toggle_led(int i) {
    LED_PINS[i].state = !LED_PINS[i].state;
    PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !LED_PINS[i].state);
}


void set_led(int i, BitStatus state) {
    LED_PINS[i].state = state;
    PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !state);
}


void init_leds() {
    for (int i = 0; i < (int)(sizeof(LED_PINS) / sizeof(LED_PINS[0])); i++) {
        PORT_InitTypeDef portInit = {
                .PORT_MODE = PORT_MODE_DIGITAL,
                .PORT_OE = PORT_OE_OUT,
                .PORT_FUNC = PORT_FUNC_PORT,
                .PORT_SPEED = PORT_SPEED_SLOW_4mA,
                .PORT_PULL_DOWN = PORT_PULL_DOWN_OFF
        };

        PORT_Init(LED_PINS[i].port, LED_PINS[i].pin, &portInit);
        PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !LED_PINS[i].state);
    }
}


void init_bkp(RTC_DateTime * dateTime) {
    BKP_InitTypeDef bkpInit;
    BKP_StructInitDefault(&bkpInit);

    // Enable peripheral clock to BKP
    RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
    BKP_FreqGenCmd(bkpLse, ENABLE, ENABLE);
    bkpInit.RTCsrc = bkpRtc_LSE;

    // As BKP is not reset on main core reset, we need to clear and disable all
    // BKP related interrupts that occurred before to avoid undefined behaviour
    BKP_SetItNewState(bkpAlarmBIE | bkpAlarmAIE | bkpWutfIE | bkpSecondIE | bkpOwerflowIE | bkpTSIE | bkpTAMPIE, DISABLE);
    PLIC_SetMinPermPriority(0);
    PLIC_SetPriority(BACKUP_IRQn, 1);
    PLIC_DisableIRQ(BACKUP_IRQn);
    PLIC_ReleaseIRQ(BACKUP_IRQn);
    enable_irq_extm();

    uint32_t prescaler = LSE_FREQUENCY;

    // RTC time can only be changed when RTC is disabled
    bkpInit.RTCenable = DISABLE;
    BKP_Init(&bkpInit);

    // Set date and time
    BKP_ConvertToBCDFormat(dateTime);
    BKP_SetDateTimeBCD(dateTime, SET, SET);

    // In this example we use WAKEUP1 as a button.
    // Here we initialize it
    BKP_TampEventInitTypeDef tampInit;
    tampInit.enable = ENABLE;
    tampInit.interrupt = ENABLE;
    tampInit.wakeup1 = BKP_FALLING_LOW;
    BKP_InitExternalEvent(&tampInit);

    // Run the clock
    bkpInit.RTCenable = ENABLE;
    bkpInit.RTCprediv = prescaler;
    BKP_Init(&bkpInit);

    // Enable interrupts
    BKP_SetItNewState(bkpSecondIE | bkpAlarmAIE | bkpTSIE, ENABLE);
    PLIC_EnableIRQ(BACKUP_IRQn);
}


int main()
{
    init_clock();
    init_uart();
    init_leds();
    init_bkp(&INIT_DATE);

    setAlarm(ALARM_POST_MINUTES, ALARM_POST_SECONDS);

    for (;;);
}


