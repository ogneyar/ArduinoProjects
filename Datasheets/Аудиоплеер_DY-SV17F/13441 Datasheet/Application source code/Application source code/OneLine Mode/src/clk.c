/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��clk.H
 * ����    ��   
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��

*****************************************************************/
#include "clk.h"

//--------------------------
void CLK_Config(void)
{
    CLK->CKDIVR=0x00 ;                    //16M
    CLK->SWCR |=0x02;                     // enable convert
    CLK->SWR=0xe1;                        //lect HSI
    
    CLK->SWCR &= 0xFD;
    CLK->PCKENR1|=(1<<5);                    //enable TIM2
    
    while((CLK->ICKR&0x02)!=0x02);        //wait for converting success
    /*
    CLK_ECKR |=0X1;  //�����ⲿʱ�� 
    
    while(!(CLK_ECKR&0X2)); //�ȴ��ⲿʱ��rdy 
    
    CLK_CKDIVR &= 0XF8;     //CPU�޷�Ƶ 
    
    CLK_SWR = 0XB4;  //ѡ���ⲿʱ�� 
    
    while(!(CLK_SWCR&0X8)); //����Ҫ�� 
    
    
    CLK_SWCR |=0X2;  //ʹ���ⲿʱ�� 
    */
}