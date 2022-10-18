/******************** (C) COPYRIGHT  ***************************
 * �ļ���  ��one_line_cmd.H
 * ����    ��   
 * ��汾  �� 
 * ����    ��
 * ����    ��
 *�޸�ʱ�� ��

*****************************************************************/
#ifndef __ONE_LINE_CMD_H_
#define __ONE_LINE_CMD_H_
#include "stm8s.h"

//one_lineָ��
#define CLEAR           0x0A    //��������
#define MUSIC_SELECT    0x0B    //ѡȡȷ��
#define VOLUME          0x0C    //��������
#define EQ              0x0D    //����EQ
#define CYCLICAL_MODE   0x0E    //����ѭ��ģʽ
#define CHANNEL         0x0F    //����ͨ��
#define INTER_CUT       0x10    //���ò岥��Ŀ
#define PLAY            0x11    //����
#define PAUSE           Ox12    //��ͣ
#define STOP            0x13    //ֹͣ
#define PREV_MUSIC      0x14    //��һ��
#define NEXT_MUSIC      0x15    //��һ��
#define PREV_CATALOGUE  0x16    //��һĿ¼
#define NEXT_CATALOGUE  0x17    //��һĿ¼
#define SD_CARD         0x18    //ѡ��SD��
#define USB_FLASH_DISK  0x19    //ѡ��U��
#define FLASH_DISK      0x1A    //ѡ��FLASH
#define SYS_HIBERNATION 0x1B    //ϵͳ����
#define CLOSE_DOWN      0x1C    //��������

//--------------------------
void Online_trans(unsigned char data);
void Mix_Command(unsigned char number,unsigned char command);
#endif          