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
 USBHS�豸�����ֽ�Ϊ��λ��д���̣�
 OTG_FS_DM(PA11)��OTG_FS_DP(PA12)
  ��������ʾ U���ļ�ϵͳ,���ֽ�Ϊ��λ��д�ļ���
  ע���ļ�ϵͳ֧�� FAT12/FAT16/FAT32��
*/
#include "stdio.h"
#include "string.h"
#include <ch32vf30x_usbfs_host.h>
#include "debug.h"
#include "CHRV3UFI.h"
__attribute__ ((aligned(4))) UINT8   buf[ 128 ];  // OUT, must even address
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
    printf( "Error: %02X\n", (UINT16)iError );                 // ��ʾ����
    /* ���������,Ӧ�÷����������Լ�CH559DiskStatus״̬,�������CH559DiskReady��ѯ��ǰU���Ƿ�����,���U���ѶϿ���ô�����µȴ�U�̲����ٲ���,
       ��������Ĵ�����:
       1������һ��CH559DiskReady,�ɹ����������,����Open,Read/Write��
       2�����CH559DiskReady���ɹ�,��ôǿ�н���ͷ��ʼ����(�ȴ�U�����ӣ�CH559DiskReady��) */
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
    UINT8 ret,s;
    UINT8 i,t;
    UINT16 TotalCount = 0;
    USART_Printf_Init(115200);
    Delay_Init();
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("USBFS HOST Test EXAM 1\r\n");
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
                        printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
                        /* ���ļ� */
                        strcpy( (PCHAR)mCmdParam.Open.mPathName, "/NEWFILE.C" );     //���ý�Ҫ�������ļ�·�����ļ���/C51/NEWFILE.C
                        ret = CHRV3FileOpen( );                                       //���ļ�
                        if ( ret == ERR_MISS_DIR || ret == ERR_MISS_FILE )            //û���ҵ��ļ�
                        {
                            //�����ļ���ʾ
                            printf( "Find No File And Create\r\n" );
                            strcpy( (PCHAR)mCmdParam.Create.mPathName, "/NEWFILE.C" );          /* ���ļ���,�ڸ�Ŀ¼��,�����ļ��� */
                            ret = CHRV3FileCreate( );                                        /* �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
                            mStopIfError( ret );
                            printf( "ByteWrite\r\n" );
                            //ʵ��Ӧ���ж�д���ݳ��ȺͶ��建���������Ƿ������������ڻ�������������Ҫ���д��
                            i = sprintf( (PCHAR)buf,"Note: \xd\xa������������ֽ�Ϊ��λ����U���ļ���д,����ʾ���ܡ�\xd\xa");  /*��ʾ */
                            for(t=0; t<10; t++)
                            {
                                mCmdParam.ByteWrite.mByteCount = i;                          /* ָ������д����ֽ��� */
                                mCmdParam.ByteWrite.mByteBuffer = buf;                       /* ָ�򻺳��� */
                                ret = CHRV3ByteWrite( );                                       /* ���ֽ�Ϊ��λ���ļ�д������ */
                                mStopIfError( ret );
                                printf("�ɹ�д�� %02X��\r\n",(UINT16)t);
                            }
                            //��ʾ�޸��ļ�����
                            printf( "Modify\r\n" );
                            mCmdParam.Modify.mFileAttr = 0xff;   //�������: �µ��ļ�����,Ϊ0FFH���޸�
                            mCmdParam.Modify.mFileTime = 0xffff;   //�������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�,ʹ���½��ļ�������Ĭ��ʱ��
                            mCmdParam.Modify.mFileDate = MAKE_FILE_DATE( 2015, 5, 18 );  //�������: �µ��ļ�����: 2015.05.18
                            mCmdParam.Modify.mFileSize = 0xffffffff;  // �������: �µ��ļ�����,���ֽ�Ϊ��λд�ļ�Ӧ���ɳ����ر��ļ�ʱ�Զ����³���,���Դ˴����޸�
                            i = CHRV3FileModify( );   //�޸ĵ�ǰ�ļ�����Ϣ,�޸�����
                            mStopIfError( i );
                            printf( "Close\r\n" );
                            mCmdParam.Close.mUpdateLen = 1;     /* �Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ����� */
                            i = CHRV3FileClose( );
                            mStopIfError( i );

                            /* ɾ��ĳ�ļ� */
    //          printf( "Erase\n" );
    //          strcpy( (PCHAR)mCmdParam.Create.mPathName, "/OLD" );  //����ɾ�����ļ���,�ڸ�Ŀ¼��
    //          i = CHRV3FileErase( );  //ɾ���ļ����ر�
    //          if ( i != ERR_SUCCESS ) printf( "Error: %02X\n", (UINT16)i );  //��ʾ����
                        }
                        else
                        {
                            //���ϣ������������ӵ�ԭ�ļ���β��,�����ƶ��ļ�ָ��
                          ///////////һ��д���ļ�/////////////////////////////////////////
                            printf( "ByteWrite\r\n" );
                            mCmdParam.ByteLocate.mByteOffset = 0xffffffff;  //�Ƶ��ļ���β��
                            CHRV3ByteLocate( );
                          //ʵ��Ӧ���ж�д���ݳ��ȺͶ��建���������Ƿ������������ڻ�������������Ҫ���д��
                            i = sprintf( (PCHAR)buf,"Note: \xd\xa������������ֽ�Ϊ��λ����U���ļ���д,����ʾ���ܡ�\xd\xa");  /*��ʾ */
                            for(t=0; t<10; t++)
                            {
                                mCmdParam.ByteWrite.mByteCount = i;                          /* ָ������д����ֽ��� */
                                mCmdParam.ByteWrite.mByteBuffer = buf;                       /* ָ�򻺳��� */
                                ret = CHRV3ByteWrite( );                                       /* ���ֽ�Ϊ��λ���ļ�д������ */
                                mStopIfError( ret );
                                printf("�ɹ�д�� %02X��\r\n",(UINT16)t);
                            }

                            printf( "Modify\r\n" );
                            mCmdParam.Modify.mFileAttr = 0xff;   //�������: �µ��ļ�����,Ϊ0FFH���޸�
                            mCmdParam.Modify.mFileTime = 0xffff;   //�������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�,ʹ���½��ļ�������Ĭ��ʱ��
                            mCmdParam.Modify.mFileDate = MAKE_FILE_DATE( 2015, 5, 18 );  //�������: �µ��ļ�����: 2015.05.18
                            mCmdParam.Modify.mFileSize = 0xffffffff;  // �������: �µ��ļ�����,���ֽ�Ϊ��λд�ļ�Ӧ���ɳ����ر��ļ�ʱ�Զ����³���,���Դ˴����޸�
                            i = CHRV3FileModify( );   //�޸ĵ�ǰ�ļ�����Ϣ,�޸�����
                            mStopIfError( i );
                            printf( "Close\r\n" );
                            mCmdParam.Close.mUpdateLen = 1;     /* �Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ����� */
                            i = CHRV3FileClose( );
                            mStopIfError( i );

                              /* open*/
                              strcpy( (PCHAR)mCmdParam.Open.mPathName, "/NEWFILE.C" );     //���ý�Ҫ�������ļ�·�����ļ���/C51/NEWFILE.C
                              ret = CHRV3FileOpen( );
                              if( ret == ERR_SUCCESS )
                              {
                                  ///////////������ȡ�ļ�ǰN�ֽ�/////////////////////////////////////////
                                  TotalCount = 100;                                      //����׼����ȡ�ܳ���100�ֽ�
                                  printf( "������ǰ%d���ַ���:\r\n",TotalCount );
                                  while ( TotalCount ) {                                 //����ļ��Ƚϴ�,һ�ζ�����,�����ٵ���CH103ByteRead������ȡ,�ļ�ָ���Զ�����ƶ�
                                      if ( TotalCount > (MAX_PATH_LEN-1) ) t = MAX_PATH_LEN-1;/* ʣ�����ݽ϶�,���Ƶ��ζ�д�ĳ��Ȳ��ܳ��� sizeof( mCmdParam.Other.mBuffer ) */
                                      else t = TotalCount;                                 /* ���ʣ����ֽ��� */
                                      mCmdParam.ByteRead.mByteCount = t;                   /* ���������ʮ�ֽ����� */
                                      mCmdParam.ByteRead.mByteBuffer= &buf[0];
                                      ret = CHRV3ByteRead( );                                /* ���ֽ�Ϊ��λ��ȡ���ݿ�,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO,�ڶ��ε���ʱ���Ÿղŵ����� */
                                      TotalCount -= mCmdParam.ByteRead.mByteCount;           /* ����,��ȥ��ǰʵ���Ѿ��������ַ��� */
                                      for ( i=0; i!=mCmdParam.ByteRead.mByteCount; i++ ) printf( "%c", mCmdParam.ByteRead.mByteBuffer[i] );  /* ��ʾ�������ַ� */
                                      if ( mCmdParam.ByteRead.mByteCount < t ) {             /* ʵ�ʶ������ַ�������Ҫ��������ַ���,˵���Ѿ����ļ��Ľ�β */
                                          printf( "\r\n" );
                                          printf( "�ļ��Ѿ�����\r\n" );
                                          break;
                                      }
                                  }
                              }

                          ///////////������ָ��λ�ö�ȡ�ļ�N�ֽ�/////////////////////////////////////////
                            printf( "Close\r\n" );
                            i = CHRV3FileClose( );                                    /* �ر��ļ� */
                            mStopIfError( i );
                        }
                        break;
                    }
                    else
                    {
                        printf("s = %02x\r\n",s);
                        printf("CHRV3DiskStatus:%02x\n",CHRV3DiskStatus);
                    }
//                    Delay_Ms( 50 );
                }
            }
            else printf( "Enum Failed:%02x\r\n", s );
        }
     }
}
