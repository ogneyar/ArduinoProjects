/**
  ******************************************************************************
  * @file    Interrupt_Example/src/main.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    02/11/2020
  * @brief   Main program body.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Includes ------------------------------------------------------------------*/
#include "csr.h"
#include <intrinsics.h>
#include "MLDR187_lib.h"
#include "MLDR187.h"
#include "interrupt.h"

#include "MLDR187_timer.h"
#include "MLDR187_gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define	LED_PORT 	MDR_PORTD
#define	LED_PORT_CLK 	RST_CLK_PORTD
#define LED_PIN_0	PORT_Pin_0
#define LED_PIN_1	PORT_Pin_1
#define LED_PIN_2	PORT_Pin_2
#define LED_PIN_3	PORT_Pin_3

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
TIMER_CntInitTypeDef sTIM_CntInit;

uint32_t SW_DelayCnt = 0;
volatile uint32_t tim_int_delay;

/* Private function prototypes -----------------------------------------------*/
void Setup_LED_Port(void);
void Setup_Timer1(void);
void Setup_Timer2(void);

/* Private functions ---------------------------------------------------------*/

/* --- */
void SysTick_Handler(void)
{
    // Set up time for next interrupt 
    MDR_CLIC_MTIMECMP_Reg = MDR_CLIC_MTIME_Reg + 32768;
    
    if (PORT_ReadPin(LED_PORT, LED_PIN_3) != 0)
          PORT_SetReset(LED_PORT, LED_PIN_3, RESET);
    else
          PORT_SetReset(LED_PORT, LED_PIN_3, SET);
}

/* --- */
void PendSV_Handler(void)
{
    PendSV_ClearPending();
    if (PORT_ReadPin(LED_PORT, LED_PIN_2) != 0)
        PORT_SetReset(LED_PORT, LED_PIN_2, RESET);
    else
        PORT_SetReset(LED_PORT, LED_PIN_2, SET);
}

/* --- */
void Timer1_IRQHandler(void)
{
    TIMER_ClearFlag(MDR_TIMER1, TIM_CNTZEROEVENT);
    if (PORT_ReadPin(LED_PORT, LED_PIN_0) != 0)
        PORT_SetReset(LED_PORT, LED_PIN_0, RESET);
    else
        PORT_SetReset(LED_PORT, LED_PIN_0, SET);
}

/* --- */
void Timer2_IRQHandler(void)
{
    tim_int_delay = MDR_TIMER2->CNT;
    TIMER_ClearFlag(MDR_TIMER2, TIM_CNTZEROEVENT);
    if (PORT_ReadPin(LED_PORT, LED_PIN_1) != 0)
        PORT_SetReset(LED_PORT, LED_PIN_1, RESET);
    else
        PORT_SetReset(LED_PORT, LED_PIN_1, SET);
}

/* Main Function */
int main()
{
    /* Global interrupt-enable */
    __enable_machine_interrupt();
    /* Set up  to point to the interrupt function */
    __write_csr(_CSR_MTVEC, (((unsigned int) IRQHandler) & 0xFFFFFFFC ));
    /* Enable external interrupts */
    enable_ExtInterrupt_EN();

    /* Disable SysTick interrupt */
    disable_SysTick_Handler();
    /* Safely set up SysTick cmp value */
    MDR_CLIC_MSIP_Reg = 0;
    MDR_CLIC_MTIMECMP_Reg = MDR_CLIC_MTIMECMP_Reg + 32768;
    /* Enable SysTick interrupt */
    enable_SysTick_Handler();
    RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
    MDR_BKP->WPR = 0x8555AAA1;
    MDR_BKP->CLK |= 0x00000003;
   
    /* Enable software interrupt */
    enable_PendSV_Handler();
       
    Setup_LED_Port();
    Setup_Timer1();
    Setup_Timer2();

    while (1)
    {
        if (SW_DelayCnt++ >= 0x00040000)
        {
            SW_DelayCnt = 0;
            PendSV_SetPending();
        }
    }
}

/* --- */
void Setup_LED_Port(void)
{
    RST_CLK_EnablePeripheralClock(LED_PORT_CLK, RST_CLK_Div1);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(LED_PORT, (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3), &PORT_InitStructure);
    PORT_SetReset(LED_PORT, LED_PIN_0, SET);
    PORT_SetReset(LED_PORT, LED_PIN_1, SET);
    PORT_SetReset(LED_PORT, LED_PIN_2, SET);
    PORT_SetReset(LED_PORT, LED_PIN_3, SET);
}

/* --- */
void Setup_Timer1(void)
{
    RST_CLK_EnablePeripheralClock(RST_CLK_TIMER1, RST_CLK_Div1);

    /* Reset all TIMER1 settings */
    TIMER_DeInit(MDR_TIMER1);

    /* Initializes the TIMERx Counter ------------------------------------*/
    sTIM_CntInit.perClkDiv                = RST_CLK_Div1;
    sTIM_CntInit.prescaler                = 0x000F;
    sTIM_CntInit.period                   = 0x0000FFFF;
    sTIM_CntInit.cntMode                  = timModeClkFixedDir;
    sTIM_CntInit.cntDirection             = timCntUp;
    sTIM_CntInit.evtSource                = timEvent_Clk;
    sTIM_CntInit.filterSampling           = timFdtsDiv1;
    sTIM_CntInit.ARRupdateMode            = timArrUpdateDelayed;
    sTIM_CntInit.ETR_FilterConf           = timFltr_1_clk;
    sTIM_CntInit.ETR_Prescaler            = timPrescaler_1;
    sTIM_CntInit.ETR_Inversion            = DISABLE;
    sTIM_CntInit.BRK_Inversion            = DISABLE;
    TIMER_Init (MDR_TIMER1,&sTIM_CntInit);

    TIMER_ItConfig(MDR_TIMER1, TIM_CNTZEROEVENT);

    PLIC_SetMinPermPriority(0);
    PLIC_ReleaseIRQ(TIM1_IRQn);
    PLIC_SetPriority(TIM1_IRQn, 1);
    PLIC_EnableIRQ(TIM1_IRQn);

    /* Enable TIMER1 */
    TIMER_Cmd(MDR_TIMER1, ENABLE);
}

/* --- */
void Setup_Timer2(void)
{
    RST_CLK_EnablePeripheralClock(RST_CLK_TIMER1, RST_CLK_Div1);

    /* Reset all TIMER2 settings */
    TIMER_DeInit(MDR_TIMER2);

    /* Initializes the TIMERx Counter ------------------------------------*/
    sTIM_CntInit.perClkDiv                = RST_CLK_Div1;
    sTIM_CntInit.prescaler                = 0;
//    sTIM_CntInit.period                   = 0x00010FFF;
    sTIM_CntInit.period                   = 0x00002FF;
    sTIM_CntInit.cntMode                  = timModeClkFixedDir;
    sTIM_CntInit.cntDirection             = timCntUp;
    sTIM_CntInit.evtSource                = timEvent_Clk;
    sTIM_CntInit.filterSampling           = timFdtsDiv1;
    sTIM_CntInit.ARRupdateMode            = timArrUpdateDelayed;
    sTIM_CntInit.ETR_FilterConf           = timFltr_1_clk;
    sTIM_CntInit.ETR_Prescaler            = timPrescaler_1;
    sTIM_CntInit.ETR_Inversion            = DISABLE;
    sTIM_CntInit.BRK_Inversion            = DISABLE;
    TIMER_Init (MDR_TIMER2,&sTIM_CntInit);

    TIMER_ItConfig(MDR_TIMER2, TIM_CNTZEROEVENT);

    PLIC_ReleaseIRQ(TIM2_IRQn);
    PLIC_SetPriority(TIM2_IRQn, 2);
    PLIC_EnableIRQ(TIM2_IRQn);

    /* Enable TIMER2 */
    TIMER_Cmd(MDR_TIMER2, ENABLE);
}

