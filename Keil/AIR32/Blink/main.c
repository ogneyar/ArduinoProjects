
#include "air32f10x.h"
#include "air32f10x_rcc.h"
#include "air32f10x_gpio.h"
#include "delay.h"

#define USE_STDDPERIPH_DRIVER


void GPIO_Configuration(void);


int main(void)
{
	Delay_Init();	
	GPIO_Configuration();

	int delay = 50;
	
	while (1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_2);
		Delay_Ms(delay);
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
		Delay_Ms(delay);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		Delay_Ms(delay);
		GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		Delay_Ms(delay);
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
		Delay_Ms(delay);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		Delay_Ms(delay);
	}
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 // 
	GPIO_Init(GPIOB, &GPIO_InitStructure); // GPIOB.2,10,11
}
