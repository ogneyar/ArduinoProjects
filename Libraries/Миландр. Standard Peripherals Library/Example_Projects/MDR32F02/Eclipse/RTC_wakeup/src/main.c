#include <stdio.h>

#include <MLDR187_bkp.h>
#include <MLDR187_it.h>
#include <MLDR187_gpio.h>

#include <init.h>
#include <stdbool.h>

#define LSE_SPEED 32768

void BACKUP_IRQHandler() {
    bool from_battery = BKP_GetSWPinState();

    if ((BKP_GetTamperEventState() & (bkpTamperWakeup1 | bkpTamperWakeup2 | bkpTamperWakeup3)) != 0) {
        // Cover detection triggered

        // Do some stuff ... e.g. log covdet event
        set_led(0, RESET);
        for (int j = 0; j < 6; j ++) {
            toggle_led(1);
            for (int i = 0; i < 0x100000; i++);
        }

        // Clear flags
        BKP_SetTamperNewState(DISABLE);
        BKP_SetCovDetectionFlag(SET);
        BKP_SetTamperNewState(ENABLE);

        // If was woken up from battery, power off
        if (from_battery) {
            BKP_SwitchOffAlarmPower();
        }
    }
}


int main()
{
    RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
    bool from_battery = BKP_GetSWPinState();

    if (!from_battery) {
        init_clock();
        init_bkp();
        init_uart();
    } else {
        BKP_LSE_Speed = LSE_SPEED;
    }
    init_leds();
    init_interrupts();

    // Main loop
    for (;;) {
        for (int i = 0; i < 0x100000; i++);
        toggle_led(0);
    }
}


