/**
  * FILE interrupt.c
  */
/* 
Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include <intrinsics.h>
#include "interrupt.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

 void (*ExtInterruptVectorTable []) (void) = {
            Default_IRQHandler,
            DMA_IRQHandler,
            UART1_IRQHandler,
            UART2_IRQHandler,
            SSP1_IRQHandler,
            POWER_IRQHandler,
            WWDG_IRQHandler,
            Timer1_IRQHandler,
            Timer2_IRQHandler,
            ADC_IRQHandler,
            I2C_IRQHandler,
            BACKUP_IRQHandler,
            EXT_1_IRQHandler,
            EXT_2_IRQHandler,
            EXT_3_IRQHandler,
            ADCIU_1_IRQHandler,
            ADCIU_2_IRQHandler,
            ADCIU_3_IRQHandler,
            L_BLOCK_IRQHandler,
            Default_IRQHandler,
            SENSORS_IRQHandler,
            CLK_MEASURE_IRQHandler,
            RANDOM_IRQHandler,
            ISO7816_IRQHandler,
            UART3_IRQHandler,
            SSP2_IRQHandler,
            SSP3_IRQHandler,
            Timer3_IRQHandler,
            Timer4_IRQHandler,
            UART4_IRQHandler,
            OTP_Corrupt_IRQHandler
            };

 void (*ExceptionVectorTable []) (void) = {
            trap_iam, // instruction address misaligned
            trap_iaf, // instruction access fault
            trap_ii,  // illegal instruction
            unexpected_handler, // breakpoint
            trap_lam, // load address misaligned
            trap_laf, // load access fault
            trap_sam, // store address misaligned
            trap_saf, // store access fault
            unexpected_handler, // environment call from U-mode
            unexpected_handler, // environment call from S-mode
            unexpected_handler, // reserved
            trap_ecallm, // environment call from M-mode
            unexpected_handler, // instruction page fault
            unexpected_handler, // load page fault
            unexpected_handler, // reserved
            unexpected_handler, // store page fault
            };

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Interrupt service routine */
__interrupt void IRQHandler(void)
{
    uint32_t    int_num, t_mcause;
    
    t_mcause = __read_csr(_CSR_MCAUSE);
    if (t_mcause < MCAUSE_INTERRUPT)
    {
        (*ExceptionVectorTable[t_mcause])(); 
    }
    else
    {
        if (t_mcause == MCAUSE_MSI)
            PendSV_Handler();
        if (t_mcause == MCAUSE_MTI)
            SysTick_Handler();
        if (t_mcause == MCAUSE_MEI)
        {
            int_num = MDR_PLIC_ICC_reg;
            while (int_num)
            {
                (*ExtInterruptVectorTable[int_num])(); 
                MDR_PLIC_ICC_reg = int_num;
                int_num = MDR_PLIC_ICC_reg;
            }
        }
    }
}

__weak void PendSV_Handler(void)
{
    ((volatile uint32_t*)(MDR_CLINT_BASE))[0] = 0;
}

__weak void SysTick_Handler(void)
{
}

__weak void DMA_IRQHandler(void)
{
}
__weak void UART1_IRQHandler(void)
{
}
__weak void UART2_IRQHandler(void)
{
}
__weak void SSP1_IRQHandler(void)
{
}
__weak void POWER_IRQHandler(void)
{
}
__weak void WWDG_IRQHandler(void)
{
}
__weak void Timer1_IRQHandler(void)
{
}
__weak void Timer2_IRQHandler(void)
{
}
__weak void ADC_IRQHandler(void)
{
}
__weak void I2C_IRQHandler(void)
{
}
__weak void BACKUP_IRQHandler(void)
{
}
__weak void EXT_1_IRQHandler(void)
{
}
__weak void EXT_2_IRQHandler(void)
{
}
__weak void EXT_3_IRQHandler(void)
{
}
__weak void ADCIU_1_IRQHandler(void)
{
}
__weak void ADCIU_2_IRQHandler(void)
{
}
__weak void ADCIU_3_IRQHandler(void)
{
}
__weak void L_BLOCK_IRQHandler(void)
{
}
__weak void RESERVED_IRQHandler(void)
{
}
__weak void SENSORS_IRQHandler(void)
{
}
__weak void CLK_MEASURE_IRQHandler(void)
{
}
__weak void RANDOM_IRQHandler(void)
{
}
__weak void ISO7816_IRQHandler(void)
{
}
__weak void UART3_IRQHandler(void)
{
}
__weak void SSP2_IRQHandler(void)
{
}
__weak void SSP3_IRQHandler(void)
{
}
__weak void Timer3_IRQHandler(void)
{
}
__weak void Timer4_IRQHandler(void)
{
}
__weak void UART4_IRQHandler(void)
{
}
__weak void OTP_Corrupt_IRQHandler(void)
{
}
__weak void Default_IRQHandler(void)
{
    while(1);
}


__weak void trap_iam(void)
{
    while(1);
}
__weak void trap_iaf(void)
{
    while(1);
}
__weak void trap_ii(void)
{
    while(1);
}
__weak void trap_lam(void)
{
    while(1);
}
__weak void trap_laf(void)
{
    while(1);
}
__weak void trap_sam(void)
{
    while(1);
}
__weak void trap_saf(void)
{
    while(1);
}
__weak void trap_ecallm(void)
{
    while(1);
}
__weak void unexpected_handler(void)
{
    while(1);
}


void ExtInterruptInit()
{
    __no_operation();    
}

/**
 * END OF FILE interrupt.c
 */

