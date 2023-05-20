/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32v30x_usbhs_host.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : This file contains all the functions prototypes for the Udisk
*                      LongName
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef USER_UDISK_LONGNAME_H_
#define USER_UDISK_LONGNAME_H_

#include "debug.h"
#include "string.h"

/*==================== ���ļ�������ĺ궨�弫��ȫ�ֱ��� ======================*/
// ���ļ�����������(0��20)*26
#define     LONG_NAME_BUF_LEN       (20*26)
#define     UNICODE_ENDIAN          0           // 1ΪUNICDOE��˱��� 0ΪС��
// ���ļ�����Ż�����(Unicode����)
extern UINT8 LongNameBuf[ ];
// ���ļ���(Unicode����)
extern UINT8 LongName[ ];

#define     LongName_Len            124

#define     TRUE                    1
#define     FALSE                   0

// ��������
#define     ERR_NO_NAME             0X44        // �˶��ļ���û�г��ļ��������ĳ��ļ�
#define     ERR_BUF_OVER            0X45        // ���ļ����������
#define     ERR_LONG_NAME           0X46        // ����ĳ��ļ���
#define     ERR_NAME_EXIST          0X47        // �˶��ļ�������

/*============================== ������������ ================================*/
extern UINT8 CHRV3GetLongName( void );
extern UINT8 GetUpSectorData( UINT32 *NowSector );
extern UINT8 CHRV3CreateLongName( void );
extern UINT8 AnalyzeLongName( void );
extern UINT8 CheckNameSum( UINT8 *p );

#endif /* USER_UDISK_LONGNAME_H_ */
