/**
  ******************************************************************************
  * @file    MDR32FG16S1QI_IT.c
  * @author  Milandr Application Team
  * @version V2.0.0i
  * @date    14/03/2022
  * @brief   Main Interrupt Service Routines for MPU MDR32FG16S1QI.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FG16S1QI_IT.h"

#if defined (USE_MDR32FG16S1QI)

#if defined (_USE_DEBUG_UART_)

    /* Private macro ---------------------------------------------------------*/
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)

    /* Private function prototypes -------------------------------------------*/
    void Hard_fault_handler_c(unsigned int* hardfault_args);

#endif /* #if defined (_USE_DEBUG_UART_) */

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
#if defined (_USE_DEBUG_UART_)
    unsigned int contr_reg;
    contr_reg = __get_CONTROL();
    if(contr_reg & 2)
    {
#if defined ( __CMCARM__ )
        __ASM MRS R0, PSP;
#else
        __ASM("MRS R0, PSP");
#endif
    }
    else
    {
#if defined ( __CMCARM__ )
        __ASM MRS R0, MSP;
#else
        __ASM("MRS R0, MSP");
#endif
    }
    //top of stack is in R0. It is passed to C-function.
#if defined ( __CMCARM__ )
    __ASM BL (Hard_fault_handler_c);
#else
    __ASM("BL (Hard_fault_handler_c)");
#endif

#endif /* #if defined (_USE_DEBUG_UART_) */

    /* Go to infinite loop when Hard Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : MemoryManagement_Handler
* Description    : This function handles MemoryManagementFault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemoryManagement_Handler(void)
{
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles BusFault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles UsageFault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SVCall_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCall_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles Debug PendSV exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SSP3_IRQHandler
* Description    : This function handles SSP3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SSP4_IRQHandler
* Description    : This function handles SSP4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : MCBSP1_IRQHandler
* Description    : This function handles MCBSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MCBSP1_IRQHandler(void)
{
}

/*******************************************************************************

* Function Name  : MCBSP2_IRQHandler
* Description    : This function handles MCBSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MCBSP2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : MCBSP3_IRQHandler
* Description    : This function handles MCBSP3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MCBSP3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C_IRQHandler
* Description    : This function handles I2C global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : POWER_IRQHandler
* Description    : This function handles POWER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void POWER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA_DSP_IRQHandler
* Description    : This function handles DMA_DSP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_DSP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIMER1_IRQHandler
* Description    : This function handles TIMER1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIMER2_IRQHandler
* Description    : This function handles TIMER2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIMER3_IRQHandler
* Description    : This function handles TIMER3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : COMPARATOR_IRQHandler
* Description    : This function handles COMPARATOR global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void COMPARATOR_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SSP2_IRQHandler
* Description    : This function handles SSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : AUDIO_IP_IRQHandler
* Description    : This function handles AUDIO_IP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AUDIO_IP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DSP_CRPT_IRQHandler
* Description    : This function handles DSP_CRPT global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DSP_CRPT_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DSP_TIMER_IRQHandler
* Description    : This function handles DSP_TIMER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DSP_TIMER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name : DSP_CORE_IRQHandler
* Description   : This function handles DSP_CORE global interrupt request.
* Input         : None
* Output        : None
* Return        : None
*******************************************************************************/
void DSP_CORE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DSP_STATE_IRQHandler
* Description    : This function handles DSP_STATE global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DSP_STATE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART3_IRQHandler
* Description    : This function handles UART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : BACKUP_IRQHandler
* Description    : This function handles BACKUP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BACKUP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT1_IRQHandler
* Description    : This function handles EXT_INT1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT2_IRQHandler
* Description    : This function handles EXT_INT2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT3_IRQHandler
* Description    : This function handles EXT_INT3 global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT4_IRQHandler
* Description    : This function handles EXT_INT4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT4_IRQHandler(void)
{
}


#if defined (_USE_DEBUG_UART_)
/**
  * @brief  Handles hard fault exception, stores stack and prints stack via UART
  * @param  hardfault_args: MCU stack
  * @retval None
  */
void Hard_fault_handler_c(unsigned int* hardfault_args)
{
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;

    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);

    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr  = ((unsigned long) hardfault_args[5]);
    stacked_pc  = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    DEBUG_PRINTF("[Hard fault handler]\r\n");
    DEBUG_PRINTF("R0 = 0x%x\r\n", stacked_r0);
    DEBUG_PRINTF("R1 = 0x%x\r\n", stacked_r1);
    DEBUG_PRINTF("R2 = 0x%x\r\n", stacked_r2);
    DEBUG_PRINTF("R3 = 0x%x\r\n", stacked_r3);
    DEBUG_PRINTF("R12 = 0x%x\r\n", stacked_r12);
    DEBUG_PRINTF("LR = 0x%x\r\n", stacked_lr);
    DEBUG_PRINTF("PC = 0x%x\r\n", stacked_pc);
    DEBUG_PRINTF("PSR = 0x%x\r\n", stacked_psr);

    /* Go to infinite loop when Hard Fault exception occurs */
    while (1);
}

#endif /* #if defined (_USE_DEBUG_UART_) */

#endif /* #if defined (USE_MDR32FG16S1QI) */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR32FG16S1QI_IT.c */


