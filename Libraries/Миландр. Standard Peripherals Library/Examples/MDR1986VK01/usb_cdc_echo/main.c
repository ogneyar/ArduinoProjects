/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.3.0
  * @date    07/04/2022
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_delay.h"

#include "adc.h"

#include "MDR1986VK01_usb_handlers.h"

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup usb_cdc_echo usb_cdc_echo
 *  @{
 */

#define CPU_CLK         50000000

#define BUFFER_LENGTH   100

static uint8_t Buffer[ BUFFER_LENGTH ];
static USB_CDC_LineCoding_TypeDef LineCoding;

extern UsbEPCfg_t RxBulkEpCgf;

static void VCom_Configuration( void );
void vErrorHandler( void );

void ClockInit()
{
    MDR_CLK->KEY      = 0x8555AAA1;
    MDR_CLK->PER0_CLK |= 1UL<<31;     // USB_CLK_EN
    MDR_CLK->PER1_CLK |= 1UL<<26;     // COMP0_CLK_EN

    MDR_COMP0->ANABG_CTRL = ANABG_IREFEN | ANABG_BGEN |
                            ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if ( !CLK_XSEWaitReady( CLK_HSE0 ) )
        vErrorHandler();

    CLK_SetPllClk( &MDR_CLK->PLL[ 0 ], PLL_CLK_HSE0, CPU_CLK );
    CLK_PllState( &MDR_CLK->PLL[ 0 ], ENABLE );
    if ( !CLK_PLLWaitReady( &MDR_CLK->PLL[ 0 ] ) )
        vErrorHandler();
    
    CLK_SetSystemClock(MAX_CLK_PLL0);

    // Настройка тактирования USB
    // На USB должно поступать 25 МГц
    MDR_CLK->USBMAC_CLK = CLK_ENABLE;
    MDR_CLK->USB0_CLK   = ( (uint32_t)CLK_SOURCE_MAX_CLK << 28 ) | CLK_ENABLE | 1;
}

int main()
{
    ClockInit();

    VCom_Configuration();
    USB_CDC_Init( Buffer, 1, SET );

    USB_DeviceInit();

    while ( 1 )
    {

    }
}

static void VCom_Configuration( void )
{
    LineCoding.dwDTERate   = 115200;
    LineCoding.bCharFormat = 0;
    LineCoding.bParityType = 0;
    LineCoding.bDataBits   = 8;
}

USB_Result USB_CDC_RecieveData( uint8_t* Buffer, uint32_t Length )
{
    USB_Result result;

    /* Send back received data portion */
    result = USB_CDC_SendData( Buffer, Length );

    return USB_SUCCESS;
}

USB_Result USB_CDC_GetLineCoding( uint16_t wINDEX, USB_CDC_LineCoding_TypeDef* DATA )
{
    assert_param( DATA );
    if ( wINDEX != 0 )
    {
        /* Invalid interface */
        return USB_ERR_INV_REQ;
    }

    /* Just store received settings */
    *DATA = LineCoding;
    return USB_SUCCESS;
}

USB_Result USB_CDC_SetLineCoding( uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef* DATA )
{
    assert_param( DATA );
    if ( wINDEX != 0 )
    {
        /* Invalid interface */
        return USB_ERR_INV_REQ;
    }

    /* Just send back settings stored earlier */
    LineCoding = *DATA;
    return USB_SUCCESS;
}

void vErrorHandler( void )
{
    while ( 1 )
    {

    }
}

void Hard_fault_handler_c( unsigned int* hardfault_args )
{
    volatile unsigned int stacked_r0;
    volatile unsigned int stacked_r1;
    volatile unsigned int stacked_r2;
    volatile unsigned int stacked_r3;
    volatile unsigned int stacked_r12;
    volatile unsigned int stacked_lr;
    volatile unsigned int stacked_pc;
    volatile unsigned int stacked_psr;

    MDR_FTMODE->KEY = 0x8555AAA1;

    if ( !( MDR_FTMODE->EVENT[ 1 ] & 0x00000099 ) )
    {
        stacked_r0 = ( ( unsigned long )hardfault_args[ 0 ] );
        stacked_r1 = ( ( unsigned long )hardfault_args[ 1 ] );
        stacked_r2 = ( ( unsigned long )hardfault_args[ 2 ] );
        stacked_r3 = ( ( unsigned long )hardfault_args[ 3 ] );

        stacked_r12 = ( ( unsigned long )hardfault_args[ 4 ] );
        stacked_lr  = ( ( unsigned long )hardfault_args[ 5 ] );
        stacked_pc  = ( ( unsigned long )hardfault_args[ 6 ] );
        stacked_psr = ( ( unsigned long )hardfault_args[ 7 ] );

        while ( 1 );
    }

    MDR_FTMODE->KEY = 0x00000000;
}

#if defined ( __ICCARM__ )
void HardFault_Handler( void )
{
    unsigned int contr_reg;


    contr_reg = __get_CONTROL();
    if ( contr_reg & 2 )
    {
        asm ( "MRS R0, PSP" );
    }
    else
    {
        asm ( "MRS R0, MSP" );
    }
    asm ( "B    (Hard_fault_handler_c)" );  // Top of stack is in R0. It is passed to C-function.
}
#endif

/** @} */ /* End of group usb_cdc_echo */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


