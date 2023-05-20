/********************************** (C) COPYRIGHT *******************************
* File Name          : cdc_ecm.h
* Author             : WCH
* Version            : V1.3.0
* Date               : 2022/06/02
* Description        : cdc-ecm program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#ifndef CDC_ECM_CDC_ECM_H_
#define CDC_ECM_CDC_ECM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "string.h"
#include "debug.h"
#include "eth_driver.h"
#include "usb_desc.h"
#include "ch32v30x_usbhs_device.h"

typedef struct __attribute__((packed)) _ECM_SPEED
{
    uint8_t  reqtype;
    uint8_t  bnotifycode;
    uint16_t wvalue;
    uint16_t windex;
    uint16_t wlength;
    uint32_t dlspeed; /* download stream speed on bit-rate */
    uint32_t ulspeed; /* upload stream speed on bit-rate */
}ECM_SPD, *pECM_SPD;

typedef struct __attribute__((packed)) _ECM_LINK
{
    uint8_t  reqtype;
    uint8_t  bnotifycode;
    uint16_t wvalue; /* 0 = link disable; 1 = Link ready */
    uint16_t windex;
    uint16_t wlength;
}ECM_LINK, *pECM_LINK;

#define ECM_SPD_Change                  ((pECM_SPD)ECM_NetWork_Speed_Change)
#define ECM_Link_Status                 ((pECM_LINK)ECM_NetWork_Connection)

/******************************************************************************/
/* CDC-ECM Link Status */
#define DEF_ECM_NETWORK_CONNECTION      0x00
#define DEF_ECM_NETWORK_CONNECT         1
#define DEF_ECM_NETWORK_DISCONN         0
#define DEF_ECM_RES_AVALABLE            0x01
#define DEF_ECM_CONN_SPD_CHANGE         0x2A
#define DEF_ECM_CONN_SPD_100M           100000000
#define DEF_ECM_CONN_SPD_10M            10000000

/******************************************************************************/
/* CDC-ECM package filter (0x43)  */
#define DEF_ECM_PACKFILTER_MASK        0x1F
#define DEF_ECM_PACK_PROMISCUOUS       0x01
#define DEF_ECM_PACK_ALL_MULTICAST     0x02
#define DEF_ECM_PACK_DIRECTED          0x04
#define DEF_ECM_PACK_BROADCASRT        0x08
#define DEF_ECM_PACK_MULTICAST         0x10

/******************************************************************************/
/* CDC-ECMģʽ�������� */
#define DEF_ECM_SENDENCAPCMD            0x00                                    /* Optional�����ڷ���һ������Э����֧�ֵ����� */
#define DEF_ECM_GET_ENCAPRESPONSE       0x01                                    /* Optional����������Կ���Э����֧�ֵĻ�Ӧ */
#define DEF_ECM_SET_ETHMULFILTERS       0x40                                    /* Optional�����������鲥 */
#define DEF_ECM_SET_ETHPOWER            0x41                                    /* Optional�����������Դ����ģʽ */
#define DEF_ECM_GET_ETHPOWER            0x42                                    /* Optional����ȡ�����Դ����ģʽ */
#define DEF_ECM_SET_ETHPACKETFILTER     0x43                                    /* Required: ���������˽�����̫�����Ĺ����� */
#define DEF_ECM_GET_ETHSTATISTIC        0x44                                    /* Optional����ȡ�����豸��ͳ����Ϣ���������Ͱ����������հ����������մ���������� */

/******************************************************************************/
/* CDC-NCMģʽ�������� */
/* 0x40---0x44����ͬECMģʽ */
#define DEF_NCM_GET_NTB_PARAMETERS      0x80                                    /* Required: ��ȡNTB�������ṹ */
#define DEF_NCM_GET_NET_ADDRESS         0x81                                    /* Optional����ȡMAC�����ַ */
#define DEF_NCM_SET_NET_ADDRESS         0x82                                    /* Optional������MAC�����ַ */
#define DEF_NCM_GET_NTB_FORMAT          0x83                                    /* Optional����ȡNTB����ʽ */
#define DEF_NCM_SET_NTB_FORMAT          0x84                                    /* Optional������NTB����ʽ*/
#define DEF_NCM_GET_NTB_INPUT_SIZE      0x85                                    /* Required: ��ȡNTB�������С */
#define DEF_NCM_SET_NTB_INPUT_SIZE      0x86                                    /* Required: ����NTB�������С */
#define DEF_NCM_GET_MAX_DATAGRAM_SIZE   0x87                                    /* Optional����ȡ����������ݰ���С */
#define DEF_NCM_SET_MAX_DATAGRAM_SIZE   0x88                                    /* Optional����������������ݰ���С */
#define DEF_NCM_GET_CRC_MODE            0x89                                    /* Optional����ȡ����CRCģʽ */
#define DEF_NCM_SET_CRC_MODE            0x8A

/******************************************************************************/
/* NET Status Definition */
#define DEF_NETSTAT_LINK_RDY            0x40 /* Valid link established */
#define DEF_NETSTAT_LINK_DIS            0x00 /* No valid link established */
#define DEF_NETSTAT_ANC_RDY             0x20 /* Auto negotiation process completed */
#define DEF_NETSTAT_ANC_DIS             0x00 /* Auto negotiation process not completed */
#define DEF_NETSTAT_100MBITS            0x80 /* Link Speed 100Mbits */
#define DEF_NETSTAT_10MBITS             0x00 /* Link Speed 10MBits */
#define DEF_NETSTAT_FULLDUPLEX          0x01 /* Link Duplex full-duplex */
#define DEF_NETSTAT_HALFDUPLEX          0x00 /* Link Duplex half-duplex */

/* Extern Variable */
extern __attribute__ ((aligned(4))) uint8_t ECM_NetWork_Speed_Change[ ];
extern __attribute__ ((aligned(4))) uint8_t ECM_NetWork_Connection[ ];
extern volatile uint8_t ECM_Pack_Filter;

/* Extern Functions */
extern void USB2ETH_Trance( void );
extern void ETH2USB_Trance( void );
extern void RB_Init( void );
extern void TIM2_Init(void);
extern void mStopIfError( uint8_t iError );
extern void ECM_Load_Status( uint8_t eth_sta );
extern void ECM_Change_MAC_Filter( uint8_t pac_filter );
extern void MACAddr_Change_To_SNDesc( uint8_t *pmacbuf );
extern uint8_t Check_Adr( uint8_t if_u2e, uint32_t addr, uint8_t ptr );

#ifdef __cplusplus
}
#endif

#endif /* CDC_ECM_CDC_ECM_H_ */
