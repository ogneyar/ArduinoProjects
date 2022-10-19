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
#include "MDR32F9Q2I_IT.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup ADC_ADC1_DMA_MDR32F9Q2I ADC_ADC1_DMA
  * @{
  */

/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;
uint16_t ADCConvertedValue[10];
DMA_ChannelInitTypeDef DMA_InitStr;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;
int tmp_reg[100];

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    RST_CLK_DeInit();
    RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSIdiv2,0);
    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_DMA | RST_CLK_PCLK_ADC),ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2),ENABLE);

    /* Disable all interrupt */
    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICER[0] = 0xFFFFFFFF;

    /* DMA Configuration */
    /* Reset all settings */
    DMA_DeInit();
    DMA_StructInit(&DMA_InitStr);
    /* Set Primary Control Data */
    DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC1_RESULT));
    DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)ADCConvertedValue;
    DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncNo;
    DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncHalfword;
    DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_PriCtrlStr.DMA_Mode = DMA_Mode_PingPong;
    DMA_PriCtrlStr.DMA_CycleSize = 10;
    DMA_PriCtrlStr.DMA_NumContinuous = DMA_Transfers_1;
    DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;

    /* Set Alternate Control Data */
    DMA_AltCtrlStr.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC1_RESULT));
    DMA_AltCtrlStr.DMA_DestBaseAddr   = (uint32_t)ADCConvertedValue;
    DMA_AltCtrlStr.DMA_SourceIncSize = DMA_SourceIncNo;
    DMA_AltCtrlStr.DMA_DestIncSize = DMA_DestIncHalfword;
    DMA_AltCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_AltCtrlStr.DMA_Mode = DMA_Mode_PingPong;
    DMA_AltCtrlStr.DMA_CycleSize = 10;
    DMA_AltCtrlStr.DMA_NumContinuous = DMA_Transfers_1;
    DMA_AltCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;

    /* Set Channel Structure */
    DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
    DMA_InitStr.DMA_AltCtrlData = &DMA_AltCtrlStr;
    DMA_InitStr.DMA_Priority = DMA_Priority_Default;
    DMA_InitStr.DMA_UseBurst = DMA_BurstClear;
    DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

    /* Init DMA channel ADC1 */
    DMA_Init(DMA_Channel_ADC1, &DMA_InitStr);

    /* Enable dma_req or dma_sreq to generate DMA request */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1<<DMA_Channel_ADC1);
    MDR_DMA->CHNL_USEBURST_CLR = (1<<DMA_Channel_ADC1);

    /* Enable DMA channel ADC1 */
    DMA_Cmd(DMA_Channel_ADC1, ENABLE);

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

    /* ADC1 Configuration */
    ADCx_StructInit (&sADCx);
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
    sADCx.ADC_ChannelNumber    = ADC_CH_TEMP_SENSOR;
    sADCx.ADC_Channels         = 0;
    sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;
    sADCx.ADC_LowLevel         = 0;
    sADCx.ADC_HighLevel        = 0;
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    sADCx.ADC_Prescaler        = ADC_CLK_div_512;
    sADCx.ADC_DelayGo          = 7;
    ADC1_Init (&sADCx);

    /* Enable ADC1 EOCIF and AWOIFEN interupts */
    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION | ADCx_IT_OUT_OF_RANGE), DISABLE);

    /* ADC1 enable */
    ADC1_Cmd(ENABLE);

    /* Enable DMA IRQ */
    NVIC_EnableIRQ(DMA_IRQn);

    while(1);
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

/** @} */ /* End of group ADC_ADC1_DMA_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


