/**
  ******************************************************************************
  * @file    adc.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   ADC source file for demo board.
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
  * FILE adc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"


/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ADC BSP_ADC
  * @{
  */

/** @defgroup BSP_ADC_Exported_Functions BSP ADC Exported Functions
  * @{
  */


void AdcInitChStruct( ADC_CH_TypeDef *adcCh )
{
    uint8_t i;
    for( i = 0; i < ADC_CNV_NUM_MAX; i++ )
    {
        adcCh->ucAdc0ConvChN[ i ] = 0;
        adcCh->ucAdc0ConvChP[ i ] = 0;
        adcCh->ucAdc1ConvChN[ i ] = 0;
        adcCh->ucAdc1ConvChP[ i ] = 0;
    }

    adcCh->ucAdc0ConvCnt = 0;
    adcCh->ucAdc1ConvCnt = 0;
}

/* ADC source clock is PLL1 */
void AdcInitClk( ADCxControl *adc, uint32_t ulClk )
{
    uint16_t div;

//    div = 2000000 / ulClk;
    div = SystemCoreClock / ulClk;

    if( div )
        div--;

    MDR_BKP->KEY = 0x8555AAA1;

//    CLK_XSEConfig( CLK_HSE1, CLK_XSE_ON );
//    if( !CLK_XSEWaitReady( CLK_HSE1 ) )
//        while( 1 );

    if( !( MDR_CLK->PLL[1].CLK & (1<<17) ) )
    {
        CLK_SetPllClk( &MDR_CLK->PLL[1], PLL_CLK_HSE0, 140000000 );

        CLK_PllState( &MDR_CLK->PLL[1], ENABLE );
        if( !CLK_PLLWaitReady( &MDR_CLK->PLL[1] ) )
            while( 1 );
    }

    if( adc == MDR_ADC0 )
        MDR_CLK->ADC0_CLK = ( CLK_SOURCE_PLL1 << 28 ) | CLK_ENABLE | div;
    else if( adc == MDR_ADC1 )
        MDR_CLK->ADC1_CLK = ( CLK_SOURCE_PLL1 << 28 ) | CLK_ENABLE | div;
    else if( adc == MDR_ADC2 )
        MDR_CLK->ADC2_CLK = ( CLK_SOURCE_PLL1 << 28 ) | CLK_ENABLE | div;
}

void AdcInitBg( ADCxControl *adc )
{

    if(adc == MDR_ADC0)
        MDR_CLK->ADC0_CLK = 1<<16;
    if(adc == MDR_ADC1)
        MDR_CLK->ADC1_CLK = 1<<16;
    if(adc == MDR_ADC2)
        MDR_CLK->ADC2_CLK = 1<<16;


    MDR_ADC0->BNGP_CTRL = ANABG_IREFEN | ANABG_BGEN | ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
    //MDR_ADC0->BNGP_CTRL = ANABG_IREFEN | ANABG_BGEN | ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
//    MDR_ADC0->BNGP_CTRL = ANABG_IREFEN | ANABG_BGEN;
}

void AdcInit( ADCxControl *adc, ADC_CH_TypeDef *convCh, uint32_t freq )
{
    uint8_t i, j, ch;

    AdcInitClk( adc, freq );

    if( convCh->ucAdc0ConvCnt )
        convCh->ucAdc0ConvCnt--;

    if( convCh->ucAdc1ConvCnt )
        convCh->ucAdc1ConvCnt--;

    adc->ADCSYNCCTRL = ADC_SYNC_CTRL_OUT_DLY_ADC1( 0 ) |
                       ADC_SYNC_CTRL_MODE_ADC1( ADC_SYNC_OFF ) |
                       ADC_SYNC_CTRL_OUT_DLY_ADC0( 0 ) |
                       ADC_SYNC_CTRL_MODE_ADC0( ADC_SYNC_OFF );

    adc->ADC0CTRL = ADC_CTRL_DELAY_TIME( 1 ) |
                    ADC_CTRL_MAX_CNV( convCh->ucAdc0ConvCnt ) |
                    ADC_CTRL_CONV_TRIG( 0 ) |
//                    ADC_CTRL_CONT_CONV |
//                    ADC_CTRL_START_CONV |
                    ADC_CTRL_ENABLE;

    adc->ADC1CTRL = ADC_CTRL_DELAY_TIME( 1 ) |
                    ADC_CTRL_MAX_CNV( convCh->ucAdc1ConvCnt ) |
                    ADC_CTRL_CONV_TRIG( 0 ) |
//                    ADC_CTRL_CONT_CONV |
//                    ADC_CTRL_START_CONV |
                    ADC_CTRL_BUFEN |                                                    // Turn on the built-in reference voltage
                    ADC_CTRL_ENABLE;


    // Analog control of ADCs
//    if( diffMode )
//        adc->ANALOG_CTRL = MODE_ADC0 | MODE_ADC1;                                       // Differential mode
//    else
        adc->ANALOG_CTRL = 0;                                                           // Not differential mode

    ch = 0;

    for( i = 0; i < 8; i++ )
    {
        for( j = 0; j < 32; j+=8 )
        {
            adc->ADC0_CHNL_SEL[i] |= ( convCh->ucAdc0ConvChP[ ch ] << j ) |             // P
                                     ( convCh->ucAdc0ConvChN[ ch ] << ( j + 4 ) );      // N

            adc->ADC1_CHNL_SEL[i] |= ( convCh->ucAdc1ConvChP[ ch ] << j ) |             // P
                                     ( convCh->ucAdc1ConvChN[ ch ] << ( j + 4 ) );      // N
            ch++;
        }
    }

//    NVIC_EnableIRQ( ADC_FIFO00_IRQn );
}

void InitAdcTest( void )
{
    ADC_CH_TypeDef adcCh;
    PORT_InitTypeDef adcPort;
    PORT_StructInit( &adcPort );

    MDR_PORTC->KEY = 0x8555AAA1;
    adcPort.PORT_Pin     = ADC_PIN;
    adcPort.PORT_CANALOG = PORT_CANALOG_DIGITAL;
    adcPort.PORT_SANALOG = PORT_SANALOG_ANALOG;
    adcPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( ADC_PORT, &adcPort );

    AdcInitChStruct( &adcCh );

    AdcInitBg(TEST_ADC);
    adcCh.ucAdc0ConvChP[ 0 ] = 1;
    adcCh.ucAdc0ConvCnt = 1;

    AdcInit( TEST_ADC, &adcCh, 250000 );
}

void AdcStartConv( ADCxControl *adc )
{
    adc->ADC0CTRL |= ADC_CTRL_START_CONV;
//    adc->ADC1CTRL |= ADC_CTRL_START_CONV;
 }

void DeinitAdc( ADCxControl *adc )
{
    adc->BNGP_CTRL = 0;
    adc->ADC0CTRL = 0;
    adc->ADC1CTRL = 0;
    if(adc == MDR_ADC0)
        MDR_CLK->ADC0_CLK = 0;
    if(adc == MDR_ADC1)
        MDR_CLK->ADC1_CLK = 0;
    if(adc == MDR_ADC2)
        MDR_CLK->ADC2_CLK = 0;
}

/** @} */ /* End of group BSP_ADC_Exported_Functions */

/** @} */ /* End of group BSP_ADC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE adc.c */


