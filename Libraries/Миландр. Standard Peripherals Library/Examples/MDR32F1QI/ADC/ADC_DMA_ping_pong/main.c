/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    21/09/2021
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
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_adc.h"
#include "MDR32FxQI_dma.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 *  @{
 */

/** @addtogroup ADC_DMA_ping_pong_MDR32F1QI ADC_DMA_ping_pong
 *  @{
 */

/* Private define ------------------------------------------------------------*/
#define SIZE_BUF_ADC      16

/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;
uint32_t ADCConvertedValue1[SIZE_BUF_ADC] __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
uint32_t ADCConvertedValue2[SIZE_BUF_ADC] __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

DMA_ChannelInitTypeDef DMA_InitStr_ADC;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr_ADC;
DMA_CtrlDataInitTypeDef DMA_AltCtrlStr_ADC;

extern DMA_CtrlDataTypeDef DMA_ControlTable[];

/* Private function prototypes -----------------------------------------------*/
void DMA_ADC1_Init(void);
void ADC1_Init_Switch(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  DMA interrupt handler.
  * @param  None
  * @retval None
  */
void DMA_IRQHandler(void)
{
    if( !(DMA_ControlTable[DMA_Channel_SREQ_ADCDMA].DMA_Control&0x7) || !(DMA_ControlTable[DMA_Channel_SREQ_ADCDMA + 32].DMA_Control&0x7) )
    {
        if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_SREQ_ADCDMA)) == (0<<DMA_Channel_SREQ_ADCDMA))     // The main structure is now in progress
        {
            DMA_CtrlDataInit(&DMA_AltCtrlStr_ADC, &DMA_ControlTable[DMA_Channel_SREQ_ADCDMA + 32]);
        }
        else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_SREQ_ADCDMA)) == (1<<DMA_Channel_SREQ_ADCDMA)) // The alternative structure is now in progress
        {
            DMA_CtrlDataInit(&DMA_PriCtrlStr_ADC, &DMA_ControlTable[DMA_Channel_SREQ_ADCDMA]);
        }
    }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* ADC1 and DMA Init */
    DMA_ADC1_Init();
    ADC1_Init_Switch();
    NVIC_EnableIRQ(DMA_IRQn);

    /* ADC1 enable */
    ADC1_Cmd(ENABLE);

    while(1);
}

/**
  * @brief  DMA channel ADC1 initialization.
  * @param  None
  * @retval None
  */
void DMA_ADC1_Init(void)
{
    RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

    /* DMA Configuration */
    /* Reset all settings */
    DMA_DeInit();

    DMA_StructInit(&DMA_InitStr_ADC);
    /* Set Primary Control Data */
    DMA_PriCtrlStr_ADC.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC1_RESULT));
    DMA_PriCtrlStr_ADC.DMA_DestBaseAddr = (uint32_t)ADCConvertedValue1;
    DMA_PriCtrlStr_ADC.DMA_SourceIncSize = DMA_SourceIncNo;
    DMA_PriCtrlStr_ADC.DMA_DestIncSize = DMA_DestIncWord;
    DMA_PriCtrlStr_ADC.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_PriCtrlStr_ADC.DMA_Mode = DMA_Mode_PingPong;
    DMA_PriCtrlStr_ADC.DMA_CycleSize = SIZE_BUF_ADC;
    DMA_PriCtrlStr_ADC.DMA_NumContinuous = DMA_Transfers_1;
    DMA_PriCtrlStr_ADC.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr_ADC.DMA_DestProtCtrl = DMA_DestPrivileged;

    /* Set Alternate Control Data */
    DMA_AltCtrlStr_ADC.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC1_RESULT));
    DMA_AltCtrlStr_ADC.DMA_DestBaseAddr   = (uint32_t)ADCConvertedValue2;
    DMA_AltCtrlStr_ADC.DMA_SourceIncSize = DMA_SourceIncNo;
    DMA_AltCtrlStr_ADC.DMA_DestIncSize = DMA_DestIncWord;
    DMA_AltCtrlStr_ADC.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_AltCtrlStr_ADC.DMA_Mode = DMA_Mode_PingPong;
    DMA_AltCtrlStr_ADC.DMA_CycleSize = SIZE_BUF_ADC;
    DMA_AltCtrlStr_ADC.DMA_NumContinuous = DMA_Transfers_1;
    DMA_AltCtrlStr_ADC.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr_ADC.DMA_DestProtCtrl = DMA_DestPrivileged;

    /* Set Channel Structure */
    DMA_InitStr_ADC.DMA_PriCtrlData = &DMA_PriCtrlStr_ADC;
    DMA_InitStr_ADC.DMA_AltCtrlData = &DMA_AltCtrlStr_ADC;
    DMA_InitStr_ADC.DMA_Priority = DMA_Priority_Default;
    DMA_InitStr_ADC.DMA_UseBurst = DMA_BurstClear;
    DMA_InitStr_ADC.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

    /* Init DMA channel ADC1 */
    DMA_Init(DMA_Channel_SREQ_ADCDMA, &DMA_InitStr_ADC);

    /* Enable dma_req or dma_sreq to generate DMA request */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1<<DMA_Channel_SREQ_ADCDMA);  
    MDR_DMA->CHNL_USEBURST_CLR = (1<<DMA_Channel_SREQ_ADCDMA);

    /* Enable DMA channel ADC1 */
    DMA_Cmd(DMA_Channel_SREQ_ADCDMA, ENABLE);
}

/**
  * @brief  ADC1 initialization.
  * @param  None
  * @retval None
  */
void ADC1_Init_Switch(void)
{
    RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC | RST_CLK_PCLK_PORTD, ENABLE); 

    /* ADC Configuration */
    /* Reset all ADC settings */
    ADC_DeInit();
    ADC_StructInit(&sADC);

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
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC2;
    sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;
    sADCx.ADC_LowLevel         = 0;
    sADCx.ADC_HighLevel        = 0;
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    sADCx.ADC_Prescaler        = ADC_CLK_div_256;
    sADCx.ADC_DelayGo          = 3;
    ADC1_Init (&sADCx);
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

/** @} */ /* End of group ADC_DMA_ping_pong_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


