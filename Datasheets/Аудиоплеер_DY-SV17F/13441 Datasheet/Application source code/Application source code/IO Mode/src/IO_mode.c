/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��IO_MODE.H
 * ����    ��   
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��

*****************************************************************/

#include "stm8s.h"

void IO_init(void)
{
  //����IO
  
  GPIOD->DDR |= (1<<1) | (1<<2) | (1<<3);    //  PD1-PD3 output mode
  GPIOD->CR1 |= (1<<1) | (1<<2) | (1<<3);
  //GPIOD->CR2 =~(1<<1) | ~(1<<2) | ~(1<<3);
  GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
  
  GPIOC->DDR |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);    //PC3-PC7 output
  GPIOC->CR1 |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
  //GPIOC->CR2 =~(1<<3) | ~(1<<4) | ~(1<<5) | ~(1<<6) | ~(1<<7);
  GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
  
  
  //BUSYλ   BUSYλռ��-�͵�ƽ���ͷ�-�ߵ�ƽ
  GPIOB->DDR &= ~(1<<4);     //PB4 input mode
  GPIOB->CR1 &= ~(1<<4);
  GPIOB->CR2 &= ~(1<<4);
  
}


//IO���Գ��򡪡��������Ϊ��Ŀ�š�ģʽ��0-������1-��ϣ�������ģʽ��0-��ƽ������1-����������

void IO_signal(unsigned char data,unsigned char combin,unsigned char key_touch)
{
  unsigned char n;
  if(combin)  //IO���ģʽ
  {
    for(n=0;n<8;n++)
    {
      if(n<5) //���ݵ�5λ��IO0-IO4
      {
        if((data & (0x01<<n))>>n) 
          GPIOC->ODR &= ~(1<<n+3);  //PC3-PC7�͵�ƽ����
        else       
          GPIOC->ODR |= (1<<n+3);
      }
      else  //���ݸ�3λ,IO5-IO7
      {
        if((data & (0x01<<n))>>n) 
          GPIOD->ODR &= ~(1<<n-4);  //PD1-PD3�͵�ƽ����
        else       
          GPIOD->ODR |= (1<<n-4);
      }
    }
    
  }
  else   //IO����ģʽ
  {
    switch(data)
    {
      case 0x01:
        GPIOC->ODR &= ~(1<<3);//PC3 �͵�ƽ����
        GPIOC->ODR |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
        break;   
      case 0x02:
        GPIOC->ODR &= ~(1<<4);//PC4
        GPIOC->ODR |= (1<<3) | (1<<5) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
        break;   
      case 0x03:
        GPIOC->ODR &= ~(1<<5);//PC5
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
        break;   
      case 0x04:
        GPIOC->ODR &= ~(1<<6);//PC6
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
        break;   
      case 0x05:
        GPIOC->ODR &= ~(1<<7);//PC7
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6);
        GPIOD->ODR |= (1<<1) | (1<<2) | (1<<3);
        break;   
      case 0x06:
        GPIOD->ODR &= ~(1<<1);//PD1
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<2) | (1<<3);
        break;   
      case 0x07:
        GPIOD->ODR &= ~(1<<2);//PD2
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<3);
        break;   
      case 0x08:
        GPIOD->ODR &= ~(1<<3);//PD3
        GPIOC->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
        GPIOD->ODR |= (1<<1) | (1<<2);
        break;   
      default:
        GPIOC->ODR = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);  //8��֮������ݣ�IO0-IO7��Ϊ�ߵ�ƽ
        GPIOD->ODR = (1<<1) | (1<<2) | (1<<3);
        break;
    } 
  }
  if(key_touch)     //����ģʽ
  {
    TIM2Delay_n100us(1000); //����100ms��ʱ   
    GPIOC->ODR = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);  //�ͷŰ���
    GPIOD->ODR = (1<<1) | (1<<2) | (1<<3);
  }
}
