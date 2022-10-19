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
//#include <intrinsics.h>

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
#define MIEP_MSIEP              0x0008
#define MIEP_MTIEP              0x0080
#define MIEP_MEIEP              0x0800

/* Machine software interrupt */
#define PendSV_SetPending()         ((volatile uint32_t*)(MDR_CLINT_BASE))[0] = 1
#define PendSV_ClearPending()       ((volatile uint32_t*)(MDR_CLINT_BASE))[0] = 0

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
extern void enable_SysTick_Handler();
extern void disable_SysTick_Handler();
extern void enable_PendSV_Handler();
extern void disable_PendSV_Handler();
extern void enable_irq_extm();
extern void disable_irq_extm();

extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void DMA_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void SSP1_IRQHandler(void);
extern void POWER_IRQHandler(void);
extern void WWDG_IRQHandler(void);
extern void Timer1_IRQHandler(void);
extern void Timer2_IRQHandler(void);
extern void ADC_IRQHandler(void);
extern void I2C_IRQHandler(void);
extern void BACKUP_IRQHandler(void);
extern void EXT_1_IRQHandler(void);
extern void EXT_2_IRQHandler(void);
extern void EXT_3_IRQHandler(void);
extern void ADCIU_1_IRQHandler(void);
extern void ADCIU_2_IRQHandler(void);
extern void ADCIU_3_IRQHandler(void);
extern void L_BLOCK_IRQHandler(void);
extern void RESERVED_IRQHandler(void);
extern void SENSORS_IRQHandler(void);
extern void CLK_MEASURE_IRQHandler(void);
extern void RANDOM_IRQHandler(void);
extern void ISO7816_IRQHandler(void);
extern void UART3_IRQHandler(void);
extern void SSP2_IRQHandler(void);
extern void SSP3_IRQHandler(void);
extern void Timer3_IRQHandler(void);
extern void Timer4_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void OTP_Corrupt_IRQHandler(void);
extern void Default_IRQHandler(void);

extern void trap_iam(void);
extern void trap_iaf(void);
extern void trap_ii(void);
extern void trap_lam(void);
extern void trap_laf(void);
extern void trap_sam(void);
extern void trap_saf(void);
extern void trap_ecallm(void);
extern void unexpected_handler(void);

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __INTERRUPT_H */

/**
 * END OF FILE interrupt.h
 */

