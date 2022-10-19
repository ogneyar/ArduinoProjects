/**
  * FILE interrupt.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include <intrinsics.h>

/* Define --------------------------------------------------------------------*/
#define MDR_CLIC_MSIP_Reg       ((volatile uint32_t*)(MDR_CLINT_BASE))[0]
#define MDR_CLIC_MTIMECMP_Reg   ((volatile uint32_t*)(MDR_CLINT_TIMER_CMP))[0]
#define MDR_CLIC_MTIME_Reg      ((volatile uint32_t*)(MDR_CLINT_TIMER))[0]
#define MDR_PLIC_PR_reg         ((volatile uint32_t*)(MDR_PLIC_PRI_BASE))
#define MDR_PLIC_IPM_reg        ((volatile uint32_t*)(MDR_PLIC_IRM))[0]
#define MDR_PLIC_IEM_reg        ((volatile uint32_t*)(MDR_PLIC_IEM))[0]
#define MDR_PLIC_THR_reg        ((volatile uint32_t*)(MDR_PLIC_THR))[0]
#define MDR_PLIC_ICC_reg        ((volatile uint32_t*)(MDR_PLIC_ICC))[0]
#define MCAUSE_INTERRUPT        0x80000000 
#define MCAUSE_MSI              0x80000003
#define MCAUSE_MTI              0x80000007
#define MCAUSE_MEI              0x8000000B
#define MIEP_MSIEP              0x0008
#define MIEP_MTIEP              0x0080
#define MIEP_MEIEP              0x0800

/* Machine software interrupt */
#define enable_PendSV_Handler()         __set_bits_csr(_CSR_MIE, MIEP_MSIEP )
#define disable_PendSV_Handler()        __clear_bits_csr(_CSR_MIE, MIEP_MSIEP )
#define PendSV_SetPending()             ((volatile uint32_t*)(MDR_CLINT_BASE))[0] = 1
#define PendSV_ClearPending()           ((volatile uint32_t*)(MDR_CLINT_BASE))[0] = 0

/* Machine timer interrupt */
#define enable_SysTick_Handler()        __set_bits_csr(_CSR_MIE, MIEP_MTIEP )
#define disable_SysTick_Handler()       __clear_bits_csr(_CSR_MIE, MIEP_MTIEP )

/* Machine external interrupts */
#define enable_ExtInterrupt_EN()        __set_bits_csr(_CSR_MIE, MIEP_MEIEP );
#define disable_ExtInterrupt_DIS()      __clear_bits_csr(_CSR_MIE, MIEP_MEIEP )

    
/* Enable External Interrupt*/
#define PLIC_EnableIRQ(IRQn)            MDR_PLIC_IEM_reg |= 1 << (IRQn + 1)

/* Disable External Interrupt */
#define PLIC_DisableIRQ(IRQn)           MDR_PLIC_IEM_reg &= ~(1 << (IRQn + 1))

/* Get Pending Interrupt*/ 
#define PLIC_GetPendingIRQ(IRQn)        (MDR_PLIC_IPM_reg >> IRQn) & 1

/* Release Processing Interrupt */ 
#define PLIC_ReleaseIRQ(IRQn)           MDR_PLIC_ICC_reg = (IRQn + 1)

/* Get Max Priority Pending Interrupt */
//#define PLIC_GetMaxPendIRQ              MDR_PLIC_ICC_reg
    
/* Clear Max Priority Pending Interrupt */
//#define PLIC_ClearMaxPendIRQ            MDR_PLIC_ICC_reg

/* Set Interrupt Priority */
#define PLIC_SetPriority(IRQn, priority)     MDR_PLIC_PR_reg[IRQn] = priority

/* Get Interrupt Priority */
#define PLIC_GetPriority(IRQn)          MDR_PLIC_PR_reg[IRQn]
    
/* Set Min Permissible Interrupt Priority */
#define PLIC_SetMinPermPriority(priority)       MDR_PLIC_THR_reg = priority

/* Get Min Permissible Interrupt Priority */
#define PLIC_GetMinPermPriority                 MDR_PLIC_THR_reg

/* Function prototypes -------------------------------------------------------*/
__interrupt void IRQHandler(void);
__weak void PendSV_Handler(void);
__weak void SysTick_Handler(void);
__weak void DMA_IRQHandler(void);
__weak void UART1_IRQHandler(void);
__weak void UART2_IRQHandler(void);
__weak void SSP1_IRQHandler(void);
__weak void POWER_IRQHandler(void);
__weak void WWDG_IRQHandler(void);
__weak void Timer1_IRQHandler(void);
__weak void Timer2_IRQHandler(void);
__weak void ADC_IRQHandler(void);
__weak void I2C_IRQHandler(void);
__weak void BACKUP_IRQHandler(void);
__weak void EXT_1_IRQHandler(void);
__weak void EXT_2_IRQHandler(void);
__weak void EXT_3_IRQHandler(void);
__weak void ADCIU_1_IRQHandler(void);
__weak void ADCIU_2_IRQHandler(void);
__weak void ADCIU_3_IRQHandler(void);
__weak void L_BLOCK_IRQHandler(void);
__weak void RESERVED_IRQHandler(void);
__weak void SENSORS_IRQHandler(void);
__weak void CLK_MEASURE_IRQHandler(void);
__weak void RANDOM_IRQHandler(void);
__weak void ISO7816_IRQHandler(void);
__weak void UART3_IRQHandler(void);
__weak void SSP2_IRQHandler(void);
__weak void SSP3_IRQHandler(void);
__weak void Timer3_IRQHandler(void);
__weak void Timer4_IRQHandler(void);
__weak void UART4_IRQHandler(void);
__weak void OTP_Corrupt_IRQHandler(void);
__weak void Default_IRQHandler(void);

__weak void trap_iam(void);
__weak void trap_iaf(void);
__weak void trap_ii(void);
__weak void trap_lam(void);
__weak void trap_laf(void);
__weak void trap_sam(void);
__weak void trap_saf(void);
__weak void trap_ecallm(void);
__weak void unexpected_handler(void);

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __INTERRUPT_H */

/**
 * END OF FILE interrupt.h
 */

