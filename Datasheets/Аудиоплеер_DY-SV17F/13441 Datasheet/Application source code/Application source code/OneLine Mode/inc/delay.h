/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��delay.H
 * ����    ��  
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��
*****************************************************************/
#ifndef __DELAY_H
#define __DELAY_H 


//-------------delay��ʱ����-------------
void Delay(unsigned int nCount);
void TIM2DelayDecrement(void);
void TIM2Delay_n100us(unsigned int n100us);
#endif