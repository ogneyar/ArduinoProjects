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
  * <h2><center>&copy; COPYRIGHT 2022 Milandr </center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_dac.h"
#include "MDR32FxQI_timer.h"
#include "MDR32FxQI_dma.h"
#include "MDR32F1QI_IT.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup DAC_DMA_SineWave_MDR32F1QI DAC_DMA_SineWave
  * @{
  */

/* Private macro -------------------------------------------------------------*/
#define DMA_SELECT(CHANNEL)    (0x00000001<<(CHANNEL))

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
TIMER_CntInitTypeDef sTIM_CntInit;
DMA_ChannelInitTypeDef DMA_InitStr;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;


uint16_t Sine12bit[32] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) = {
    2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
    939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
    99, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647
};

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
    SystemCoreClockUpdate();
    /* Enable peripheral clocks ----------------------------------------------*/
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_DMA | RST_CLK_PCLK_PORTE),ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_TIMER1 | RST_CLK_PCLK_DAC),ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2),ENABLE);

    /* Disable all interrupt */
    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICER[0] = 0xFFFFFFFF;

    /* Reset PORTE settings */
    PORT_DeInit(MDR_PORTE);

    /* Configure DAC pin: DAC1_OUT */
    /* Configure PORTE pin 9 */
    PORT_InitStructure.PORT_Pin  = PORT_Pin_2;
    PORT_InitStructure.PORT_OE   = PORT_OE_OUT;
    PORT_InitStructure.PORT_MODE = PORT_MODE_ANALOG;
    PORT_Init(MDR_PORTE, &PORT_InitStructure);

    /* DMA Configuration */
    /* Reset all DMA settings */
    DMA_DeInit();
    DMA_StructInit(&DMA_InitStr);
    /* Set Primary Control Data */
    DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)Sine12bit;
    DMA_PriCtrlStr.DMA_DestBaseAddr   = (uint32_t)(&(MDR_DAC->DAC1_DATA));
    DMA_PriCtrlStr.DMA_SourceIncSize  = DMA_SourceIncHalfword;
    DMA_PriCtrlStr.DMA_DestIncSize    = DMA_DestIncNo;
    DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_PriCtrlStr.DMA_Mode           = DMA_Mode_PingPong;
    DMA_PriCtrlStr.DMA_CycleSize      = 32;
    DMA_PriCtrlStr.DMA_NumContinuous  = DMA_Transfers_1;
    DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr.DMA_DestProtCtrl   = DMA_DestPrivileged;
    /* Set Alternate Control Data */
    DMA_AltCtrlStr.DMA_SourceBaseAddr = (uint32_t)Sine12bit;
    DMA_AltCtrlStr.DMA_DestBaseAddr   = (uint32_t)(&(MDR_DAC->DAC1_DATA));
    DMA_AltCtrlStr.DMA_SourceIncSize  = DMA_SourceIncHalfword;
    DMA_AltCtrlStr.DMA_DestIncSize    = DMA_DestIncNo;
    DMA_AltCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_AltCtrlStr.DMA_Mode           = DMA_Mode_PingPong;
    DMA_AltCtrlStr.DMA_CycleSize      = 32;
    DMA_AltCtrlStr.DMA_NumContinuous  = DMA_Transfers_1;
    DMA_AltCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr.DMA_DestProtCtrl   = DMA_DestPrivileged;
    /* Set Channel Structure */
    DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
    DMA_InitStr.DMA_AltCtrlData = &DMA_AltCtrlStr;
    DMA_InitStr.DMA_Priority    = DMA_Priority_Default;
    DMA_InitStr.DMA_UseBurst    = DMA_BurstClear;
    DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

    /* Init DMA channel TIM1*/
    DMA_Init(DMA_Channel_REQ_TIM1, &DMA_InitStr);

    /* Enable dma_req or dma_sreq to generate DMA request */
    MDR_DMA->CHNL_REQ_MASK_CLR = DMA_SELECT(DMA_Channel_REQ_TIM1);
    MDR_DMA->CHNL_USEBURST_CLR = DMA_SELECT(DMA_Channel_REQ_TIM1);

    /* Enable DMA_Channel_TIM1 */
    DMA_Cmd(DMA_Channel_REQ_TIM1, ENABLE);

    /* ADC Configuration */
    /* Reset all ADC settings */
    DAC_DeInit();
    /* DAC channel1 Configuration */
    DAC1_Init(DAC1_AVCC);
    /* DAC channel1 enable */
    DAC1_Cmd(ENABLE);

    /* TIMER1 Configuration */
    /* Time base configuration */
    TIMER_DeInit(MDR_TIMER1);
    TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv1);
    sTIM_CntInit.TIMER_Prescaler        = 0;
    sTIM_CntInit.TIMER_Period           = 0xFF;
    sTIM_CntInit.TIMER_CounterMode      = TIMER_CntMode_ClkFixedDir;
    sTIM_CntInit.TIMER_CounterDirection = TIMER_CntDir_Up;
    sTIM_CntInit.TIMER_EventSource      = TIMER_EvSrc_TIM_CLK;
    sTIM_CntInit.TIMER_FilterSampling   = TIMER_FDTS_TIMER_CLK_div_1;
    sTIM_CntInit.TIMER_ARR_UpdateMode   = TIMER_ARR_Update_Immediately;
    sTIM_CntInit.TIMER_ETR_FilterConf   = TIMER_Filter_1FF_at_TIMER_CLK;
    sTIM_CntInit.TIMER_ETR_Prescaler    = TIMER_ETR_Prescaler_None;
    sTIM_CntInit.TIMER_ETR_Polarity     = TIMER_ETRPolarity_NonInverted;
    sTIM_CntInit.TIMER_BRK_Polarity     = TIMER_BRKPolarity_NonInverted;
    TIMER_CntInit (MDR_TIMER1,&sTIM_CntInit);

    /* Enable DMA for TIMER1 */
    TIMER_DMACmd(MDR_TIMER1, TIMER_STATUS_CNT_ARR, TIMER_DMA_Channel0, ENABLE);

    /* TIMER1 enable counter */
    TIMER_Cmd(MDR_TIMER1,ENABLE);

    /* Enable DMA IRQ */
    NVIC_EnableIRQ(DMA_IRQn);

    /* Infinite loop */
    while(1)
    {
    }
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

/** @} */ /* End of group DAC_DMA_SineWave_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


