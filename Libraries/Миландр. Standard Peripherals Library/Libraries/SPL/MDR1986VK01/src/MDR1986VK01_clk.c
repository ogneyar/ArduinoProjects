/**
  ******************************************************************************
  * @file    MDR1986VK01_clk.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   This file contains all the CLKCTRL firmware functions.
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
  * FILE MDR1986VK01_clk.c
  */


/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup CLK CLK
  * @{
  */

/** @defgroup CLK_Private_Constants CAN Private Constants
  * @{
  */

#define MIN_PLL_INT_CLK             150000000UL
#define MAX_PLL_INT_CLK             300000000UL

/** @} */ /* End of group CLK_Private_Constants */

/** @defgroup CLK_Private_Function_Prototypes CLK Private Function Prototypes
 * 	@{
 */

static uint32_t CLK_MaxClkGetClock( void );
static uint32_t CLK_PLLGetClock( MDR_CLK_TypeDef *pll );
static uint32_t CLK_PLLGetSourceClk( uint8_t source );

/** @} */ /* End of group CLK_Private_Function_Prototypes */

/** @defgroup CLK_Exported_Functions CLK Exported Functions
 * 	@{
 */

uint32_t CLK_GetSourceClk( uint8_t source )
{
    uint32_t clock = 0;

    switch( source )
    {
    case CLK_SOURCE_HSI:
        clock = HSI_Value;
        break;
    case CLK_SOURCE_HSE0:
        if( ( MDR_BKP->REG_63_CLK0 & ( 1 << CLK_HSE0 * 4 ) ) )
            clock = HSE0_Value;
        break;
    case CLK_SOURCE_HSE1:
        if( ( MDR_BKP->REG_63_CLK0 & ( 1 << CLK_HSE1 * 4 ) ) )
            clock = HSE1_Value;
        break;
    case CLK_SOURCE_LSI:
        clock = LSI_Value;
        break;
    case CLK_SOURCE_LSE:
        if( ( MDR_BKP->REG_63_CLK0 & ( 1 << CLK_LSE * 4 ) ) )
            clock = LSE_Value;
        break;
    case CLK_SOURCE_PLL0:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[0] );
        break;
    case CLK_SOURCE_PLL1:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[1] );
        break;
    case CLK_SOURCE_PLL2:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[2] );
        break;
    case CLK_SOURCE_PLL3:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[3] );
        break;
    case CLK_SOURCE_MAX_CLK:
        clock = CLK_MaxClkGetClock();
        break;
    default:
        clock = 0;
    }

    return clock;
}

void CLK_XSEConfig( uint32_t xse, uint32_t state )
{
    switch( xse )
    {
    case CLK_LSE:
        MDR_BKP->REG_63_CLK0 &= ~( 0xF << 0 );
        MDR_BKP->REG_63_CLK0 |= state << 0;
        break;
    case CLK_HSE0:
        MDR_BKP->REG_63_CLK0 &= ~( 0xF << 4 );
        MDR_BKP->REG_63_CLK0 |= state << 4;
        break;
    case CLK_HSE1:
        MDR_BKP->REG_63_CLK0 &= ~( 0xF << 8 );
        MDR_BKP->REG_63_CLK0 |= state << 8;
        break;
    default:
        break;
    }
}

uint32_t CLK_XSEWaitReady( uint32_t xse )
{
    uint32_t timeout = 10000000;

    while( !( MDR_BKP->REG_63_CLK0 & ( 1 << xse * 4 ) ) && timeout )
        timeout--;

    if( timeout )
        return 1;
    else
        return 0;
}

uint32_t CLK_SetPllClk( MDR_CLK_TypeDef *pll, uint8_t source, uint32_t clock )
{
    uint32_t sourceClk, refClk;
    uint16_t n = 0;
    uint8_t dv, q = 0;

    if( ( clock * 4 >= MIN_PLL_INT_CLK)  && ( clock * 4 <= MAX_PLL_INT_CLK ) )
        dv = PLL_DV_4;
    else if( ( clock * 2 >= MIN_PLL_INT_CLK)  && ( clock * 2 <= MAX_PLL_INT_CLK ) )
        dv = PLL_DV_2;
    else if( ( clock >= MIN_PLL_INT_CLK )  && ( clock <= MAX_PLL_INT_CLK ) )
        dv = PLL_DV_NONE;
    else
        return 0;

    sourceClk = CLK_PLLGetSourceClk( source );

    clock *= 1 << dv;

    do
    {
        q++;
        refClk = sourceClk / q;
    }while( ( clock % refClk ) && ( q < 31 ) );

    if( q > 31 )
        return 0;

    n = clock / refClk;

    if( n > 299 )
        return 0;

    CLK_PllConfig( pll, source, n, q, dv );

    return ( refClk * n ) / ( 1 << dv );
}

void CLK_PllConfig( MDR_CLK_TypeDef *pll, uint32_t source, uint16_t n, uint8_t q, uint8_t dv )
{
    n--;
    q--;

    pll->CLK &= ~0x1FFFFF;
    pll->CLK |= ( ( source & 0x7 ) << 18 ) | ( ( dv & 0x3 ) << 14 ) | ( ( n & 0x1FF ) << 5 ) | ( q & 0x1F );
}

void CLK_PllState( MDR_CLK_TypeDef *pll, FunctionalState NewState )
{
	if(NewState == ENABLE)
    {
		pll->CLK |= 1<<17;
	}
	else
    {
		pll->CLK &= ~(1<<17);
	}
}

uint32_t CLK_PLLWaitReady( MDR_CLK_TypeDef *pll )
{
    uint32_t timeout = 10000000;

    while( !( pll->STAT & 0x100000 ) && timeout )
    {
        timeout--;
    }

    if( timeout )
        return 1;
    else
        return 0;
}

uint32_t CLK_PLLGetSourceClk( uint8_t source )
{
    uint32_t clock;

    switch( source )
    {
    case PLL_CLK_HSI:
        clock = HSI_Value;
        break;
    case PLL_CLK_HSI_DV2:
        clock = HSI_Value / 2;
        break;
    case PLL_CLK_HSE0:
        clock = HSE0_Value;
        break;
    case PLL_CLK_HSE0_DV2:
        clock = HSE0_Value / 2;
        break;
    case PLL_CLK_HSE1:
        clock = HSE1_Value;
        break;
    case PLL_CLK_HSE1_DV2:
        clock = HSE1_Value / 2;
        break;
    }

    return clock;
}

uint32_t CLK_PLLGetClock( MDR_CLK_TypeDef *pll )
{
    uint8_t source, q, n, dv;
    uint32_t clock;

    if( !( pll->STAT & 0x100000 ) )
        return 0;

    source = ( pll->CLK >> 18 ) & 0x7;
    q = ( pll->CLK & 0x1F ) + 1;
    n = ( ( pll->CLK >> 5 ) & 0x1FF ) + 1;
    dv = ( ( pll->CLK >> 14 ) & 0x3 );

    clock = CLK_PLLGetSourceClk( source );
    clock = ( ( clock * n ) / q ) / ( 1 << dv );

    return clock;
}

uint32_t CLK_MaxClkGetClock( void )
{
    uint8_t source;
    uint32_t clock;

    source = MDR_CLK->MAX_CLK & 0xF;

    switch( source )
    {
    case MAX_CLK_HSI:
        clock = HSI_Value;
        break;
    case MAX_CLK_HSI_DV2:
        clock = HSI_Value / 2;
        break;
    case MAX_CLK_HSE0:
        clock = HSE0_Value;
        break;
    case MAX_CLK_HSE0_DV2:
        clock = HSE0_Value / 2;
        break;
    case MAX_CLK_HSE1:
        clock = HSE1_Value;
        break;
    case MAX_CLK_HSE1_DV2:
        clock = HSE1_Value / 2;
        break;
    case MAX_CLK_LSI:
        clock = LSI_Value;
        break;
    case MAX_CLK_LSE:
        clock = LSE_Value;
        break;
    case MAX_CLK_PLL0:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[0] );
        break;
    case MAX_CLK_PLL1:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[1] );
        break;
    case MAX_CLK_PLL2:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[2] );
        break;
    case MAX_CLK_PLL3:
        clock = CLK_PLLGetClock( &MDR_CLK->PLL[3] );
        break;
    }

    return clock;
}

void CLK_SetSystemClock( uint8_t maxClkSource )
{
    MDR_CLK->MAX_CLK = maxClkSource;
    SystemCoreClock = CLK_MaxClkGetClock();
}

/** @} */ /* End of group CLK_Exported_Functions */

/** @} */ /* End of group CLK */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr *********************************
*
* END OF FILE MDR1986VK01_clk.c */


