/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��ONE_LINE���ܲ���
 * ����    ��  
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��
//--------------------------------------------------------------
  Ӳ������
      _____________________________
     |                            | 
     |  IO4/ONE_LINE---------PD4  |
     |____________________________|

*****************************************************************/
/* Includes ------------------------------------------------- --*/
#include "stm8s.h"
#include "main.h"
#include "clk.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "tim2.h"
#include "IO.h"
#include "one_line_cmd.h"

//���ò���
unsigned char music_num = 2;    //��Ŀ��
unsigned char vol_num = 20;     //����ֵ��Χ0-30���ϵ�Ĭ��20
unsigned char EQ_num = 0;       //EQ���壬NORMAL(00),POP(01),ROCK(02),JAZZ(03),CLASSIC(04),�ϵ�Ĭ��NORMAL(00)
unsigned char cyc_num = 2;      //���岥��ģʽ��ȫ��ѭ����00��������ѭ����01��������ֹͣ��02����ȫ�������03����
                                  //Ŀ¼ѭ����04����Ŀ¼�����05����Ŀ¼˳�򲥷ţ�06����˳�򲥷ţ�07�����ϵ�Ĭ��Ϊ����ֹͣ��
unsigned char chnl_num = 0;     //DAC���ͨ�����壬MP3����ͨ����00����AUX����ͨ����01����MP3+AUX��02�����ϵ�Ĭ��MP3����ͨ�� 


void main(void)
{
  
  sim();
  CLK_Config();//CLK HSI 16MHz
  LED_Init();
  UART_Config();
  rim();
  CFG->GCR|= CFG_GCR_SWD;//Disable swim function
  IO_Init();
  TIM2_Init();
  TIM2Delay_n100us(50000); //s
//  TIM2Delay_n100us(50000); //s
  LED_OFF();
  
      
      /***********��������ָ��***********/
      //ѡ�񲥷Ŵ��̣�SD����U�̡�Flash��ѡһ
      //Online_trans(SD_CARD);            //ѡ��SD��
      //Online_trans(USB_FLASH_DISK);     //ѡ��U��
      //Online_trans(FLASH_DISK);         //ѡ��FLASH
      
      /***********��ϲ���ָ��***********/
      //Mix_Command(vol_num,VOLUME);               //��������
      //Mix_Command(EQ_num,EQ);                    //����EQ
      Mix_Command(cyc_num,CYCLICAL_MODE);          //����ѭ��ģʽ
      //Mix_Command(chnl_num,CHANNEL);             //ѡ�񲥷�ͨ��
  
 //     Online_trans(PLAY);               //����
      //Online_trans(PAUSE);              //��ͣ
      //Online_trans(STOP);               //ֹͣ
      //Online_trans(PREV_MUSIC);         //��һ��
      //Online_trans(NEXT_MUSIC);         //��һ��
      //Online_trans(PREV_CATALOGUE);     //��һĿ¼��������һĿ¼�����һ����Ŀ
      //Online_trans(NEXT_CATALOGUE);     //��һĿ¼��������һĿ¼�е�һ����Ŀ
      //Online_trans(SYS_HIBERNATION);    //ϵͳ����
      //Online_trans(CLOSE_DOWN);         //��������
      //Online_trans(CLEAR);              //�������

     
      //��ѡ�����͡��岥���Ǹ�����Ŀ���ֲ���  
      //����ָ����Ŀ
      //�������Ŀ����ÿһλ���ֵ������ͣ����ַ�����Ϻ��ٷ���ָ��
      //������Ŀ��Ϊ��00123.mp3������ѡ���������������Ϊ��0x01����0x02����0x03����0x0B�������ѡ��
      //���磬00255.mp3
      Online_trans(0);
      Online_trans(0);
      Online_trans(2);
      Online_trans(MUSIC_SELECT);

 /*
      //���ò岥��Ŀ
      Online_trans(2);
      Online_trans(5);
      Online_trans(5);
      Online_trans(INTER_CUT);
*/
  while(1)
  {
      LED_ON();
      TIM2Delay_n100us(5000); //s
      LED_OFF();
      TIM2Delay_n100us(5000); //s
  }
      
}