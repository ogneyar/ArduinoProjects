/**
  ******************************************************************************
  * @file    adcsync.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   ADCSYNC source file for demo board.
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
  * FILE adcsync.c
  */

/* Includes ------------------------------------------------------------------*/
#include "adcsync.h"

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ADCSYNC BSP_ADCSYNC
  * @{
  */

/** @defgroup BSP_ADCSYNC_Exported_Functions BSP ADCSYNC Exported Functions
  * @{
  */

//ADCxControl *adc = MDR_ADC1;

void AdcInitChStruct( ADC_CH_TypeDef *adcCh )
{
    for( uint8_t i = 0; i < ADC_CNV_NUM_MAX; i++ )
    {
        adcCh->Adc0ConvChN[ i ] = 0;
        adcCh->Adc0ConvChP[ i ] = 0;
        adcCh->Adc1ConvChN[ i ] = 0;
        adcCh->Adc1ConvChP[ i ] = 0;
    }
    
    adcCh->Adc0ConvCnt = 0;
    adcCh->Adc1ConvCnt = 0;
    adcCh->Adc0ConvTrig = 0;
    adcCh->Adc1ConvTrig = 0;
}

void AdcInitClk( ADCxControl *adc, uint8_t clkSource, uint8_t div )
{
    if( adc == MDR_ADC0 )
        MDR_CLK->ADC0_CLK = ( clkSource << 28 ) | CLK_ENABLE | div;
    else if( adc == MDR_ADC1 )
        MDR_CLK->ADC1_CLK = ( clkSource << 28 ) | CLK_ENABLE | div;
    else if( adc == MDR_ADC2 )
        MDR_CLK->ADC2_CLK = ( clkSource << 28 ) | CLK_ENABLE | div;
}

uint32_t AdcGetSampleRate( ADCxControl *adc, uint8_t adcNum )
{
    uint8_t clkSource, delay;
    uint32_t sampleRate;
    
    if( adc == MDR_ADC0 )
        clkSource = ( MDR_CLK->ADC0_CLK >> 28 ) & 0x0F;
    else if( adc == MDR_ADC1 )
        clkSource = ( MDR_CLK->ADC1_CLK >> 28 ) & 0x0F;
    else if( adc == MDR_ADC2 )
        clkSource = ( MDR_CLK->ADC2_CLK >> 28 ) & 0x0F;
    
    if( adcNum == 0 )
        delay = ( adc->ADC0CTRL >> 24 ) & 0xFF;
    else
        delay = ( adc->ADC1CTRL >> 24 ) & 0xFF;
    
    sampleRate = CLK_GetSourceClk( clkSource ) / ( 70 + delay );
    
    return sampleRate;
}

void AdcInitBg( void )
{
    MDR_ADC0->BNGP_CTRL = ANABG_IREFEN | ANABG_BGEN | ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
//    MDR_ADC0->BNGP_CTRL = ANABG_IREFEN | ANABG_BGEN;
}

void AdcInit( ADCxControl *adc, ADC_CH_TypeDef *convCh )
{
    uint8_t i, j, ch;
    
    if( convCh->Adc0ConvCnt )
        convCh->Adc0ConvCnt--;
    
    if( convCh->Adc1ConvCnt )
        convCh->Adc1ConvCnt--;
    
    adc->ADCSYNCCTRL = ADC_SYNC_CTRL_OUT_DLY_ADC1( 0 ) |
                       ADC_SYNC_CTRL_MODE_ADC1( ADC_SYNC_OFF ) |
                       ADC_SYNC_CTRL_OUT_DLY_ADC0( 0 ) |    
                       ADC_SYNC_CTRL_MODE_ADC0( ADC_SYNC_OFF );    
    
    adc->ADC0CTRL = ADC_CTRL_DELAY_TIME( 0 ) | 
                    ADC_CTRL_MAX_CNV( convCh->Adc0ConvCnt ) | 
                    ADC_CTRL_CONV_TRIG( convCh->Adc0ConvTrig ) |                                           
//                    ADC_CTRL_CONT_CONV |
//                    ADC_CTRL_START_CONV |     
                    ADC_CTRL_ENABLE;
    
    adc->ADC1CTRL = ADC_CTRL_DELAY_TIME( 0 ) | 
                    ADC_CTRL_MAX_CNV( convCh->Adc1ConvCnt ) | 
                    ADC_CTRL_CONV_TRIG( convCh->Adc1ConvTrig ) | 
//                    ADC_CTRL_CONT_CONV | 
//                    ADC_CTRL_START_CONV |    
                    ADC_CTRL_BUFEN |                                                    // Enable build-in voltage reference
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
            adc->ADC0_CHNL_SEL[i] |= ( convCh->Adc0ConvChP[ ch ] << j ) |             // P
                                     ( convCh->Adc0ConvChN[ ch ] << ( j + 4 ) );      // N 
            
            adc->ADC1_CHNL_SEL[i] |= ( convCh->Adc1ConvChP[ ch ] << j ) |             // P
                                     ( convCh->Adc1ConvChN[ ch ] << ( j + 4 ) );      // N 
            ch++;
        }
    }
   
//    NVIC_EnableIRQ( ADC_FIFO00_IRQn );
}

void AdcStartConv( ADCxControl *adc )
{
    // Запуск
    adc->ADC0CTRL |= ADC_CTRL_START_CONV;    
//    adc->ADC1CTRL |= ADC_CTRL_START_CONV;
 }

/** @} */ /* End of group BSP_ADCSYNC_Exported_Functions */

/** @} */ /* End of group BSP_ADCSYNC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE adcsync.c */


