
#include <stdio.h>
#include "wm_hal.h"

void Error_Handler(void);

int main(void)
{
	SystemClock_Config(CPU_CLK_160M);
	printf("enter main\r\n");
	
	while (1)
	{
		printf(".");
		HAL_Delay(1000);
	}
}

void Error_Handler(void)
{
	while (1)
	{
	}
}

void assert_failed(uint8_t *file, uint32_t line)
{
	printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}