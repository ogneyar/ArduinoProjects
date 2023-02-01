/****************************************************************************************************************************************** 
* �ļ�����:	system_SWM181.c
* ����˵��:	SWM181��Ƭ����ʱ������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
* ������¼: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/ 
#include <stdint.h>
#include "SWM181.h"


/******************************************************************************************************************************************
 * ϵͳʱ���趨
 *****************************************************************************************************************************************/
#define SYS_CLK_24MHz	0	 	//0 �ڲ���Ƶ24MHz RC����
#define SYS_CLK_6MHz	1		//1 �ڲ���Ƶ 6MHz RC����									
#define SYS_CLK_48MHz	2		//2 �ڲ���Ƶ48MHz RC����									
#define SYS_CLK_12MHz	3		//3 �ڲ���Ƶ12MHz RC����									
#define SYS_CLK_32KHz	4		//4 �ڲ���Ƶ32KHz RC����									
#define SYS_CLK_XTAL	5		//5 �ⲿXTAL����������2-30MHz��

#define SYS_CLK   	SYS_CLK_48MHz


#define __HSI		(24000000UL)		//�����ڲ�ʱ��
#define __LSI		(   32000UL)		//�����ڲ�ʱ��
#define __HSE		(24000000UL)		//�����ⲿʱ��



uint32_t SystemCoreClock  = __HSI;   				//System Clock Frequency (Core Clock)
uint32_t CyclesPerUs      = (__HSI / 1000000); 		//Cycles per micro second


/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: This function is used to update the variable SystemCoreClock and must be called whenever the core clock is changed
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemCoreClockUpdate(void)    
{
	if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)			//SYS_CLK  <= HFCK
	{
		if(SYS->CLKSEL & SYS_CLKSEL_HFCK_Msk)			//HFCK <= HRC/4
		{
			if(SYS->HRCCR & SYS_HRCCR_DBL_Msk)				//HRC = 48MHz
			{
				SystemCoreClock = __HSI*2/4;
			}
			else											//HRC = 24MHz
			{
				SystemCoreClock =  __HSI/4;
			}
		}
		else											//HFCK <= HRC
		{
			if(SYS->HRCCR & SYS_HRCCR_DBL_Msk)				//HRC = 48MHz
			{
				SystemCoreClock = __HSI*2;
			}
			else											//HRC = 24MHz
			{
				SystemCoreClock = __HSI;
			}
		}
	}
	else											//SYS_CLK  <= LFCK
	{
		if(SYS->CLKSEL & SYS_CLKSEL_LFCK_Msk)			//LFCK <= XTAL
		{
			SystemCoreClock = __HSE;
		}
		else											//LFCK <= LRC
		{
			SystemCoreClock = __LSI;
		}
	}
	
	CyclesPerUs = SystemCoreClock / 1000000;
}


/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: The necessary initializaiton of systerm
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemInit(void)
{
	uint32_t i;
	
	SYS->CLKEN |= (1 << SYS_CLKEN_OSC_Pos);
	
	switch(SYS_CLK)
	{
		case SYS_CLK_24MHz:			//0 �ڲ���Ƶ24MHz RC����
			if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)	//��ǰʱ���Ǹ�ƵRC���޸ĸ�ƵRCʱ��Ƶ��ʱ��Ҫ���е�һ���ȶ�ʱ��Դ
			{
				switchToRC32KHz();
			}
			switchToRC24MHz();
			break;
		
		case SYS_CLK_6MHz:			//1 �ڲ���Ƶ 6MHz RC����
			if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)	//��ǰʱ���Ǹ�ƵRC���޸ĸ�ƵRCʱ��Ƶ��ʱ��Ҫ���е�һ���ȶ�ʱ��Դ
			{
				switchToRC32KHz();
			}
			switchToRC6MHz();
			break;
		
		case SYS_CLK_48MHz:			//2 �ڲ���Ƶ48MHz RC����
			if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)	//��ǰʱ���Ǹ�ƵRC���޸ĸ�ƵRCʱ��Ƶ��ʱ��Ҫ���е�һ���ȶ�ʱ��Դ
			{
				switchToRC32KHz();
			}
			switchToRC48MHz();
			break;
		
		case SYS_CLK_12MHz:			//3 �ڲ���Ƶ12MHz RC����
			if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)	//��ǰʱ���Ǹ�ƵRC���޸ĸ�ƵRCʱ��Ƶ��ʱ��Ҫ���е�һ���ȶ�ʱ��Դ
			{
				switchToRC32KHz();
			}
			switchToRC12MHz();
			break;
		
		case SYS_CLK_32KHz:			//4 �ڲ���Ƶ32KHz RC����
			if((SYS->CLKSEL & SYS_CLKSEL_SYS_Msk) == 0)
			{
				switchToRC24MHz();
			}
			switchToRC32KHz();
			break;
		
		case SYS_CLK_XTAL:			//5 �ⲿXTAL����������2-30MHz��
			if((SYS->CLKSEL & SYS_CLKSEL_SYS_Msk) == 0)
			{
				switchToRC24MHz();
			}
			switchToXTAL();
			break;
	}
	
	for(i = 0;i <10000;i++);		//�ȴ�ʱ���ȶ�������
	
	SystemCoreClockUpdate();
}

void switchToRC24MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_EN_Pos) |
				 (0 << SYS_HRCCR_DBL_Pos);		//HRC = 24MHz
	
	SYS->CLKSEL &= ~SYS_CLKSEL_HFCK_Msk;		//HFCK  <=  HRC
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= HFCK
}

void switchToRC6MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_EN_Pos) |
				 (0 << SYS_HRCCR_DBL_Pos);		//HRC = 24MHz
	
	SYS->CLKSEL |= (1 << SYS_CLKSEL_HFCK_Pos);	//HFCK  <=  HRC/4
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= HFCK
}

void switchToRC48MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_EN_Pos) |
				 (1 << SYS_HRCCR_DBL_Pos);		//HRC = 48MHz		
	
	SYS->CLKSEL &= ~SYS_CLKSEL_HFCK_Msk;		//HFCK  <=  HRC
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= HFCK
}

void switchToRC12MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_EN_Pos) |
				 (1 << SYS_HRCCR_DBL_Pos);		//HRC = 48MHz
	
	SYS->CLKSEL |= (1 << SYS_CLKSEL_HFCK_Pos);	//HFCK  <=  HRC/4
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= HFCK
}

void switchToRC32KHz(void)
{
	SYS->LRCCR = (1 << SYS_LRCCR_EN_Pos);
	
	SYS->CLKSEL &= ~(1 << SYS_CLKSEL_LFCK_Pos);	//LFCK  <=  LRC
	SYS->CLKSEL &= ~(1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= LFCK
}

void switchToXTAL(void)
{
	uint32_t i;
	
	PORT_Init(PORTC, PIN1, PORTC_PIN1_XTAL_IN, 0);
	PORT_Init(PORTC, PIN0, PORTC_PIN0_XTAL_OUT, 0);
	
	SYS->XTALCR = (1 << SYS_XTALCR_EN_Pos);
	
	for(i = 0; i < 22118; i++);
	
	SYS->CLKSEL |= (1 << SYS_CLKSEL_LFCK_Pos);	//LFCK  <=  XTAL
	SYS->CLKSEL &= ~(1 << SYS_CLKSEL_SYS_Pos);	//SYS_CLK  <= LFCK
}
