/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 *@Note
  USBHS��U���ļ�ö�����̣�
    ����/C51/CH559HFT.C�ļ������û���ҵ���ö�ٸ�Ŀ¼�²�����10000���ļ�����Ŀ¼(ʵ�ʲ���������)
    ֧��: FAT12/FAT16/FAT32
*/

#include "debug.h"
#include "ch32v30x_usbhs_host.h"
#include "string.h"
#include "CHRV3UFI.h"

__attribute__ ((aligned(4))) UINT8   RxBuffer[ MAX_PACKET_SIZE  ];  // IN, must even address
__attribute__ ((aligned(4))) UINT8   TxBuffer[ MAX_PACKET_SIZE  ];  // OUT, must even address
__attribute__ ((aligned(4))) UINT8   endpTxBuf[ MAX_PACKET_SIZE ];  // OUT, must even address
__attribute__ ((aligned(4))) UINT8   endpRxBuf[ MAX_PACKET_SIZE ];  // OUT, must even addres
__attribute__ ((aligned(4))) UINT8   buf[ 128 ];  // OUT, must even address
__attribute__ ((aligned(4))) UINT8   MY_DATA_BUF[ DISK_BASE_BUF_LEN ];   /* MY_DATA_BUFָ���ⲿRAM�Ĵ������ݻ�����,����������Ϊ����һ�������ĳ���,�����û����ݻ���*/

/* ������״̬,�����������ʾ������벢ͣ�� */
void mStopIfError( UINT8 iError )
{
    if ( iError == ERR_SUCCESS )
    {
        return;    /* �����ɹ� */
    }
    printf( "Error:%02x\r\n", iError );  /* ��ʾ���� */
    /* ���������,Ӧ�÷����������Լ�CHRV3DiskStatus״̬,�������CHRV3DiskReady��ѯ��ǰU���Ƿ�����,���U���ѶϿ���ô�����µȴ�U�̲����ٲ���,
         ��������Ĵ�����:
         1������һ��CHRV3DiskReady,�ɹ����������,����Open,Read/Write��
         2�����CHRV3DiskReady���ɹ�,��ôǿ�н���ͷ��ʼ���� */
    while(1)
    {  }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    UINT8 ret,s;
    UINT8 i;
    UINT8   *pCodeStr;
    UINT16 j;
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBHS HOST Test EXAM 11\r\n");
	pHOST_TX_RAM_Addr = TxBuffer;
	pHOST_RX_RAM_Addr = RxBuffer;
	USBHS_HostInit(ENABLE);
    ret = CHRV3LibInit();
	while(1)
	{
        if( USBHSH->INT_FG & USBHS_DETECT_FLAG )
        {
            USBHSH->INT_FG = USBHS_DETECT_FLAG;
            if( USBHSH->MIS_ST & USBHS_ATTCH )
            {
                ret = USBHS_HostEnum( );
                if( ret == ERR_SUCCESS )
                {
                    printf( "Enum Succeed\r\n" );
                    Delay_Ms(100);
                    // U�̲������̣�USB���߸�λ��U�����ӡ���ȡ�豸������������USB��ַ����ѡ�Ļ�ȡ������������֮�󵽴�˴�����CH103�ӳ���������ɺ�������
                    CHRV3DiskStatus = DISK_USB_ADDR;
                    for ( i = 0; i != 10; i ++ )
                    {
                        printf( "Wait DiskReady\r\n" );
                        s = CHRV3DiskReady( );                                 //�ȴ�U��׼����
                        if ( s == ERR_SUCCESS )
                        {
                            /* ��ȡԭ�ļ� */
                            printf( "Open\r\n" );
                            strcpy( mCmdParam.Open.mPathName, "/C51/CHRV3HFT.C" );//�ļ���,���ļ���C51��Ŀ¼��
                            s = CHRV3FileOpen( );                        //���ļ�
                            /* �г��ļ� */
                            if ( s == ERR_MISS_DIR )
                            {
                                printf("�����ڸ��ļ����г������ļ�\r\n");  //C51��Ŀ¼���������г���Ŀ¼�µ������ļ�
                                pCodeStr = "/*";
                            }
                            else
                            {
                                pCodeStr = "/C51/*";                     //* CHRV3HFT.C�ļ����������г�\C51��Ŀ¼�µ���CHRV3��ͷ���ļ�
                            }
                            printf( "List file %s\r\n", pCodeStr );
                            for ( j = 0; j < 10000; j ++ )               //�������ǰ10000���ļ�,ʵ����û������
                            {
                                strcpy( mCmdParam.Open.mPathName, pCodeStr );//�����ļ���,*Ϊͨ���,�����������ļ�������Ŀ¼
                                i = strlen( mCmdParam.Open.mPathName );
                                mCmdParam.Open.mPathName[ i ] = 0xFF;    //�����ַ������Ƚ��������滻Ϊ���������,��0��254,�����0xFF��255��˵�����������CHRV3vFileSize������
                                CHRV3vFileSize = j;                      //ָ������/ö�ٵ����
                                i = CHRV3FileOpen( );                    //���ļ�,����ļ����к���ͨ���*,��Ϊ�����ļ�������
                                /* CHRV3FileEnum �� CHRV3FileOpen ��Ψһ�����ǵ����߷���ERR_FOUND_NAMEʱ��ô��Ӧ��ǰ�߷���ERR_SUCCESS */
                                if ( i == ERR_MISS_FILE )
                                {
                                    break;                                //��Ҳ��������ƥ����ļ�,�Ѿ�û��ƥ����ļ���
                                }
                                if ( i == ERR_FOUND_NAME )
                                {
                                    /* ��������ͨ�����ƥ����ļ���,�ļ�����������·������������� */
                                    printf( "  match file %04d#: %s\r\n", (unsigned int)j, mCmdParam.Open.mPathName );//��ʾ��ź���������ƥ���ļ���������Ŀ¼��
                                    continue;                             //����������һ��ƥ����ļ���,�´�����ʱ��Ż��1
                                }
                                else
                                {
                                    /* ���� */
                                    mStopIfError( i );
                                    break;
                                }
                            }
                            printf( "Close\r\n" );
                            i = CHRV3FileClose( );                         //�ر��ļ�
                            printf( "U����ʾ���\r\n" );
                            break;
                        }
                        else
                        {
                            printf("s = %02x\r\n",s);
                            printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
                        }
    //                    Delay_Ms( 50 );
                    }
                }
                else
                {
                    printf( "Enum Failed:%02x\r\n", ret );
                }
            }
            else
            {
                USBHS_HostInit(DISABLE);
                USBHS_HostInit(ENABLE);
                CHRV3DiskStatus = DISK_DISCONNECT;
                printf("disconnect\r\n");
            }
        }
	}
}




