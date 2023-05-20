/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/10/26
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

#include "stdio.h"
#include "string.h"
#include <ch32vf30x_usbfs_host.h>
#include "debug.h"
#include "CHRV3UFI.h"
__attribute__ ((aligned(4))) UINT8   buf[ 128 ];  // OUT, must even address
__attribute__ ((aligned(4))) UINT8   MY_DATA_BUF[ DISK_BASE_BUF_LEN ];   /* MY_DATA_BUFָ���ⲿRAM�Ĵ������ݻ�����,����������Ϊ����һ�������ĳ���,�����û����ݻ���*/
/*******************************************************************************
* Function Name  : mStopIfError
* Description    : ������״̬,�����������ʾ������벢ͣ��
* Input          : UINT8 iError
* Output         : None
* Return         : None
*******************************************************************************/
void    mStopIfError( UINT8 iError )
{
    if ( iError == ERR_SUCCESS )
    {
        return;                                                // �����ɹ�
    }
    printf( "Error: %02X\r\n", (UINT16)iError );                 // ��ʾ����
    /* ���������,Ӧ�÷����������Լ�CHRV3DiskStatus״̬,�������CHRV3DiskReady��ѯ��ǰU���Ƿ�����,���U���ѶϿ���ô�����µȴ�U�̲����ٲ���,
       ��������Ĵ�����:
       1������һ��CHRV3DiskReady,�ɹ����������,����Open,Read/Write��
       2�����CHRV3DiskReady���ɹ�,��ôǿ�н���ͷ��ʼ����(�ȴ�U�����ӣ�CHRV3DiskReady��) */
    while ( 1 )
    {
//      LED_TMP=0;                                             // LED��˸
//      mDelaymS( 100 );
//      LED_TMP=1;
//      mDelaymS( 100 );
    }
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
    UINT8 s;
    UINT8 i;
    UINT8   *pCodeStr;
    UINT16 j;
    USART_Printf_Init(115200);
    Delay_Init();
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("USBFS HOST Test EXAM 11\r\n");
    pHOST_TX_RAM_Addr = TxBuffer;
    pHOST_RX_RAM_Addr = RxBuffer;
    USBOTG_HostInit(ENABLE);
    s = CHRV3LibInit();
    while(1)
    {
        s = ERR_SUCCESS;
        if ( USBOTG_H_FS->INT_FG & USBHD_UIF_DETECT )
        {
            USBOTG_H_FS->INT_FG = USBHD_UIF_DETECT ;

            s = AnalyzeRootHub( );
            if ( s == ERR_USB_CONNECT )
            {
                printf( "New Device In\r\n" );
                FoundNewDev = 1;
            }
            if( s == ERR_USB_DISCON )
            {
                printf( "Device Out\r\n" );
            }
        }

        if ( FoundNewDev || s == ERR_USB_CONNECT )
        {
            FoundNewDev = 0;
            Delay_Ms( 200 );
            s = USBOTG_HostEnum( RxBuffer );
            if ( s == ERR_SUCCESS )
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
                    printf( "List file %s\n", pCodeStr );
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
            else printf( "Enum Failed:%02x\r\n", s );
        }
     }
}
