/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    22/09/2021
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
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_adc.h"
#include "MDR32FxQI_dma.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup ADC_DMA_ping_pong_MDR32F9Q2I ADC_DMA_ping_pong
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define SIZE_BUF_ADC2      16

/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;
uint32_t ADCConvertedValue1[SIZE_BUF_ADC2];
uint32_t ADCConvertedValue2[SIZE_BUF_ADC2];

DMA_ChannelInitTypeDef DMA_InitStr_ADC2;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr_ADC2;
DMA_CtrlDataInitTypeDef DMA_AltCtrlStr_ADC2;

extern DMA_CtrlDataTypeDef DMA_ControlTable[];

/* Private functions ---------------------------------------------------------*/
void DMA_ADC2_Init(void);
void ADC2_Init_Switch(void);


void DMA_IRQHandler(void)
{
    /* Обработка канала DMA_Channel_ADC2 */
    if( !(DMA_ControlTable[DMA_Channel_ADC2].DMA_Control&0x7) || !(DMA_ControlTable[DMA_Channel_ADC2 + 32].DMA_Control&0x7) )
    {
        /* Reconfigure the inactive DMA data structure*/
        if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_ADC2)) == (0<<DMA_Channel_ADC2))     // Сейчас выполняется основная структура
        {
            DMA_CtrlDataInit(&DMA_AltCtrlStr_ADC2, &DMA_ControlTable[DMA_Channel_ADC2 + 32]);
        }
        else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_ADC2)) == (1<<DMA_Channel_ADC2)) // Сейчас выполняется альтернативная структура
        {
            DMA_CtrlDataInit(&DMA_PriCtrlStr_ADC2, &DMA_ControlTable[DMA_Channel_ADC2]);
        }
    }
}

int main(void)
{
    /* ADC2 and DMA Init */
    DMA_ADC2_Init();
    ADC2_Init_Switch();
    NVIC_EnableIRQ(DMA_IRQn);

    /* ADC2 enable */
    ADC2_Cmd (ENABLE);

    while(1);
}


void DMA_ADC2_Init(void)
{
    RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

    /* DMA Configuration */
    /* Reset all settings */
    DMA_DeInit();

    DMA_StructInit(&DMA_InitStr_ADC2);
    /* Set Primary Control Data */
    DMA_PriCtrlStr_ADC2.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC2_RESULT));
    DMA_PriCtrlStr_ADC2.DMA_DestBaseAddr = (uint32_t)ADCConvertedValue1;
    DMA_PriCtrlStr_ADC2.DMA_SourceIncSize = DMA_SourceIncNo;
    DMA_PriCtrlStr_ADC2.DMA_DestIncSize = DMA_DestIncWord;
    DMA_PriCtrlStr_ADC2.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_PriCtrlStr_ADC2.DMA_Mode = DMA_Mode_PingPong;
    DMA_PriCtrlStr_ADC2.DMA_CycleSize = SIZE_BUF_ADC2;
    DMA_PriCtrlStr_ADC2.DMA_NumContinuous = DMA_Transfers_1;
    DMA_PriCtrlStr_ADC2.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr_ADC2.DMA_DestProtCtrl = DMA_DestPrivileged;

    /* Set Alternate Control Data */
    DMA_AltCtrlStr_ADC2.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC2_RESULT));
    DMA_AltCtrlStr_ADC2.DMA_DestBaseAddr   = (uint32_t)ADCConvertedValue2;
    DMA_AltCtrlStr_ADC2.DMA_SourceIncSize  = DMA_SourceIncNo;
    DMA_AltCtrlStr_ADC2.DMA_DestIncSize    = DMA_DestIncWord;
    DMA_AltCtrlStr_ADC2.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_AltCtrlStr_ADC2.DMA_Mode           = DMA_Mode_PingPong;
    DMA_AltCtrlStr_ADC2.DMA_CycleSize      = SIZE_BUF_ADC2;
    DMA_AltCtrlStr_ADC2.DMA_NumContinuous  = DMA_Transfers_1;
    DMA_AltCtrlStr_ADC2.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr_ADC2.DMA_DestProtCtrl  = DMA_DestPrivileged;

    /* Set Channel Structure */
    DMA_InitStr_ADC2.DMA_PriCtrlData = &DMA_PriCtrlStr_ADC2;
    DMA_InitStr_ADC2.DMA_AltCtrlData = &DMA_AltCtrlStr_ADC2;
    DMA_InitStr_ADC2.DMA_Priority = DMA_Priority_Default;
    DMA_InitStr_ADC2.DMA_UseBurst = DMA_BurstClear;
    DMA_InitStr_ADC2.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

    /* Init DMA channel ADC2 */
    DMA_Init(DMA_Channel_ADC2, &DMA_InitStr_ADC2);

    /* Enable dma_req or dma_sreq to generate DMA request */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1<<DMA_Channel_ADC2);
    MDR_DMA->CHNL_USEBURST_CLR = (1<<DMA_Channel_ADC2);

    /* Enable DMA channel ADC2 */
    DMA_Cmd(DMA_Channel_ADC2, ENABLE);
}

void ADC2_Init_Switch(void)
{
    RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC | RST_CLK_PCLK_PORTD, ENABLE); 

    /* ADC Configuration */
    /* Reset all ADC settings */
    ADC_DeInit();
    ADC_StructInit(&sADC);

    sADC.ADC_SynchronousMode      = ADC_SyncMode_Independent;
    sADC.ADC_StartDelay           = 0;
    sADC.ADC_TempSensor           = ADC_TEMP_SENSOR_Enable;
    sADC.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Enable;
    sADC.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Enable;
    sADC.ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;
    sADC.ADC_IntVRefTrimming      = 1;
    ADC_Init (&sADC);

    /* ADC2 Configuration */
    ADCx_StructInit (&sADCx);
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC7;
    sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;
    sADCx.ADC_LowLevel         = 0;
    sADCx.ADC_HighLevel        = 0;
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    sADCx.ADC_Prescaler        = ADC_CLK_div_256;
    sADCx.ADC_DelayGo          = 3;
    ADC2_Init (&sADCx);
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group ADC_DMA_ping_pong_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


