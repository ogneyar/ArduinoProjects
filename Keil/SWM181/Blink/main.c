

#include "SWM181.h"


int main(void)
{	
	SystemInit();
	
	GPIO_Init(GPIOB, PIN0, 0, 1, 0, 0);			//输入，上拉使能，接KEY
	
	GPIO_Init(GPIOD, PIN0, 1, 0, 0, 0);			//输出， 接LED
	GPIO_Init(GPIOB, PIN8, 1, 0, 0, 0);
	GPIO_Init(GPIOB, PIN9, 1, 0, 0, 0);
	
	while(1==1)
	{
		if(GPIO_GetBit(GPIOB, PIN0) == 0)		//按键被按下
		{
			GPIO_SetBit(GPIOB, PIN8);
			GPIO_ClrBit(GPIOB, PIN9);
			GPIO_SetBit(GPIOD, PIN0);
		}
		else
		{
			GPIO_ClrBit(GPIOB, PIN8);
			GPIO_SetBit(GPIOB, PIN9);
			GPIO_ClrBit(GPIOD, PIN0);
		}
	}
}

