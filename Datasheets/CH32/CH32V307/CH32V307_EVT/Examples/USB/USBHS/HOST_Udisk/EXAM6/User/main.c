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
 USBFS�ļ���ö�ٹ�������U���ļ�������дʾ������
 OTG_FS_DM(PA11)��OTG_FS_DP(PA12)��
 ��ʾ����/C51/CH559HFT.C�ļ�������ҵ������������ļ����ݣ�
 ��ʾ����/LIUNEWFILE.TXT�ļ���ѭ������д��ָ���ַ��������޸��ļ����ԣ�
 ��ʾɾ��/OLD.TXT�ļ���
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
    UINT8  ret, SecCount, s;
    UINT8  i;
    UINT16 tmp;
    UINT8  tmpbuf[64];
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBHS HOST Test EXAM 6\r\n");
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
                            printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
#if DISK_BASE_BUF_LEN
                            //if ( DISK_BASE_BUF_LEN < CHRV3vSectorSize ) {  /* ���������ݻ������Ƿ��㹻��,CHRV3vSectorSize��U�̵�ʵ��������С */
                            //    printf( "Too large sector size\n" );
                            //    goto UnknownUsbDevice;
                            //  }
#endif
                            /* ��ѯ������������ */
                            /*      printf( "DiskSize\n" );
                                    i = CHRV3DiskQuery( );
                                    mStopIfError( i );
                                    printf( "TotalSize = %u MB \n", (unsigned int)( mCmdParam.Query.mTotalSector * CHRV3vSectorSizeH / 2 ) );  ��ʾΪ��MBΪ��λ������
                            */
                            /* ��ȡԭ�ļ� */
                            printf( "Open\r\n" );
                            strcpy( mCmdParam.Open.mPathName, "/C51/CHRV3HFT.C" );//�ļ���,���ļ���C51��Ŀ¼��
                            s = CHRV3FileOpen( );                       //���ļ�
                            if ( s == ERR_MISS_DIR || s == ERR_MISS_FILE )//û���ҵ��ļ�
                            {
                                printf( "û���ҵ��ļ�\r\n" );
                            }
                            else                                        //�ҵ��ļ����߳���
                            {
                                printf( "Query\r\n" );
                                i = CHRV3FileQuery( );                  //��ѯ��ǰ�ļ�����Ϣ
                                mStopIfError( i );
                                printf( "Read\r\n" );
                                CHRV3vFileSize = CHRV3vFileSize+(sizeof( MY_DATA_BUF )-1);    //ԭ�ļ��ĳ���
                                SecCount = CHRV3vFileSize/ sizeof( MY_DATA_BUF )  ;//�����ļ���������,��Ϊ��д��������Ϊ��λ��,�ȼ�CHRV3vSectorSize-1��Ϊ�˶����ļ�β������1�������Ĳ���
                                printf( "Size=%ld, Sec=%d\r\n", CHRV3vFileSize, (UINT16)SecCount );
                                while(SecCount--)
                                {
                                    mCmdParam.Read.mSectorCount = sizeof( MY_DATA_BUF )/512;  //��ȡȫ������,�������2��������ֻ��ȡ2������
                                    mCmdParam.Read.mDataBuffer = &MY_DATA_BUF[0];//ָ���ļ����ݻ���������ʼ��ַ
                                    i = CHRV3FileRead( );                    //���ļ���ȡ����
                                    mStopIfError( i );
                                    if(SecCount == 0) break;
                                    /*
                                    for(tmp=0; tmp<sizeof( MY_DATA_BUF ); tmp++)
                                    {
                                    printf("%02X ",(UINT16)MY_DATA_BUF[tmp]);
                                    }
                                    printf("\n");
                                    */
                                }
                                tmp = (CHRV3vFileSize-(sizeof( MY_DATA_BUF )-1))%sizeof( MY_DATA_BUF );
                                if((tmp == 0)&&(CHRV3vFileSize != 0)) tmp = sizeof( MY_DATA_BUF );
                                CHRV3vFileSize = CHRV3vFileSize-(sizeof( MY_DATA_BUF )-1);    //�ָ�ԭ�ļ��ĳ���
                                /*
                                for(i=0; i<tmp; i++)
                                {
                                  printf("%02X ",(UINT16)MY_DATA_BUF[i]);
                                }
                                printf("\n");
                                */
                                /*
                                                                 ����ļ��Ƚϴ�,һ�ζ�����,�����ٵ���CHRV3FileRead������ȡ,�ļ�ָ���Զ�����ƶ�
                                 while ( 1 )
                                 {
                                   c = 4;   ÿ�ζ�ȡ4������,�����������Խ��һ�ζ�ȡ��������Խ��
                                   mCmdParam.Read.mSectorCount = c;   ָ����ȡ��������
                                   mCmdParam.Read.mDataBuffer = &MY_DATA_BUF[0];  ָ���ļ����ݻ���������ʼ��ַ
                                   CHRV3FileRead();   ������ļ�ָ���Զ����� ��������
                                   if ( mCmdParam.Read.mSectorCount < c ) break;   ʵ�ʶ�������������С��˵���ļ��Ѿ�����
                                 }
                                                                   ���ϣ����ָ��λ�ÿ�ʼ��д,�����ƶ��ļ�ָ��
                                  mCmdParam.Locate.mSectorOffset = 3;  �����ļ���ǰ3��������ʼ��д
                                  i = CHRV3FileLocate( );
                                  mCmdParam.Read.mSectorCount = 10;
                                  mCmdParam.Read.mDataBuffer = &MY_DATA_BUF[0];  ָ���ļ����ݻ���������ʼ��ַ
                                  CHRV3FileRead();   ֱ�Ӷ�ȡ���ļ��ĵ�(CHRV3vSectorSizeH*256*3)���ֽڿ�ʼ������,ǰ3������������
                                                                   ���ϣ������������ӵ�ԭ�ļ���β��,�����ƶ��ļ�ָ��
                                  i = CHRV3FileOpen( );
                                  mCmdParam.Locate.mSectorOffset = 0xffffffff;  �Ƶ��ļ���β��,������Ϊ��λ,���ԭ�ļ���3�ֽ�,���CHRV3vSectorSizeH���ֽڴ���ʼ���
                                  i = CHRV3FileLocate( );
                                  mCmdParam.Write.mSectorCount = 10;
                                  mCmdParam.Write.mDataBuffer = &MY_DATA_BUF[0];
                                  CHRV3FileWrite();   ��ԭ�ļ��ĺ����������
                                                                   ʹ��CHRV3FileRead�������ж������ݻ���������ʼ��ַ
                                  mCmdParam.Read.mSectorCount = 2;
                                  mCmdParam.Read.mDataBuffer = 0x50;  �����������ݷŵ�50H��ʼ�Ļ������У���Ҫָ������������ʼ��ַ
                                  CHRV3FileRead();   ���ļ��ж�ȡ2��������ָ��������
                                                                    ʹ��CHRV3FileWrite�������ж������ݻ���������ʼ��ַ
                                  mCmdParam.Wiite.mSectorCount = 2;
                                  mCmdParam.Write.mDataBuffer = 0x50;  ��50H��ʼ�Ļ������е�����д��
                                  CHRV3FileWrite();   ��ָ���������е�����д��2���������ļ���
                                */
                                printf( "Close\r\n" );
                                i = CHRV3FileClose( );                            //�ر��ļ�
                                mStopIfError( i );
                            }
                            printf( "Create\r\n" );
                            strcpy( mCmdParam.Create.mPathName, "/NEWFILE.TXT" );//���ļ���,�ڸ�Ŀ¼��,�����ļ���
                            s = CHRV3FileCreate( );                               //�½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
                            mStopIfError( s );
                            printf( "Write\r\n" );
                            strcpy( tmpbuf, "0000ABCDEFGHIJKLMNOPQRSTUVWXYZ\xd\xa" );//׼��д�ļ�����
                            for(i=0; i<(DISK_BASE_BUF_LEN/sizeof(tmpbuf)); i++)
                            {
                                tmp=i*sizeof(tmpbuf);
                                strcpy(&MY_DATA_BUF[tmp],tmpbuf);
                            }
                            for(tmp=0; tmp<sizeof(MY_DATA_BUF); tmp++)
                            {
                                printf("%02X",(UINT16)MY_DATA_BUF[tmp]);
                            }
                            printf("\r\n");
                            for(s=0; s<10; s++)
                            {
                                mCmdParam.Write.mSectorCount = 1;                 //д����������������
                                mCmdParam.Write.mDataBuffer = &MY_DATA_BUF[0];    //ָ���ļ����ݻ���������ʼ��ַ
                                i = CHRV3FileWrite( );                            //���ļ�д������
                                mStopIfError( i );
                                printf("�ɹ�д�� %02X��\r\n",(UINT16)s);
                            }
                            /* printf( "Modify\n" );
                               mCmdParam.Modify.mFileAttr = 0xff;   �������: �µ��ļ�����,Ϊ0FFH���޸�
                               mCmdParam.Modify.mFileTime = 0xffff;   �������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�,ʹ���½��ļ�������Ĭ��ʱ��
                               mCmdParam.Modify.mFileDate = MAKE_FILE_DATE( 2015, 5, 18 );  �������: �µ��ļ�����: 2015.05.18
                               mCmdParam.Modify.mFileSize = 0xffffffff;   �������: �µ��ļ�����,���ֽ�Ϊ��λд�ļ�Ӧ���ɳ����ر��ļ�ʱ�Զ����³���,���Դ˴����޸�
                               i = CHRV3FileModify( );   �޸ĵ�ǰ�ļ�����Ϣ,�޸�����
                               mStopIfError( i );
                            */
                            printf( "Close\r\n" );
                            mCmdParam.Close.mUpdateLen = 1;                        //�Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ�����
                            i = CHRV3FileClose( );
                            mStopIfError( i );
                            /* ɾ��ĳ�ļ� */
                            /*printf( "Erase\n" );
                              strcpy( mCmdParam.Create.mPathName, "/OLD.TXT" );  ����ɾ�����ļ���,�ڸ�Ŀ¼��
                              i = CHRV3FileErase( );  ɾ���ļ����ر�
                              if ( i != ERR_SUCCESS ) printf( "Error File not exist: %02X\n", (UINT16)i );  ��ʾ����
                            */
                            printf( "U����ʾ���\r\n" );
                            break;
                        }
                        else
                        {
                            printf("s = %02x\r\n",s);
                            printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
                        }
//                       Delay_Ms( 50 );
                    }
                }
                else
                {

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




