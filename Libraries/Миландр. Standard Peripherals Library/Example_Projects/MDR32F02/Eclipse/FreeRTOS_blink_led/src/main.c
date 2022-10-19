#include <MLDR187_gpio.h>
#include <MLDR187_lib.h>

#include <FreeRTOS.h>
#include <queue.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <init.h>

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

void blink_task(void* arg) {
	(void)arg;
    while (true) {
        vTaskDelay(1000);
        PORT_SetReset(LED_PORT, LED_PIN_0, !PORT_ReadPin(LED_PORT, LED_PIN_0));
    }
}

void blink_task2(void* arg) {
	(void)arg;
    while (true) {
        vTaskDelay(1500);
        PORT_SetReset(LED_PORT, LED_PIN_1, !PORT_ReadPin(LED_PORT, LED_PIN_1));
    }
}

int main() {
    init_clock();
    init_uart();
    init_bkp();
    init_leds();

    xQueue = xQueueCreate( 2, sizeof( uint32_t ) );

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
        file. */
        xTaskCreate( blink_task,				/* The function that implements the task. */
                     "blink1", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
                     configMINIMAL_STACK_SIZE * 2U, 			/* The size of the stack to allocate to the task. */
                     NULL, 								/* The parameter passed to the task - not used in this case. */
                     ( tskIDLE_PRIORITY + 2 ), 	/* The priority assigned to the task. */
                     NULL );								/* The task handle is not required, so NULL is passed. */

        xTaskCreate( blink_task2,				/* The function that implements the task. */
                     "blink2", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
                     configMINIMAL_STACK_SIZE * 2U, 			/* The size of the stack to allocate to the task. */
                     NULL, 								/* The parameter passed to the task - not used in this case. */
                     ( tskIDLE_PRIORITY + 2 ), 	/* The priority assigned to the task. */
                     NULL );

        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    return 0;
}

