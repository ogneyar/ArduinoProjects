/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��IO_MODE.H
 * ����    ��   
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��

*****************************************************************/
#ifndef __IO_MODE_H_
#define __IO_MODE_H_
#include "stm8s.h"


//--------------------------
void IO_init(void);
void IO_signal(unsigned char data,unsigned char combin,unsigned char key_touch);
#endif