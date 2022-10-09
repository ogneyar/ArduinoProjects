/******************** (C) COPYRIGHT  ***************************
 * 文件名  ：TIM2.H
 * 描述    ：   
 * 库版本  ： 
 * 作者    ：
 * 博客    ：
 *修改时间 ：

*****************************************************************/
#include "TIM2.h"

//--------------------------
void TIM2_Init(void)
{
  TIM2->PSCR =0x04; // TIM2的时钟频率=fCK_PSC/2^4，即16分频，得到1us时基
  TIM2->ARRH =0x00;
  TIM2->ARRL =0x63; // TIM2_ARR初值设定为0x0063=99，计数100    ----100us
  TIM2->EGR=0x01;
  TIM2->CR1|=0x80;
  TIM2->IER|=0x01;//enable tim int  
//  TIM2->CR1|=0x01;//enable TIM
}