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
  USBFS��U��Ŀ¼�����ļ����̣�
  OTG_FS_DM(PA11)��OTG_FS_DP(PA12)��
    �ó�����U�̸�Ŀ¼���½�/YEAR2004��Ŀ¼��Ȼ���ڸ�Ŀ¼���½��ļ�DEMO2004.TXT���ֽ�д������;
    �����/YEAR2004Ŀ¼�´�����Ŀ¼/MONTH05Ŀ¼
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

/*******************************************************************************
* Function Name  : CreateDirectory
* Description    : �½�Ŀ¼����,���Ŀ¼�Ѿ�������ֱ�Ӵ򿪣�Ŀ¼����mCmdParam.Create.mPathName��,���ļ���������ͬ
* Input          :
* Output         : None
* Return         : ERR_SUCCESS = ��Ŀ¼�ɹ����ߴ���Ŀ¼�ɹ�,
                   ERR_FOUND_NAME = �Ѿ�����ͬ���ļ�,
                   ERR_MISS_DIR = ·������Ч�����ϼ�Ŀ¼������
*******************************************************************************/
UINT8   CreateDirectory( void )
{
    UINT8   i, j;
    UINT32  UpDirCluster;
    PUINT8 DirXramBuf;
    UINT8  *DirConstData;
    j = 0xFF;
    for ( i = 0; i != sizeof( mCmdParam.Create.mPathName ); i ++ )    //���Ŀ¼·��
    {
        if ( mCmdParam.Create.mPathName[ i ] == 0 )
        {
            break;
        }
        if ( mCmdParam.Create.mPathName[ i ] == PATH_SEPAR_CHAR1 || mCmdParam.Create.mPathName[ i ] == PATH_SEPAR_CHAR2 )
        {
            j = i;                                                     //��¼�ϼ�Ŀ¼
        }
    }
    i = ERR_SUCCESS;
    if ( j == 0 || (j == 2 && mCmdParam.Create.mPathName[1] == ':') )
    {
        UpDirCluster = 0;                                              //�ڸ�Ŀ¼�´�����Ŀ¼
    }
    else
    {
        if ( j != 0xFF )                                               //���ھ���·��Ӧ�û�ȡ�ϼ�Ŀ¼����ʼ�غ�
        {
            mCmdParam.Create.mPathName[ j ] = 0;
            i = CHRV3FileOpen( );                                      //���ϼ�Ŀ¼
            if ( i == ERR_SUCCESS )
            {
                i = ERR_MISS_DIR;                                      //���ļ�����Ŀ¼
            }
            else if ( i == ERR_OPEN_DIR )
            {
                i = ERR_SUCCESS;                                       //�ɹ����ϼ�Ŀ¼
            }
            mCmdParam.Create.mPathName[ j ] = PATH_SEPAR_CHAR1;        //�ָ�Ŀ¼�ָ���
        }
        UpDirCluster = CHRV3vStartCluster;                             //�����ϼ�Ŀ¼����ʼ�غ�
    }
    if ( i == ERR_SUCCESS )                                            //�ɹ���ȡ�ϼ�Ŀ¼����ʼ�غ�
    {
        i = CHRV3FileOpen( );                                          //�򿪱�����Ŀ¼
        if ( i == ERR_SUCCESS )
        {
            i = ERR_FOUND_NAME;                                        //���ļ�����Ŀ¼
        }
        else if ( i == ERR_OPEN_DIR )
        {
            i = ERR_SUCCESS;                                           //Ŀ¼�Ѿ�����
        }
        else if ( i == ERR_MISS_FILE )                                 //Ŀ¼������,�����½�
        {
            i = CHRV3FileCreate( );                                    //�Դ����ļ��ķ�������Ŀ¼
            if ( i == ERR_SUCCESS )
            {
                if ( pDISK_FAT_BUF == pDISK_BASE_BUF )
                {
                    memset(pDISK_FAT_BUF,0,CHRV3vSectorSize);     //���FILE_DATA_BUF��DISK_BASE_BUF���������������̻�����
                }
                DirXramBuf = pDISK_FAT_BUF;                            //�ļ����ݻ�����
                DirConstData = ".          \x10\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x21\x30\x0\x0\x0\x0\x0\x0..         \x10\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x21\x30\x0\x0\x0\x0\x0\x0";
                for ( i = 0x40; i != 0; i -- )                         //Ŀ¼�ı�����Ԫ,�ֱ�ָ��������ϼ�Ŀ¼
                {
                    *DirXramBuf = *DirConstData;
                    DirXramBuf ++;
                    DirConstData ++;
                }
                *(pDISK_FAT_BUF+0x1A) = ( (PUINT8)&CHRV3vStartCluster )[3];//�������ʼ�غ�
                *(pDISK_FAT_BUF+0x1B) = ( (PUINT8)&CHRV3vStartCluster )[2];
                *(pDISK_FAT_BUF+0x14) = ( (PUINT8)&CHRV3vStartCluster )[1];
                *(pDISK_FAT_BUF+0x15) = ( (PUINT8)&CHRV3vStartCluster )[0];
                *(pDISK_FAT_BUF+0x20+0x1A) = ( (PUINT8)&UpDirCluster )[3];//�ϼ�Ŀ¼����ʼ�غ�
                *(pDISK_FAT_BUF+0x20+0x1B) = ( (PUINT8)&UpDirCluster )[2];
                *(pDISK_FAT_BUF+0x20+0x14) = ( (PUINT8)&UpDirCluster )[1];
                *(pDISK_FAT_BUF+0x20+0x15) = ( (PUINT8)&UpDirCluster )[0];
//              for ( count = 0x40; count != CHRV3vSectorSizeH*256; count ++ ) {  /* ���Ŀ¼��ʣ�ಿ�� */
//                  *DirXramBuf = 0;
//                  DirXramBuf ++;
//              }
                mCmdParam.Write.mSectorCount = 1;
                mCmdParam.Write.mDataBuffer = pDISK_FAT_BUF;                //ָ���ļ����ݻ���������ʼ��ַ
                i = CHRV3FileWrite( );                                      //���ļ�д������
                if ( i == ERR_SUCCESS )
                {
                    DirXramBuf = pDISK_FAT_BUF;
                    for ( i = 0x40; i != 0; i -- )                          //���Ŀ¼��
                    {
                        *DirXramBuf = 0;
                        DirXramBuf ++;
                    }
                    for ( j = 1; j != CHRV3vSecPerClus; j ++ )
                    {
                        if ( pDISK_FAT_BUF == pDISK_BASE_BUF )
                        {
                            memset(pDISK_FAT_BUF,0,CHRV3vSectorSize);   //���FILE_DATA_BUF��DISK_BASE_BUF���������������̻�����
                        }
                        mCmdParam.Write.mSectorCount = 1;
                        mCmdParam.Write.mDataBuffer = pDISK_FAT_BUF;         //ָ���ļ����ݻ���������ʼ��ַ
                        i = CHRV3FileWrite( );                               //���Ŀ¼��ʣ������
                        if ( i != ERR_SUCCESS )
                        {
                            break;
                        }
                    }
                    if ( j == CHRV3vSecPerClus )                              //�ɹ����Ŀ¼
                    {
                        mCmdParam.Modify.mFileSize = 0;                       //Ŀ¼�ĳ�������0
                        mCmdParam.Modify.mFileDate = 0xFFFF;
                        mCmdParam.Modify.mFileTime = 0xFFFF;
                        mCmdParam.Modify.mFileAttr = 0x10;                    //��Ŀ¼����
                        i = CHRV3FileModify( );                               //���ļ���Ϣ�޸�ΪĿ¼
                    }
                }
            }
        }
    }
    return( i );
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
    UINT8  ret, s;
    UINT8  i;
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBHS HOST Test EXAM 9\r\n");
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
                        printf( "Create Level 1 Directory /YEAR2004 \r\n" );
                        strcpy( mCmdParam.Create.mPathName, "/YEAR2004" );           //Ŀ¼��,��Ŀ¼���ڸ�Ŀ¼��
                        i = CreateDirectory( );                                      //�½����ߴ�Ŀ¼
                        mStopIfError( i );
                        /* Ŀ¼�½����ߴ򿪳ɹ�,�����������Ŀ¼���½�һ����ʾ�ļ� */
                        printf( "Create New File /YEAR2004/DEMO2004.TXT \r\n" );
                        strcpy( mCmdParam.Create.mPathName, "/YEAR2004/DEMO2004.TXT" );//�ļ���
                        i = CHRV3FileCreate( );                                       //�½��ļ�����,����ļ��Ѿ���������ɾ�������½�
                        mStopIfError( i );
                        printf( "Write some data to file DEMO2004.TXT \r\n" );
                        i = sprintf( buf, "��ʾ�ļ�\xd\xa" );
                        mCmdParam.ByteWrite.mByteCount = i;                           //ָ������д����ֽ���,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO
                        mCmdParam.ByteWrite.mByteBuffer = buf;                        //ָ�򻺳���
                        i = CHRV3ByteWrite( );                                        //���ֽ�Ϊ��λ���ļ�д������,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO
                        mStopIfError( i );
                        printf( "Close file DEMO2004.TXT \r\n" );
                        mCmdParam.Close.mUpdateLen = 1;                               //�Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ�����
                        i = CHRV3FileClose( );
                        mStopIfError( i );
                        /* �����½�������Ŀ¼,������ǰ���һ����Ŀ¼��ȫ��ͬ */
                        printf( "Create Level 2 Directory /YEAR2004/MONTH05 \r\n" );
                        strcpy( mCmdParam.Create.mPathName, "/YEAR2004/MONTH05" );    //Ŀ¼��,��Ŀ¼����YEAR2004��Ŀ¼��,YEAR2004Ŀ¼�������ȴ���
                        i = CreateDirectory( );                                       //�½����ߴ�Ŀ¼
                        mStopIfError( i );
                        printf( "Close\r\n" );
                        mCmdParam.Close.mUpdateLen = 0;                               //����Ŀ¼����Ҫ�Զ������ļ�����
                        i = CHRV3FileClose( );                                        //�ر�Ŀ¼,Ŀ¼����Ҫ�ر�,�ر�ֻ��Ϊ�˷�ֹ���������
                        mStopIfError( i );
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




