/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.1.0
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
#include "MDR1986VK01_dma.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_timer.h"
#include "demoboard.h"
#include "dac.h"
#include "adc.h"


#include <string.h>
#include <stdlib.h>
#include <math.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup dma_pingpong dma_pingpong
 *  @{
 */

#define DAC_EN_A                    (1 << 0)
#define DAC_EN_D                    (1 << 1)

#define DAC_REF_VDD                 (0 << 2)
#define DAC_REF_VREF0               (1 << 2)
#define DAC_REF_VREF1               (2 << 2)
#define DAC_REF_VREF                (3 << 2)

#define DAC_MODE_SINGLE             (0 << 4)
#define DAC_MODE_FIFO               (1 << 4)
#define DAC_MODE_FIFO_EX_SYNC       (2 << 4)

#define DAC_RST                     (1 << 8)

#define DAC_OUT_2V5                 3100

#define DAC_DATA_SIZE               32000
#define DAC_TEST_FREQ               1000.0F

#define M_PI                        3.1415926535897932384626433832795F

#define CCR2_Val 5
#define DMA_SELECT(CHANNEL)	(0x00000001<<(CHANNEL))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
TIMER_CntInitTypeDef sTIM_CntInit;
TIMER_ChnInitTypeDef sTIM_ChnInit;
TIMER_ChnOutInitTypeDef sTIM_ChnOutInit;


DMA_ChannelInitTypeDef DMA_InitStr;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

volatile uint32_t ch = 0;
volatile uint32_t c = 0;

uint32_t dat;
uint32_t tmpDac0 = 0;

uint32_t tmptim = 0;

uint16_t SinDAC[32] = { 2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056,
                        4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
                        2047, 1647, 1263,  909,  599,  344,  155,   38,
                           0,   38,  155,  344,  599,  909, 1263, 1647};

uint16_t SinDAC2[32] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
                        4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
                        4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
                        4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void POR_disable(void);
void KEY_reg_accs(void);


void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_COMP0->ANABG_CTRL= ANABG_IREFEN | ANABG_BGEN | 
                     ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );

    
    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
//    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
//        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
//        while(1){}

    CLK_SetSystemClock( MAX_CLK_HSE0 );

}

static void vShifterInit( void )
{
    PORT_InitTypeDef ShifterPort;
    PORT_StructInit( &ShifterPort );
    
    MDR_PORTA->KEY = 0x8555AAA1;
    
    ShifterPort.PORT_Pin     = PORT_Pin_31;
    ShifterPort.PORT_SOE     = PORT_SOE_OUT;
    ShifterPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    ShifterPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ShifterPort.PORT_SPWR    = PORT_SPWR_10;
    
    PORT_Init( MDR_PORTA, &ShifterPort );
    
    BUF_OE_OFF;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
    uint32_t per;
    
    ClockInit();

//	/*PORT configuration*/
//	PORT_InitStructure.PORT_Pin   = (PORT_Pin_25);
//	PORT_InitStructure.PORT_CPULLUP  = PORT_CPULLUP_ON;
//  PORT_InitStructure.PORT_CANALOG  = PORT_CANALOG_DIGITAL;
//  PORT_Init(MDR_PORTC, &PORT_InitStructure);
    
    /* DMA Configuration */
    /* Reset all DMA settings */
    DMA_DeInit();
    DMA_StructInit(&DMA_InitStr);
    /* Set Primary Control Data */
    DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)SinDAC;
    DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)(&(MDR_DAC2->DATA));
    DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncHalfword;
    DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncNo;
    DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_PriCtrlStr.DMA_Mode = DMA_Mode_PingPong;
    DMA_PriCtrlStr.DMA_CycleSize = 32;
    DMA_PriCtrlStr.DMA_NumContinuous = DMA_Transfers_1;
    DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;
    /* Set Alternate Control Data */
    DMA_AltCtrlStr.DMA_SourceBaseAddr = (uint32_t)SinDAC2;
    DMA_AltCtrlStr.DMA_DestBaseAddr   = (uint32_t)(&(MDR_DAC2->DATA));
    DMA_AltCtrlStr.DMA_SourceIncSize = DMA_SourceIncHalfword;
    DMA_AltCtrlStr.DMA_DestIncSize = DMA_DestIncNo;
    DMA_AltCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_AltCtrlStr.DMA_Mode = DMA_Mode_PingPong;
    DMA_AltCtrlStr.DMA_CycleSize = 32;
    DMA_AltCtrlStr.DMA_NumContinuous = DMA_Transfers_1;
    DMA_AltCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;
    /* Set Channel Structure */
    DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
    DMA_InitStr.DMA_AltCtrlData = &DMA_AltCtrlStr;
    DMA_InitStr.DMA_Priority = DMA_Priority_Default;
    DMA_InitStr.DMA_UseBurst = DMA_BurstClear;
    DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_ALTERNATE;
    
    DMA_Init( 0, &DMA_InitStr );
    
    /* Enable dma_req or dma_sreq to generate DMA request */
    MDR_DMA->CHNL_REQ_MASK_CLR = 1;
    MDR_DMA->CHNL_USEBURST_CLR = 1;

    
    per = SystemCoreClock / 32000;
    
    MDR_DAC1->DATA = 0;
    MDR_DAC1->PRD = per;
    MDR_DAC1->CTRL = DAC_EN_A | DAC_EN_D | DAC_REF_VREF;// | DAC_MODE_FIFO;

    MDR_DAC2->DATA = 0;
    MDR_DAC2->PRD = per;
    MDR_DAC2->CTRL = DAC_EN_A | DAC_EN_D | DAC_REF_VREF;// | DAC_MODE_FIFO;

    // TIM_CLK_en(TIM1, TIM_CLKdiv1);

    MDR_CLK->TIM1_CLK = (1 << 16);

    /* TIMER1 Configuration */
    /* Time base configuration */
    TIMER_DeInit(MDR_TIMER1);
    //TIM_CLK_en(TIM1, TIM_CLKdiv1);
    sTIM_CntInit.TIMER_Prescaler                = 0;
    sTIM_CntInit.TIMER_Period                   = 0xFF;
    sTIM_CntInit.TIMER_CounterMode              = TIMER_CntMode_ClkFixedDir;
    sTIM_CntInit.TIMER_CounterDirection         = TIMER_CntDir_Up;
    sTIM_CntInit.TIMER_EventSource              = TIMER_EvSrc_None;
    sTIM_CntInit.TIMER_FilterSampling           = TIMER_FDTS_TIMER_CLK_div_1;
    sTIM_CntInit.TIMER_ARR_UpdateMode           = TIMER_ARR_Update_Immediately;
    sTIM_CntInit.TIMER_ETR_FilterConf           = TIMER_Filter_1FF_at_TIMER_CLK;
    sTIM_CntInit.TIMER_ETR_Prescaler            = TIMER_ETR_Prescaler_None;
    sTIM_CntInit.TIMER_ETR_Polarity             = TIMER_ETRPolarity_NonInverted;
    sTIM_CntInit.TIMER_BRK_Polarity             = TIMER_BRKPolarity_NonInverted;
    TIMER_CntInit (MDR_TIMER1,&sTIM_CntInit);
    
    /* Enable DMA for TIMER1 */
    TIMER_DMACmd(MDR_TIMER1,(TIMER_STATUS_CNT_ARR), TIMER_DMA_Channel0, ENABLE);
    
    /* TIMER1 enable counter */
    TIMER_Cmd(MDR_TIMER1,ENABLE);
    
    DMA_SetChannelRequest( 0, DMA_Channel_REQ_TIM1_0 );
    
    DMA_Cmd( 0, ENABLE );
    NVIC_ClearPendingIRQ( DMA_DONE0_IRQn );
    NVIC_EnableIRQ( DMA_DONE0_IRQn );
    
    /*Main cycle*/
    while (1){
        tmptim = MDR_TIMER1->CNT;
    }

}

/** @} */ /* End of group dma_pingpong */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


