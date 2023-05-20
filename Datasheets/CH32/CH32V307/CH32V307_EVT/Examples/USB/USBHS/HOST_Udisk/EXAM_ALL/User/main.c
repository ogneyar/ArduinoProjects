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
  *����1��
  USBHS�ļ���ö�ٹ�������U���ļ�������дʾ������
    ��ʾ����/C51/CH559HFT.C�ļ�������ҵ������������ļ����ݣ�
    ��ʾ����/LIUNEWFILE.TXT�ļ���ѭ������д��ָ���ַ��������޸��ļ����ԣ�
    ��ʾɾ��/OLD.TXT�ļ���
  *����2��
    �빦��1ͬʱʹ��ʹ��һ����
    ��ʾ����/C51/CH559HFT.C�ļ�������ҵ������������ļ����ݣ�
    ��ʾ����/LIUNEWFILE.TXT�ļ���ѭ������д��ָ���ַ��������޸��ļ����ԣ�
    ��ʾɾ��/OLD.TXT�ļ���
  *����3��
  USBHS��U��Ŀ¼�����ļ����̣�
    �ó�����U�̸�Ŀ¼���½�/YEAR2004��Ŀ¼��Ȼ���ڸ�Ŀ¼���½��ļ�DEMO2004.TXT���ֽ�д������;
    �����/YEAR2004Ŀ¼�´�����Ŀ¼/MONTH05Ŀ¼
  *����4��
  USBHS��U���ļ�ö�����̣�
    ����/C51/CH559HFT.C�ļ������û���ҵ���ö�ٸ�Ŀ¼�²�����10000���ļ�����Ŀ¼(ʵ�ʲ���������)
  *����4��
  USBHS��U��Ŀ¼�������ļ����ļ�����
  OTG_FS_DM(PA11)��OTG_FS_DP(PA12)��
    �������ļ���
    ֧��: FAT12/FAT16/FAT32
*/

#include "debug.h"
#include "ch32v30x_usbhs_host.h"
#include "UDisk_LongName.h"
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
    if ( (j == 0) || ((j == 2) && (mCmdParam.Create.mPathName[1] == ':') ))
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
    UINT8  ret,s,SecCount;
    UINT8  i;
    UINT16 tmp;
    UINT8  tmpbuf[64];
    UINT8  *pCodeStr;
    UINT16 j;
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBHS HOST Test EXAM ALL\r\n");
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
                            printf("CHRV3DiskStatus:%02x\n",CHRV3DiskStatus);
#if 1
#if 0
                            /*====================== ������ʾ�ֽڲ����Ĺ��� ==============================*/
                            printf( "�ֽڲ����Ĺ��� \n" );
                            /* ���ļ� */
                            strcpy( (PCHAR)mCmdParam.Open.mPathName, "/C51/NEWFILE.C" );     //���ý�Ҫ�������ļ�·�����ļ���/C51/NEWFILE.C
                            ret = CHRV3FileOpen( );                                       //���ļ�
                            if ( ret == ERR_MISS_DIR || ret == ERR_MISS_FILE )            //û���ҵ��ļ�
                            {
                                //�����ļ���ʾ
                                printf( "Find No File And Create\r\n" );
                                strcpy( (PCHAR)mCmdParam.Create.mPathName, "/NEWFILE.TXT" );          /* ���ļ���,�ڸ�Ŀ¼��,�����ļ��� */
                                ret = CHRV3FileCreate( );                                        /* �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
//                                mStopIfError( ret );
                                printf( "ByteWrite\n" );
                                //ʵ��Ӧ���ж�д���ݳ��ȺͶ��建���������Ƿ������������ڻ�������������Ҫ���д��
                                i = sprintf( (PCHAR)buf,"Note: \xd\xa������������ֽ�Ϊ��λ����U���ļ���д,����ʾ���ܡ�\xd\xa");  /*��ʾ */
                                for(t=0; t<10; t++)
                                {
                                    mCmdParam.ByteWrite.mByteCount = i;                          /* ָ������д����ֽ��� */
                                    mCmdParam.ByteWrite.mByteBuffer = buf;                       /* ָ�򻺳��� */
                                    ret = CHRV3ByteWrite( );                                       /* ���ֽ�Ϊ��λ���ļ�д������ */
//                                    mStopIfError( ret );
                                    printf("�ɹ�д�� %02X��\r\n",(UINT16)t);
                                }
                                //��ʾ�޸��ļ�����
                                printf( "Modify\r\n" );
                                mCmdParam.Modify.mFileAttr = 0xff;   //�������: �µ��ļ�����,Ϊ0FFH���޸�
                                mCmdParam.Modify.mFileTime = 0xffff;   //�������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�,ʹ���½��ļ�������Ĭ��ʱ��
                                mCmdParam.Modify.mFileDate = MAKE_FILE_DATE( 2015, 5, 18 );  //�������: �µ��ļ�����: 2015.05.18
                                mCmdParam.Modify.mFileSize = 0xffffffff;  // �������: �µ��ļ�����,���ֽ�Ϊ��λд�ļ�Ӧ���ɳ����ر��ļ�ʱ�Զ����³���,���Դ˴����޸�
                                i = CHRV3FileModify( );   //�޸ĵ�ǰ�ļ�����Ϣ,�޸�����
//                                mStopIfError( i );
                                printf( "Close\r\n" );
                                mCmdParam.Close.mUpdateLen = 1;     /* �Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ����� */
                                i = CHRV3FileClose( );
//                                mStopIfError( i );

                                /* ɾ��ĳ�ļ� */
//                                    printf( "Erase\n" );
//                                    strcpy( (PCHAR)mCmdParam.Create.mPathName, "/OLD" );  //����ɾ�����ļ���,�ڸ�Ŀ¼��
//                                    i = CHRV3FileErase( );  //ɾ���ļ����ر�
//                                    if ( i != ERR_SUCCESS ) printf( "Error: %02X\n", (UINT16)i );  //��ʾ����
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
//                                    mStopIfError( ret );
                                    printf("�ɹ�д�� %02X��\r\n",(UINT16)t);
                                }

                                ///////////������ȡ�ļ�ǰN�ֽ�/////////////////////////////////////////
                                TotalCount = 100;                                      //����׼����ȡ�ܳ���100�ֽ�
                                printf( "������ǰ%d���ַ���:\r\n",TotalCount );
                                while ( TotalCount )
                                {                                                      //����ļ��Ƚϴ�,һ�ζ�����,�����ٵ���CH103ByteRead������ȡ,�ļ�ָ���Զ�����ƶ�
                                    if ( TotalCount > (MAX_PATH_LEN-1) ) t = MAX_PATH_LEN-1;/* ʣ�����ݽ϶�,���Ƶ��ζ�д�ĳ��Ȳ��ܳ��� sizeof( mCmdParam.Other.mBuffer ) */
                                    else t = TotalCount;                                 /* ���ʣ����ֽ��� */
                                    mCmdParam.ByteRead.mByteCount = t;                   /* ���������ʮ�ֽ����� */
                                    mCmdParam.ByteRead.mByteBuffer= &buf[0];
                                    ret = CHRV3ByteRead( );                                /* ���ֽ�Ϊ��λ��ȡ���ݿ�,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO,�ڶ��ε���ʱ���Ÿղŵ����� */
                                    TotalCount -= mCmdParam.ByteRead.mByteCount;           /* ����,��ȥ��ǰʵ���Ѿ��������ַ��� */
                                    for ( i=0; i!=mCmdParam.ByteRead.mByteCount; i++ )
                                    {
                                        printf( "%c", mCmdParam.ByteRead.mByteBuffer[i] );  /* ��ʾ�������ַ� */
                                    }
                                    if ( mCmdParam.ByteRead.mByteCount < t )
                                    {
                                        /* ʵ�ʶ������ַ�������Ҫ��������ַ���,˵���Ѿ����ļ��Ľ�β */
                                        printf( "\r\n" );
                                        printf( "�ļ��Ѿ�����\r\n" );
                                        break;
                                    }
                                }

                              ///////////������ָ��λ�ö�ȡ�ļ�N�ֽ�/////////////////////////////////////////
                                printf( "Close\r\n" );
                                i = CHRV3FileClose( );                                    /* �ر��ļ� */
//                                mStopIfError( i );
                                printf( "�ֽڲ�����ʾ���\r\n" );
                                printf( "\r\n" );
                            }
#else
                            /*====================== ������ʾ���������Ĺ��� ==============================*/
                            printf( "��ʾ��������\r\n" );
#if DISK_BASE_BUF_LEN
//                            if ( DISK_BASE_BUF_LEN < CHRV3vSectorSize )
//                            {  /* ���������ݻ������Ƿ��㹻��,CHRV3vSectorSize��U�̵�ʵ��������С */
//                                printf( "Too large sector size\n" );
//                                goto UnknownUsbDevice;
//                            }
#endif
                            /* ��ѯ������������ */
//                            printf( "DiskSize\n" );
//                            i = CHRV3DiskQuery( );
//                            mStopIfError( i );
//                            printf( "TotalSize = %u MB \n", (unsigned int)( mCmdParam.Query.mTotalSector * CHRV3vSectorSizeH / 2 ) );  //��ʾΪ��MBΪ��λ������

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
//                                for(i=0; i<tmp; i++)
//                                {
//                                  printf("%02X ",(UINT16)MY_DATA_BUF[i]);
//                                }
//                                printf("\n");

//                                 ����ļ��Ƚϴ�,һ�ζ�����,�����ٵ���CHRV3FileRead������ȡ,�ļ�ָ���Զ�����ƶ�
//                                 while ( 1 )
//                                 {
//                                   c = 4;   ÿ�ζ�ȡ4������,�����������Խ��һ�ζ�ȡ��������Խ��
//                                   mCmdParam.Read.mSectorCount = c;   ָ����ȡ��������
//                                   mCmdParam.Read.mDataBuffer = &MY_DATA_BUF[0];  ָ���ļ����ݻ���������ʼ��ַ
//                                   CHRV3FileRead();   ������ļ�ָ���Զ����� ��������
//                                   if ( mCmdParam.Read.mSectorCount < c ) break;   ʵ�ʶ�������������С��˵���ļ��Ѿ�����
//                                 }
//                                                                   ���ϣ����ָ��λ�ÿ�ʼ��д,�����ƶ��ļ�ָ��
//                                  mCmdParam.Locate.mSectorOffset = 3;  �����ļ���ǰ3��������ʼ��д
//                                  i = CHRV3FileLocate( );
//                                  mCmdParam.Read.mSectorCount = 10;
//                                  mCmdParam.Read.mDataBuffer = &MY_DATA_BUF[0];  ָ���ļ����ݻ���������ʼ��ַ
//                                  CHRV3FileRead();   ֱ�Ӷ�ȡ���ļ��ĵ�(CHRV3vSectorSizeH*256*3)���ֽڿ�ʼ������,ǰ3������������
//                                                                   ���ϣ������������ӵ�ԭ�ļ���β��,�����ƶ��ļ�ָ��
//                                  i = CHRV3FileOpen( );
//                                  mCmdParam.Locate.mSectorOffset = 0xffffffff;  �Ƶ��ļ���β��,������Ϊ��λ,���ԭ�ļ���3�ֽ�,���CHRV3vSectorSizeH���ֽڴ���ʼ���
//                                  i = CHRV3FileLocate( );
//                                  mCmdParam.Write.mSectorCount = 10;
//                                  mCmdParam.Write.mDataBuffer = &MY_DATA_BUF[0];
//                                  CHRV3FileWrite();   ��ԭ�ļ��ĺ����������
//                                                                   ʹ��CHRV3FileRead�������ж������ݻ���������ʼ��ַ
//                                  mCmdParam.Read.mSectorCount = 2;
//                                  mCmdParam.Read.mDataBuffer = 0x50;  �����������ݷŵ�50H��ʼ�Ļ������У���Ҫָ������������ʼ��ַ
//                                  CHRV3FileRead();   ���ļ��ж�ȡ2��������ָ��������
//                                                                    ʹ��CHRV3FileWrite�������ж������ݻ���������ʼ��ַ
//                                  mCmdParam.Wiite.mSectorCount = 2;
//                                  mCmdParam.Write.mDataBuffer = 0x50;  ��50H��ʼ�Ļ������е�����д��
//                                  CHRV3FileWrite();   ��ָ���������е�����д��2���������ļ���

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
                            printf( "����������ʾ���\r\n" );
#endif
#endif
#if 1
                            /*==================== ������ʾĿ¼�����ļ����� ============================*/
                            printf( "�����Ͷ�ȡ�ļ�\r\n" );
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
                            printf( "Ŀ¼�����ļ����̲�����ʾ���\r\n" );
#endif
#if 1
                            /*==================== ������ʾ��������ȡ���ļ��� ============================*/
                            printf( "�����Ͷ�ȡ���ļ���\r\n" );
                            // ���Ƴ��ļ���(UNICODE ���)��LongNameBuf��
                            memcpy( LongNameBuf, LongName, LongName_Len );
                            // ĩβ������0��ʾ����
                            LongNameBuf[LongName_Len] = 0x00;
                            LongNameBuf[LongName_Len + 1] = 0x00;
                            // �ó��ļ�����ANSI������ļ���(8+3��ʽ)
                            strcpy( mCmdParam.Create.mPathName, "\\���ļ���.TXT" );
                            i = CHRV3CreateLongName( );
                            if( i == ERR_SUCCESS )
                                printf( "Created Long Name OK!!\r\n" );
                            else
                                printf( "Error Code: %02X\n", (UINT16)i );

                            printf( "Get long Name#\r\n" );
                            strcpy( mCmdParam.Open.mPathName, "\\���ļ���.TXT" );
                            // ������Ҫ�����ļ���������·��
                            i = CHRV3GetLongName( );
                            if( i == ERR_SUCCESS )
                            {
                                // ���ļ����ռ����,��UNICODE���뷽ʽ(��UNICODE_ENDIAN����)
                                // �����LongNameBuf������,���ļ������������0����.
                                // ������ʾ����������������
                                printf( "LongNameBuf: " );
                                for( j=0; j!=LONG_NAME_BUF_LEN; j++ )
                                    printf( "%02X ", (UINT16)LongNameBuf[j] );
                                printf( "\r\n" );
                            }
                            else
                            {
                                printf( "Error Code: %02X\r\n", (UINT16)i );
                            }
                            printf( "���ļ�������������ʾ���\r\n" );
#endif
#if 1
                            /*==================== ������ʾö�ٸ�Ŀ¼���ļ����� ============================*/
                            printf( "ö���ļ�\r\n" );
                            printf( "open\r\n" );
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

#endif
                            break;
                        }
                        else
                        {
                            printf("s = %02x\r\n",s);
                            printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
                        }
//                        Delay_Ms( 50 );
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




