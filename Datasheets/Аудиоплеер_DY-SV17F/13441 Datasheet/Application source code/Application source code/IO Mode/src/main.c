/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��I/Oģʽ����
 * ����    ��  
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��
//--------------------------------------------------------------
  Ӳ������
      ____________________________
     |                           / 
     |         IO0-> PC3         |
     |         IO1-> PC4         |
     |         IO2-> PC5         |
     |         IO3-> PC6         |
     |         IO4-> PC7         |
     |         IO5-> PD1         |
     |         IO6-> PD2         |
     |         IO7-> PD3         |
     |___________________________|

*****************************************************************/
/* Includes ------------------------------------------------- --*/
#include "stm8s.h"
#include "main.h"
#include "clk.h"
#include "led.h"
#include "delay.h"
#include "IO_mode.h"
#include "TIM2.h"

//���ò�����Ŀ�ż�����ģʽ
unsigned char music_num=0x07; //��Ŀ��
unsigned char play_mode=1;    //����ģʽ������ϣ�1��������(0)
unsigned char play_key=1;     //����ģʽ��������ģʽ(1)������ģʽ(0)


void main(void)
{
  
  sim();
  CLK_Config();//CLK HSI 16MHz
  LED_Init();
  rim();
  CFG->GCR|= CFG_GCR_SWD;//Disable swim function
  IO_init();
  TIM2_Init();
//  TIM2Delay_n100us(50000); //s
  LED_OFF();
  
  while (1)
  {
      IO_signal(music_num,play_mode,play_key); //IOģʽ����
      while( GPIOB->IDR & 0x08 == 1);//�ȴ��ͷ�busyλ
      if(play_key == 1)  //����ģʽ������һ�κ�ֹͣ
        break;     
  }
}