/**
  ******************************************************************************
  * @file    MDR1986VK01_usb.c
  * @author  Milandr Application Team
  * @version V1.3.0
  * @date    06/04/2022
  * @brief   This file contains all the EBC firmware functions.
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
  * FILE MDR1986VK01_usb.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_usb.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @defgroup USB USB
  * @{
  */

/** @defgroup USB_Private_Function_Prototypes USB Private Function Prototypes
 * 	@{
 */

static uint32_t power( uint32_t x, uint32_t n );
static uint32_t USB_SetPullPeriod( UsbEPCfg_t  *EPCfg );

/** @} */ /* End of group USB_Private_Function_Prototypes */

/** @defgroup USB_Exported_Functions USB Exported Functions
 * 	@{
 */

/**
  * @param  UsbInitCfg_t pointer
  * @retval uint32_t
  */
uint32_t USB_Init( UsbInitCfg_t *InitCfg )
{
    if ( InitCfg->ForceHS == 1 )
    {
        SetBit( MDR_USB0->TESTMODE, 4 );
    }

    if ( InitCfg->ForceFS == 1 )
    {
        SetBit( MDR_USB0->TESTMODE, 5 );
    }

    /* Enable basic IRQ - reset and SOF detection */
    MDR_USB0->INTRUSBE = ( 1 << USB_INTR_CON_BIT ) | ( 1 << USB_INTR_RST_BIT );

    /* Set HS bit */
    if ( InitCfg->HsEnable == 1 )
    {
        SetBit( MDR_USB0->POWER, USB_PWR_HSEN_BIT );
    }
    else
    {
        ClearBit( MDR_USB0->POWER, USB_PWR_HSEN_BIT );
    }

    /* If Peripheral */
    if ( InitCfg->Device == 1 )
    {
        /* IDDIG bit already set */
        /* Set softconn bit */
        /* Stay here until controller goes in Session. */
        SetBit( MDR_USB0->POWER, USB_PWR_SFTC_BIT );
        while ( ( MDR_USB0->DEVCTL & ( 1 << USB_DEVC_SESSION_BIT ) ) == 0 );
    }

    /* if Host */
    if ( InitCfg->Device == 0 )
    {
        /* clear IDDIG bit - be A-device and Start a session */

        ClearBit( MDR_USB_RAM0->USB_M31_CNTR, USB_M31_IDDIG );
        SetBit( MDR_USB0->DEVCTL, USB_DEVC_SESSION_BIT );
    }

    return( 0 );
}

/**
  * @param  UsbEPCfg_t pointer
  * @retval uint32_t
  */
uint32_t USB_InitEP( UsbEPCfg_t *EPCfg )
{
    uint32_t FifoSize;

    MDR_USB0->INDEX = EPCfg->EP_Num;

    FifoSize = power( 2, ( MDR_USB0->CONFIGDATA_FIFOSIZE & 0x0000000F ) );

    if ( ( EPCfg->PktMaxSize <= ( FifoSize / 2 ) ) & ( EPCfg->EP_Type != Iso ) )
    {
        EPCfg->DoubleBuffering = 1;
    }
    else
    {
        EPCfg->DoubleBuffering = 0;
    }

    if ( EPCfg->Direction == Tx )
    {
        switch ( EPCfg->EP_Type )
        {
        case Control:
            ClearBit( MDR_USB0->CSR0_TXCSR, 14 );                                                              // Clear ISO
            SetBit( MDR_USB0->CSR0_TXCSR, 13 );                                                                // Set Tx
            ClearBit( MDR_USB0->CSR0_TXCSR, 11 );                                                              // Allow Data toggle
            break;
        case Bulk:
            ClearBit( MDR_USB0->CSR0_TXCSR, 14 );                                                              // Clear ISO
            SetBit( MDR_USB0->CSR0_TXCSR, 13 );                                                                // Set Tx
            ClearBit( MDR_USB0->CSR0_TXCSR, 11 );                                                              // Allow Data toggle
            break;
        case Iso:
            SetBit( MDR_USB0->CSR0_TXCSR, 14 );                                                                // Set ISO
            SetBit( MDR_USB0->CSR0_TXCSR, 13 );                                                                // Set Tx
            ClearBit( MDR_USB0->CSR0_TXCSR, 12 );                                                              // Disable Nyet
            break;
        case Irq:
            ClearBit( MDR_USB0->CSR0_TXCSR, 14 );                                                              // Clear ISO
            SetBit( MDR_USB0->CSR0_TXCSR, 13 );                                                                // Set Tx
            break;
        /* invalid cfg */
        default:        return 1;
            //break;
        }

        if ( EPCfg->AutoHandling == 1 )
        {
            SetBit( MDR_USB0->CSR0_TXCSR, 15 );
        }

        /* Enable IRQ */
        MDR_USB0->INTRTXE |= ( 1 << EPCfg->EP_Num );

        MDR_USB0->TXMAXP = EPCfg->PktMaxSize;
        if ( EPCfg->EP_Type == Iso )
        {
            MDR_USB0->TXMAXP |= ( 1 << 11 );                                                                   // 1 pkt per uFrame
        }
        return 0;
    }

    if ( EPCfg->Direction == Rx )
    {
        switch ( EPCfg->EP_Type )
        {
        case Control:
            ClearBit( MDR_USB0->RXCSR, 14 );                                                                   // Clear ISO
            ClearBit( MDR_USB0->RXCSR, 11 );                                                                   // Data toggle
            break;
        case Bulk:
            ClearBit( MDR_USB0->RXCSR, 14 );                                                                   // Clear ISO
            ClearBit( MDR_USB0->RXCSR, 12 );                                                                   // Enable Nyet
            break;
        case Iso:
            SetBit( MDR_USB0->RXCSR, 14 );                                                                     // Set ISO
            ClearBit( MDR_USB0->RXCSR, 12 );                                                                   // Enable Nyet
            break;
        case Irq:
            ClearBit( MDR_USB0->RXCSR, 14 );                                                                   // Clear ISO
            SetBit( MDR_USB0->RXCSR, 12 );                                                                     // Disable Nyet
            break;
        /* invalid cfg */
        default:        return 1;
            //break;
        }

        if ( EPCfg->AutoHandling == 1 )
        {
            SetBit( MDR_USB0->RXCSR, 15 );
        }

        /* Enable IRQ */
        MDR_USB0->INTRRXE |= ( 1 << EPCfg->EP_Num );

        MDR_USB0->RXMAXP = EPCfg->PktMaxSize;

        if ( EPCfg->EP_Type == Iso )
        {
            MDR_USB0->RXMAXP |= ( 1 << 11 );                                                                   // 1 pkt per uFrame
        }
        return 0;
    }

    return 0;
}

/**
  * @param  UsbEPCfg_t pointer
  * @param  uint16_t WPP
  * @param  uint16_t PktNum
  * @retval uint32_t
  */
uint32_t USB_GET( UsbEPCfg_t *EPCfg, uint16_t WPP, uint16_t PktNum )
{
    uint16_t          PktCnt;
    uint16_t          WrdCnt;
    uint32_t          WrdAmount;
    volatile uint32_t delay;
    uint32_t          pull_period;

    MDR_USB0->INDEX = EPCfg->EP_Num;
    pull_period     = USB_SetPullPeriod( EPCfg ) >> 2;

    for ( PktCnt = 0; PktCnt < PktNum; PktCnt++ )
    {
        /* Clear OverRun */
        ClearBit( MDR_USB0->RXCSR, 2 );

        /* Wait RxPktRdy */
        do
        {
            do
            {
                delay++;
            } while ( delay <= pull_period );
            delay = 0;
        } while ( ( MDR_USB0->INTRRX & ( 1 << EPCfg->EP_Num ) ) != ( 1 << EPCfg->EP_Num ) );

        /* check number of received bytes and convert them info words */
        WrdAmount = MDR_USB0->COUNT0_RXCOUNT >> 2;

        /* Copy data from FIFO */
        for ( WrdCnt = 0; WrdCnt < WrdAmount; WrdCnt++ )
        {
            *( EPCfg->DataPtr + WrdCnt + ( PktCnt * WrdAmount ) ) = MDR_USB0->FIFO[ EPCfg->EP_Num ];
        }

        /* Clear RxPktRdy */
        if ( EPCfg->AutoHandling == 0 )
        {
            ClearBit( MDR_USB0->RXCSR, 0 );
        }
    }

    return 0;
}

void USB_GetDataEp0( uint32_t *DataPointer )
{
    volatile uint32_t delay;
    uint32_t          WrdAmount;
    uint8_t           pt;

    MDR_USB0->INDEX = 0;

    do
    {
        do
        {
            delay++;
        } while ( delay <= 10 );
        delay = 0;
        /* wait RxPktRdy bit */
    } while ( ( MDR_USB0->CSR0_TXCSR & ( 1 << 0 ) ) == 0 );

    /* check number of received bytes and convert them info words */
    WrdAmount = MDR_USB0->COUNT0_RXCOUNT >> 2;

    /* unload packet from the FIFO */
    for ( pt = 0; pt < WrdAmount; pt++ )
    {
        *( DataPointer + pt ) = MDR_USB0->FIFO[ 0 ];
    }
}

void USB_SetSA( uint8_t addr )
{
    MDR_USB0->FADDR = addr;
}

uint16_t USB_GetRxCnt( uint8_t ep )
{
    uint16_t cnt;

    MDR_USB0->INDEX = ep;
    cnt             = MDR_USB0->COUNT0_RXCOUNT;

    return cnt;
}

uint8_t USB_SendData( uint8_t ep, uint8_t *data, uint16_t size, uint8_t dataEnd )
{
    uint16_t i;

    MDR_USB0->INDEX = ep;

    if ( ( ep == 0 ) && ( MDR_USB0->CSR0_TXCSR & ( 1 << USB_CSR0_TX_PKT_RDY ) ) )
        return USB_ERR;
    else if ( ( ep != 0 ) && MDR_USB0->CSR0_TXCSR & ( 1 << USB_TXCSR_TX_PKT_RDY ) )
        return USB_ERR;

    if ( size == 0 )
    {
        if ( ep == 0 )
        {
            MDR_USB0->CSR0_TXCSR |= ( 1 << 8 );
//            MDR_USB0->CSR0_TXCSR |= (1<<USB_CSR0_DATA_END)|(1<<USB_CSR0_TX_PKT_RDY);                            // Set DataEnd and TxPktRdy bits and leave
        }
        else
            MDR_USB0->CSR0_TXCSR |= ( 1 << USB_TXCSR_TX_PKT_RDY );
        return USB_OK;
    }

    for ( i = 0; i < size; i++ )
    {
        *( char * )&MDR_USB0->FIFO[ ep ] = *( data + i );
    }

    if ( ep == 0 )
    {
        if ( dataEnd )
            MDR_USB0->CSR0_TXCSR |= ( 1 << USB_CSR0_DATA_END ) | ( 1 << USB_CSR0_TX_PKT_RDY );                 // Set DataEnd and TxPktRdy bits
        else
            MDR_USB0->CSR0_TXCSR |= ( 1 << USB_CSR0_TX_PKT_RDY );
    }
    else
    {
        ClearBit( MDR_USB0->CSR0_TXCSR, USB_TXCSR_UNDER_RUN );                                                 // Clear UnderRun
        MDR_USB0->CSR0_TXCSR |= ( 1 << USB_TXCSR_TX_PKT_RDY );
    }

    return USB_OK;
}

uint8_t USB_GetData( uint8_t ep, uint8_t *data )
{
    uint16_t dataSize;

    if ( ep == USB_EP0 )
    {
        USB_GetDataEp0( ( uint32_t* )data );
        return USB_OK;
    }

    MDR_USB0->INDEX = ep;
    
    ClearBit( MDR_USB0->RXCSR, USB_RXCSR_OVER_RUN );
    dataSize        = MDR_USB0->COUNT0_RXCOUNT;

    while ( dataSize-- )
    {
        *data++ = *( char * )&MDR_USB0->FIFO[ ep ];
    }

    ClearBit( MDR_USB0->RXCSR, USB_RXCSR_RX_PKT_RDY );

    return USB_OK;
}

/** @} */ /* End of group USB_Exported_Functions */


/** @defgroup USB_Private_Functions USB Private Functions
 * 	@{
 */

static uint32_t USB_SetPullPeriod( UsbEPCfg_t *EPCfg )
{
    switch ( EPCfg->EP_Type )
    {
    case Bulk: return 6;                                                                                       //break;
    case Control: return 20;                                                                                   //break;
    case Irq: return 10;                                                                                       //break;
    case Iso: return 150;                                                                                      //break;
    default: return 5;                                                                                         //break;
    }
}

static uint32_t power( uint32_t x, uint32_t n )
{
    /* x power of n */
    uint32_t a = 1;

    while ( n )
    {
        if ( n % 2 )
        {
            a *= x;
            n--;
        }
        else
        {
            x *= x;
            n /= 2;
        }
    }

    return a;
}

/** @} */ /* End of group USB_Private_Functions */

/** @} */ /* End of group USB */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr *********************************
*
* END OF FILE MDR1986VK01_usb.c */

