/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��one_line_cmd.c
 * ����    ��   
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��

*****************************************************************/
#include "one_line_cmd.h"
#include "delay.h"

#define Oneline_H GPIOD->ODR |= (1<<4);
#define Oneline_L GPIOD->ODR &= ~(1<<4);


//��������
void Online_trans(unsigned char data)
{
  unsigned char shiftcnt=0;
  Oneline_H
  TIM2Delay_n100us(1); //3ms
  Oneline_L
  TIM2Delay_n100us(30); //3ms
  for(shiftcnt=0;shiftcnt<8;shiftcnt++)
  {
    if(data&0x01)
    {
      Oneline_H
      TIM2Delay_n100us(12); //1200us 
      Oneline_L
      TIM2Delay_n100us(4); //400us
    }
    else
    {
      Oneline_H
      TIM2Delay_n100us(4); //400us 
      Oneline_L
      TIM2Delay_n100us(12); //1200us
    }
    data>>=1;
  }
  Oneline_H;
}


//���������������ú�����
void Mix_Command(unsigned char number,unsigned char command)
{
/*
  unsigned char i;
  unsigned char a[5]={0};
  unsigned char n;
  //��ȡ������ÿλ�ϵ�����
  for(i=0;i<5;i++)    
  {
    a[i] = number/(10^(4-i))%10;
    Online_trans(a[i]);
  }
  
  //�ҵ�������ʼ����
  i=0;
  while(i<5)    
  {
    if(a[i] != 0)break;
    i++;
  } 
  
  //���δ�������
  for(n=i;n<5;n++)
  {
    Online_trans(a[n]);
  }
*/
  Online_trans(number);
  //����ָ��
  Online_trans(command);   
}


















