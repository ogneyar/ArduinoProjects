/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��delay.c
 * ����    ��
 * ��汾  ��
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��
*****************************************************************/
#include "delay.H"
#include "stm8s.h"
volatile unsigned int TIM2n100usdelay=0;
void Delay(unsigned int nCount)
{
  while (nCount != 0)
  {
    nCount--;
  }
}
void TIM2DelayDecrement(void)
{
  if(TIM2n100usdelay)
  {
    TIM2n100usdelay--;
  }
}
void TIM2Delay_n100us(unsigned int n100us)
{
  TIM2n100usdelay=n100us;
  TIM2->CR1|=0x01;//enable TIM2 
  while(TIM2n100usdelay);
  TIM2->CR1&=~0x01;//disable TIM2
}
