
#include "gd32f30x.h"
#include <stdio.h>

#include "systick.h"
#include "gpio.h"


int main(void)
{			
	systick_config();
	
	gpio_config();
			
	uint32_t tick1,tick2;	
	tick1 = tick2 = get_tick();
	
	while(1)
	{
		
		if(get_tick() > tick1)
		{
			tick1 = get_tick() + 100 / SysTick_Tick;				
			/* toggle LED */
			gpio_bit_write(LED_PB2_PORT,LED_PB2_PIN,(gpio_output_bit_get(LED_PB2_PORT,LED_PB2_PIN)) == SET?RESET:SET);
		}
		
	}
	
}

