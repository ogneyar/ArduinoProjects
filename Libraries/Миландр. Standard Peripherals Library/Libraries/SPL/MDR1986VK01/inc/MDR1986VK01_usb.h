/**
  ******************************************************************************
  * @file    MDR1986VK01_usb.h
  * @author  Milandr Application Team
  * @version V1.0.2
  * @date    06/04/2022
  * @brief   This file contains all the functions prototypes for the USB
  *          firmware library.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE MDR1986VK01_usb.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_USB_H
#define __MDR1986VK01_USB_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup  USB USB
  * @{
  */

/** @defgroup USB_Exported_Macros USB Exported Macros
  * @{
  */

#define ClearBit( reg, bit )    reg &= ( ~( 1 << ( bit ) ) )
#define SetBit( reg, bit )      reg |= ( 1 << ( bit ) )

/** @} */ /* End of group USB_Exported_Macros */

/** @defgroup USB_Exported_Types USB Exported Types
  * @{
  */

/* IntrUSB and IntrUSBE registers bits */
#define USB_INTR_SUSP_BIT          0
#define USB_INTR_RESM_BIT          1
#define USB_INTR_RST_BIT           2
#define USB_INTR_SOF_BIT           3
#define USB_INTR_CON_BIT           4
#define USB_INTR_DISCON_BIT        5

/* DevCtl register bits */
#define USB_DEVC_SESSION_BIT       0
#define USB_DEVC_HOSTREQ_BIT       1
#define USB_DEVC_HOST_BIT          2
#define USB_DEVC_VBUSLO_BIT        3
#define USB_DEVC_VBUSHI_BIT        4
#define USB_DEVC_LSDEV_BIT         5
#define USB_DEVC_FSDEV_BIT         6
#define USB_DEVC_BDEV_BIT          7

/* POWER register bits */
#define USB_PWR_ENSUSPM_BIT        0
#define USB_PWR_SUSPM_BIT          1
#define USB_PWR_RSM_BIT            2
#define USB_PWR_RST_BIT            3
#define USB_PWR_HSM_BIT            4
#define USB_PWR_HSEN_BIT           5
#define USB_PWR_SFTC_BIT           6
#define USB_PWR_ISOU_BIT           7

/* USB PHY control register */
#define USB_M31_OUTCLKSEL          0
#define USB_M31_OSCOUTEN           1
#define USB_M31_PLLEN              2
#define USB_M31_TX_SE0             3
#define USB_M31_TX_DAT             4
#define USB_M31_TX_ENABLE_N        5
#define USB_M31_TX_BITSTUFF_ENH    6
#define USB_M31_TX_BITSTUFF_EN     7
#define USB_M31_LPM_ALIVE          8
#define USB_M31_SESEND             15
#define USB_M31_VBUSVALID          16
#define USB_M31_AVALID             17
#define USB_M31_IDDIG              18

/* USB CSR0 */
#define USB_CSR0_RX_PKT_RDY        0
#define USB_CSR0_TX_PKT_RDY        1
#define USB_CSR0_SENT_STALL        2
#define USB_CSR0_DATA_END          3
#define USB_CSR0_SETUP_END         4
#define USB_CSR0_SEND_STALL        5
#define USB_CSR0_SRV_RX_PKT_RDY    6
#define USB_CSR0_SRV_SETUP_END     7
#define USB_CSR0_FLUSH_FIFO        8

/* USB TXCSR */
#define USB_TXCSR_TX_PKT_RDY       0
#define USB_TXCSR_FIFO_NEMPTY      1
#define USB_TXCSR_UNDER_RUN        2
#define USB_TXCSR_FLUSH_FIFO       3
#define USB_TXCSR_SEND_STALL       4
#define USB_TXCSR_SENT_STALL       5
#define USB_TXCSR_CLR_DATA_TOG     6
#define USB_TXCSR_INCOMP_TX        7
#define USB_TXCSR_DMA_REQ_MODE     10
#define USB_TXCSR_FRC_DATA_TOG     11
#define USB_TXCSR_DMA_REQ_EN       12
#define USB_TXCSR_MODE             13
#define USB_TXCSR_ISO              14
#define USB_TXCSR_AUTO_SET         15

/* USB RXCSR */
#define USB_RXCSR_RX_PKT_RDY       0
#define USB_RXCSR_FIFO_FULL        1
#define USB_RXCSR_OVER_RUN         2
#define USB_RXCSR_DATA_ERROR       3
#define USB_RXCSR_FLUSH_FIFO       4
#define USB_RXCSR_SEND_STALL       5
#define USB_RXCSR_SENT_STALL       6
#define USB_RXCSR_CLR_DATA_TOG     7
#define USB_RXCSR_INCOMP_RX        8
#define USB_RXCSR_DMA_REQ_MODE     11
#define USB_RXCSR_DIS_NYET         12
#define USB_RXCSR_DMA_REQ_EN       13
#define USB_RXCSR_ISO              14
#define USB_RXCSR_AUTO_CLEAR       15

typedef enum
{
    Control = 0,
    Bulk    = 1,
    Iso     = 2,
    Irq     = 3
} USBEpTypes_t;

typedef enum
{
    Tx    = 0,
    Rx    = 1,
    BiDir = 2                                                                                                  // only for EP0
} USBEpDirection_t;

typedef struct
{
    // Operation mode
    uint8_t Device;
    uint8_t HsEnable;
    uint8_t ForceHS;
    uint8_t ForceFS;
    uint8_t Addr;
    uint8_t IntrEn;
} UsbInitCfg_t;

typedef struct
{
    uint32_t *       DataPtr;
    uint16_t         PktMaxSize;
    uint8_t          EP_Num;
    USBEpTypes_t     EP_Type;
    USBEpDirection_t Direction;
    unsigned         AutoHandling    : 1;                                                                      // automaticaly set or clear ready bit
    unsigned         DoubleBuffering : 1;                                                                      // store two packates in FIFO
} UsbEPCfg_t;

/* bRequest types */
typedef enum
{
    GET_STATUS        = 0x00,
    CLEAR_FEATURE     = 0x01,
    Reserved1         = 0x02,
    SET_FEATURE       = 0x03,
    Reserved2         = 0x04,
    SET_ADDRESS       = 0x05,
    GET_DESCRIPTOR    = 0x06,
    SET_DESCRIPTOR    = 0x07,
    GET_CONFIGURATION = 0x08,
    SET_CONFIGURATION = 0x09,
    GET_INTERFACE     = 0x0A,
    SET_INTERFACE     = 0x0B,
    SYNCH_FRAME       = 0x0C
} bRequest_t;

typedef struct
{
    /* Standart Device Request structure */
    uint8_t    bmRequestType;
    bRequest_t bRequest;
    uint16_t   wValue;
    uint16_t   wIndex;
    uint16_t   wLength;
} StdDevReq_t;

typedef enum
{
    USB_EP0 = 0,
    USB_EP1 = 1,
    USB_EP2 = 2,
    USB_EP3 = 3,
    Num_USB_EndPoints
}USB_EP_TypeDef;

enum
{
    USB_ERR = 0,
    USB_OK  = 1
};

/** @} */ /* End of group USB_Exported_Types */


/** @defgroup USB_Exported_Functions USB Exported Functions
  * @{
  */

void USB_EP0_SEND( uint8_t *DataPointer, uint8_t Lenght );

void USB_EP0_GET( uint32_t *DataPointer );

uint32_t USB_ProcessRequest( StdDevReq_t *ObsRqstPtr, uint32_t    *StoragePtr );

uint32_t USB_ClockSetup( void );

uint32_t USB_Init( UsbInitCfg_t *InitCfg );

uint32_t USB_InitEP( UsbEPCfg_t *EPCfg );

uint32_t USB_SEND( UsbEPCfg_t *EPCfg, uint16_t WPP, uint16_t PktNum );
uint32_t USB_GET( UsbEPCfg_t *EPCfg, uint16_t WPP, uint16_t PktNum );


void USB_EP0_SEND( uint8_t *DataPointer, uint8_t Lenght );
void USB_EP0_GET( uint32_t *DataPointer );

void USB_EPX_SEND( uint8_t EndPoint, uint8_t *DataPointer, uint8_t Lenght );

void USB_FillRequest( StdDevReq_t *ReceivedRequest, uint32_t *DataPointer );

void USB_SetSA( uint8_t addr );
uint16_t USB_GetRxCnt( uint8_t ep );

uint8_t USB_SendData( uint8_t ep, uint8_t *data, uint16_t size, uint8_t dataEnd );
uint8_t USB_GetData( uint8_t ep, uint8_t *data );

/** @} */ /* End of group USB_Exported_Functions */

/** @} */ /* End of group USB */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */


#endif /* __MDR1986VK01_USB_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE MDR1986VK01_usb.h */


