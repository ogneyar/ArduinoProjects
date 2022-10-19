/*****************************************************************************
*
* @brief Startup file.
*
* Copyright (c) 2018 CloudBEAR LLC - http://www.cloudbear.ru/
* Copyright (c) 2020 JSC "ICC MILANDR" - https://www.milandr.ru/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
*   Neither the name of Milandr nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

// Interrupt numbers:
#define IRQ_M_SOFT      3   // machine software interrupt
#define IRQ_M_TIMER     7   // machine timer interrupt
#define IRQ_M_EXT       11  // machine external interrupt

#define DMA_IRQn        0
#define UART1_IRQn      1
#define UART2_IRQn      2
#define SSP1_IRQn       3
#define POWER_IRQn      4
#define WWDG_IRQn       5
#define TIM1_IRQn       6
#define TIM2_IRQn       7
#define ADC_IRQn        8
#define I2C_IRQn        9
#define BACKUP_IRQn     10
#define EXT1_IRQn       11
#define EXT2_IRQn       12
#define EXT3_IRQn       13
#define ADCUI03_IRQn    14
#define ADCUI1_IRQn     15
#define ADCUI2_IRQn     16
#define LBLOCK_IRQn     17
#define RFU_IRQn        18
#define SENSORS_IRQn    19
#define CLKMEAUSRE_IRQn 20
#define RANDOM_IRQn     21
#define ISO7816_IRQn    22
#define UART3_IRQn      23
#define SSP2_IRQn       24
#define SSP3_IRQn       25
#define TIM3_IRQn       26
#define TIM4_IRQn       27
#define UART4_IRQn      28
#define OTP_IRQn        29

// Interrupt enable bits for machine mode
#define MSTATUS_MIE  0x00000008

// Periph Interrupt occured
#define MCAUSE_MEI  0x8000000B

// Periph Interrupt occured
#define PLIC_ICC_ADDR  0x0C200004

#if __riscv_xlen == 64
# define LREG           ld
# define SREG           sd
# define REGBYTES       8
# define LOG2_REGBYTES  3
# define XWORD          .dword
#else
# define LREG           lw
# define SREG           sw
# define REGBYTES       4
# define LOG2_REGBYTES  2
# define XWORD          .word
#endif

  .section ".text.init"
  .globl _start

_start:
  // Only first hart runs
  csrr s10, mhartid
  beqz s10, 1f
  j .
1:

  // Zeroing registers
  li  x1, 0
  li  x2, 0
  li  x3, 0
  li  x4, 0
  li  x5, 0
  li  x6, 0
  li  x7, 0
  li  x8, 0
  li  x9, 0
  li  x10,0
  li  x11,0
  li  x12,0
  li  x13,0
  li  x14,0
  li  x15,0
  li  x16,0
  li  x17,0
  li  x18,0
  li  x19,0
  li  x20,0
  li  x21,0
  li  x22,0
  li  x23,0
  li  x24,0
  li  x25,0
  li  x26,0
  li  x27,0
  li  x28,0
  li  x29,0
  li  x30,0
  li  x31,0

  // Global pointer (gp) allows using more effective gp-relative addressing instead of
  // abosulte/pc-relative for arbitrary 4KiB memory range. For the optimisation to be effective,
  // it should cover the most intensely used RAM area. For standard newlib apps, this is the
  // area where the .sdata section is located. The linker uses the (!) __global_pointer$ symbol
  // definition to compare the memory addresses and, if within range, it replaces
  // absolute/pc-relative addressing with gp-relative addressing, which makes the code more
  // efficient. This process is also called relaxing, and can be disabled by -Wl,--no-relax.
  // The gp register should be loaded during startup and should not be changed later.
  .option push
  .option norelax
    la gp, __global_pointer$
  .option pop

  la   sp, __sp

  /*-----------*/
  /* Init trap */
  /*-----------*/
  la t0, trap_vector
  csrw mtvec, t0

  /*-------------------------*/
  /*  Copy functions to RAM  */
  /*-------------------------*/
  la a0, __ramfunc_load_start
  la a1, __ramfunc_start
  la a2, __ramfunc_end
  bgeu a0, a1, 2f          // do i need to copy?
  bgeu a1, a2, 2f
1:
  lw t0, (a0)
  sw t0, (a1)
  addi a0, a0, 4
  addi a1, a1, 4
  bltu a1, a2, 1b
2:

  /*-------------*/
  /*  Init data  */
  /*-------------*/
  la a0, __data_load_start
  la a1, __data_start
  la a2, __data_end
  bgeu a1, a2, 2f
1:
  lw t0, (a0)
  sw t0, (a1)
  addi a0, a0, 4
  addi a1, a1, 4
  bltu a1, a2, 1b
2:

  /*-------------*/
  /* Zeroing bss */
  /*-------------*/
  la    t0, __bss_start
  la    t1, __bss_end
1:
  bge   t0, t1, 2f
  sw    zero, 0(t0)
  addi  t0, t0, 4
  j     1b
2:

  /*-----------------*/
  /* AHB_RAM Section */
  /*-----------------*/
  /*  Init AHB_RAM data  */
  la a0, __ahbram_data_load_start
  la a1, __ahbram_data_start
  la a2, __ahbram_data_end
  bgeu a1, a2, 2f
1:
  lw t0, (a0)
  sw t0, (a1)
  addi a0, a0, 4
  addi a1, a1, 4
  bltu a1, a2, 1b
2:
  /* Zeroing AHB_RAM bss */
  la    t0, __ahbram_bss_start
  la    t1, __ahbram_bss_end
1:
  bge   t0, t1, 2f
  sw    zero, 0(t0)
  addi  t0, t0, 4
  j     1b
2:

  /*----------------------------------*/
  /* Calculating heap and stack areas */
  /*----------------------------------*/

  // Calculate brk_end and store it to s6
  // brk_end = __vma_end(sp) - stack_size
  // Stack size = 2 KiB.
  li s4, 2048
  sub s6, sp, s4

  // brk_base = __end
  la s4, __end
  la t0, brk_base
  SREG s4, 0(t0)

  // brk_size = brk_end (s6) - brk_base (s4)
  sub s6, s6, s4
  la t0, brk_size
  SREG s6, 0(t0)

  /*------------------------------*/
  /* Init machine mode interrupts */
  /*------------------------------*/
  csrsi mstatus, MSTATUS_MIE

  /* Call static constructors */
  call __libc_init_array

  /*-----------*/
  /* Call main */
  /*-----------*/
  call main
  // get main return code
  mv t0, a0

  j .

  /*-------------*/
  /* Trap vector */
  /*-------------*/
  // trap vector must be aligned on a 4-byte boundary
.section .ramfunc, "ax"
.cfi_sections	.debug_frame
.align 2
.type trap_vector, @function
.globl trap_vector
trap_vector:                        ; .cfi_startproc
  addi sp, sp, -33*REGBYTES         ; .cfi_def_cfa_offset 33*REGBYTES

  // save registers to stack
  SREG s0, 8*REGBYTES(sp)           ; .cfi_offset 8, -25*REGBYTES
  addi s0, sp, 33*REGBYTES          ; .cfi_def_cfa 8, 0

  SREG x1, 1*REGBYTES(sp)
  SREG x2, 2*REGBYTES(sp)
  SREG x3, 3*REGBYTES(sp)
  SREG x4, 4*REGBYTES(sp)
  SREG x5, 5*REGBYTES(sp)
  SREG x6, 6*REGBYTES(sp)           ; .cfi_offset 6, -27*REGBYTES
  SREG x7, 7*REGBYTES(sp)           ; .cfi_offset 7, -26*REGBYTES

  SREG x9, 9*REGBYTES(sp)           ; .cfi_offset 9, -24*REGBYTES
  SREG x10, 10*REGBYTES(sp)         ; .cfi_offset 10, -23*REGBYTES
  SREG x11, 11*REGBYTES(sp)         ; .cfi_offset 11, -22*REGBYTES
  SREG x12, 12*REGBYTES(sp)         ; .cfi_offset 12, -21*REGBYTES
  SREG x13, 13*REGBYTES(sp)         ; .cfi_offset 13, -20*REGBYTES
  SREG x14, 14*REGBYTES(sp)         ; .cfi_offset 14, -19*REGBYTES
  SREG x15, 15*REGBYTES(sp)         ; .cfi_offset 15, -18*REGBYTES
  SREG x16, 16*REGBYTES(sp)         ; .cfi_offset 16, -17*REGBYTES
  SREG x17, 17*REGBYTES(sp)         ; .cfi_offset 17, -16*REGBYTES
  SREG x18, 18*REGBYTES(sp)         ; .cfi_offset 18, -15*REGBYTES
  SREG x19, 19*REGBYTES(sp)         ; .cfi_offset 19, -14*REGBYTES
  SREG x20, 20*REGBYTES(sp)         ; .cfi_offset 20, -13*REGBYTES
  SREG x21, 21*REGBYTES(sp)         ; .cfi_offset 21, -12*REGBYTES
  SREG x22, 22*REGBYTES(sp)         ; .cfi_offset 22, -11*REGBYTES
  SREG x23, 23*REGBYTES(sp)         ; .cfi_offset 23, -10*REGBYTES
  SREG x24, 24*REGBYTES(sp)         ; .cfi_offset 24, -9*REGBYTES
  SREG x25, 25*REGBYTES(sp)         ; .cfi_offset 25, -8*REGBYTES
  SREG x26, 26*REGBYTES(sp)         ; .cfi_offset 26, -7*REGBYTES
  SREG x27, 27*REGBYTES(sp)         ; .cfi_offset 27, -6*REGBYTES
  SREG x28, 28*REGBYTES(sp)         ; .cfi_offset 28, -5*REGBYTES
  SREG x29, 29*REGBYTES(sp)         ; .cfi_offset 29, -4*REGBYTES
  SREG x30, 30*REGBYTES(sp)         ; .cfi_offset 30, -3*REGBYTES
  SREG x31, 31*REGBYTES(sp)//         ; .cfi_offset 31, -2*REGBYTES

  csrr ra, mepc
  SREG ra, 32*REGBYTES(sp)          ; .cfi_offset 1, -REGBYTES

  csrr s1, mcause
  // Highest bit indicates is it interrupt or not, so we can compare it with zero: negative value
  // means interrupt
  bgez s1, 1f
  la s2, interrupt_table // interrupt is occured, s2 = &(interrupt_table)
  j 2f
1:
  la s2, exception_table // exception is occured, s2 = &(exception_table)
2:
  la s3, MCAUSE_MEI
  bne s1, s3, 4f
  la s4, PLIC_ICC_ADDR  // s4 = PLIC_ICC_ADDR
  lw s1, (s4)			// s1 = PLIC_ICC
3:
  la s2, irq_extm_table // periph interrupt is occured, s2 = &(irq_extm_table)
  // Trap processing: call corresponding function (from periph interrupt)
  sll s3, s1, LOG2_REGBYTES // s3 = mcause << 2 (xlen == 32) or mcause << 3 (xlen == 64)
  add s2, s2, s3            // s2 = &table[mcause]
  LREG s2, 0(s2)            // s2 = table[mcause] (s2 - address of corresponding handler)
  jalr s2                   // Invoke the handler
  sw s1, (s4)			// PLIC_ICC = s1
  lw s1, (s4)			// s1 = PLIC_ICC
  bnez s1, 3b
  j 5f
4:
  // Trap processing: call corresponding function (from interrupt or exception tables)
  sll s1, s1, LOG2_REGBYTES // s1 = mcause << 2 (xlen == 32) or mcause << 3 (xlen == 64)
  add s2, s2, s1            // s2 = &table[mcause]
  LREG s2, 0(s2)            // s2 = table[mcause] (s2 - address of corresponding handler)
  csrr a0, mepc
  csrr a1, mcause
  mv a2, sp
  jalr s2                   // Invoke the handler
  csrw mepc, a0
5:
  // load registers from stack
  LREG ra, 1*REGBYTES(sp)           ; .cfi_restore 1
  LREG x2, 2*REGBYTES(sp)           ; .cfi_restore 2
  LREG x3, 3*REGBYTES(sp)           ; .cfi_restore 3
  LREG x4, 4*REGBYTES(sp)           ; .cfi_restore 4
  LREG x5, 5*REGBYTES(sp)           ; .cfi_restore 5
  LREG x6, 6*REGBYTES(sp)           ; .cfi_restore 6
  LREG x7, 7*REGBYTES(sp)           ; .cfi_restore 7
  LREG s0, 8*REGBYTES(sp)           ; .cfi_restore 8; .cfi_def_cfa 2, 33*REGBYTES
  LREG x9, 9*REGBYTES(sp)           ; .cfi_restore 9
  LREG x10, 10*REGBYTES(sp)         ; .cfi_restore 10
  LREG x11, 11*REGBYTES(sp)         ; .cfi_restore 11
  LREG x12, 12*REGBYTES(sp)         ; .cfi_restore 12
  LREG x13, 13*REGBYTES(sp)         ; .cfi_restore 13
  LREG x14, 14*REGBYTES(sp)         ; .cfi_restore 14
  LREG x15, 15*REGBYTES(sp)         ; .cfi_restore 15
  LREG x16, 16*REGBYTES(sp)         ; .cfi_restore 16
  LREG x17, 17*REGBYTES(sp)         ; .cfi_restore 17
  LREG x18, 18*REGBYTES(sp)         ; .cfi_restore 18
  LREG x19, 19*REGBYTES(sp)         ; .cfi_restore 19
  LREG x20, 20*REGBYTES(sp)         ; .cfi_restore 20
  LREG x21, 21*REGBYTES(sp)         ; .cfi_restore 21
  LREG x22, 22*REGBYTES(sp)         ; .cfi_restore 22
  LREG x23, 23*REGBYTES(sp)         ; .cfi_restore 23
  LREG x24, 24*REGBYTES(sp)         ; .cfi_restore 24
  LREG x25, 25*REGBYTES(sp)         ; .cfi_restore 25
  LREG x26, 26*REGBYTES(sp)         ; .cfi_restore 26
  LREG x27, 27*REGBYTES(sp)         ; .cfi_restore 27
  LREG x28, 28*REGBYTES(sp)         ; .cfi_restore 28
  LREG x29, 29*REGBYTES(sp)         ; .cfi_restore 29
  LREG x30, 30*REGBYTES(sp)         ; .cfi_restore 30
  LREG x31, 31*REGBYTES(sp)         ; .cfi_restore 31

  addi sp, sp, 33*REGBYTES          ; .cfi_def_cfa_offset 0
  mret                              ; .cfi_endproc

unexpected_handler:
  j .

// This macros is used to define weak exception handler
# define DECLARE_WEAK_EXC_FUNC(func_name) \
.type func_name, @function; \
.weak func_name; \
func_name:          ; .cfi_startproc; \
  addi    sp,sp,-8  ; .cfi_def_cfa_offset 8; \
  sw      ra,4(sp)  ; .cfi_offset 1, -4; \
  sw      s0,0(sp)  ; .cfi_offset 8, -8; \
  addi    s0,sp,8   ; .cfi_def_cfa 8, 0; \
  j .               ; .cfi_endproc

DECLARE_WEAK_EXC_FUNC(trap_iam) // instruction address misaligned
DECLARE_WEAK_EXC_FUNC(trap_iaf) // instruction access fault
DECLARE_WEAK_EXC_FUNC(trap_ii)  // illegal instruction
DECLARE_WEAK_EXC_FUNC(trap_lam) // load address misaligned
DECLARE_WEAK_EXC_FUNC(trap_laf) // load access fault
DECLARE_WEAK_EXC_FUNC(trap_sam) // store address misaligned
DECLARE_WEAK_EXC_FUNC(trap_saf) // store access fault
DECLARE_WEAK_EXC_FUNC(trap_ecallm) // environment call from M-mode

DECLARE_WEAK_EXC_FUNC(_exit)

// This macros is used to define following function:
// 1. weak irq handler
// 2. enable irq
// 3. disable irq
// param irq_num is used to setup corresponding bit in register 'mie'.
// For more information, see RISC-V ISA privilleged specification, section 3.1.14.
# define DECLARE_WEAK_IRQ_FUNC(func_name, irq_num) \
  .type func_name, @function; \
  .weak func_name; \
  func_name:; \
    j . ; \
  .type enable_##func_name, @function; \
  .globl enable_##func_name; \
  enable_##func_name: \
    li t0, 1 << irq_num; \
    csrs mie, t0; \
    ret; \
  .type disable_##func_name, @function; \
  .globl disable_##func_name; \
  disable_##func_name: \
    li t0, 1 << irq_num; \
    csrc mie, t0; \
    ret

DECLARE_WEAK_IRQ_FUNC(PendSV_Handler, IRQ_M_SOFT) // machine software interrupt
DECLARE_WEAK_IRQ_FUNC(SysTick_Handler, IRQ_M_TIMER) // machine timer interrupt
DECLARE_WEAK_IRQ_FUNC(irq_extm, IRQ_M_EXT) // machine external interrupt

// This macros is used to define weak peripheral irq handler
# define DECLARE_WEAK_PER_IRQ_FUNC(func_name) \
  .type func_name, @function; \
  .weak func_name; \
  func_name: \
    j .  \

DECLARE_WEAK_PER_IRQ_FUNC(DMA_IRQHandler)       // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(UART1_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(UART2_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(SSP1_IRQHandler)      // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(POWER_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(WWDG_IRQHandler)      // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(Timer1_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(Timer2_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(ADC_IRQHandler)       // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(I2C_IRQHandler)       // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(BACKUP_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(EXT_1_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(EXT_2_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(EXT_3_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(ADCIU_1_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(ADCIU_2_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(ADCIU_3_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(L_BLOCK_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(Default_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(SENSORS_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(CLK_MEASURE_IRQHandler)  // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(RANDOM_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(ISO7816_IRQHandler)   // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(UART3_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(SSP2_IRQHandler)      // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(SSP3_IRQHandler)      // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(Timer3_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(Timer4_IRQHandler)    // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(UART4_IRQHandler)     // peripheral interrupt
DECLARE_WEAK_PER_IRQ_FUNC(OTP_Corrupt_IRQHandler) // peripheral interrupt

// The following tables contains addresses of handlers that
// will be invoked by trap_handler. Select of corresponding
// handler is performed based on mcause register.
// For more details, see RISC-V ISA privilleged specification, section 3.1.20.
.data
.align 6
exception_table:
XWORD trap_iam // instruction address misaligned
XWORD trap_iaf // instruction access fault
XWORD trap_ii  // illegal instruction
XWORD unexpected_handler // breakpoint
XWORD trap_lam // load address misaligned
XWORD trap_laf // load access fault
XWORD trap_sam // store address misaligned
XWORD trap_saf // store access fault
XWORD unexpected_handler // environment call from U-mode
XWORD unexpected_handler // environment call from S-mode
XWORD unexpected_handler // reserved
XWORD trap_ecallm // environment call from M-mode
XWORD unexpected_handler // instruction page fault
XWORD unexpected_handler // load page fault
XWORD unexpected_handler // reserved
XWORD unexpected_handler // store page fault

.data
.align 6
interrupt_table:
XWORD unexpected_handler // user software interrupt
XWORD unexpected_handler // supervisor software interrupt
XWORD unexpected_handler // reserved
XWORD PendSV_Handler // machine software interrupt
XWORD unexpected_handler // user timer interrupt
XWORD unexpected_handler // supervisor timer interrupt
XWORD unexpected_handler // reserved
XWORD SysTick_Handler // machine timer interrupt
XWORD unexpected_handler // user external interrupt
XWORD unexpected_handler // supervisor external interrupt
XWORD unexpected_handler // reserved
XWORD irq_extm // machine external interrupt

.data
.align 6
irq_extm_table:
XWORD unexpected_handler
XWORD DMA_IRQHandler
XWORD UART1_IRQHandler
XWORD UART2_IRQHandler
XWORD SSP1_IRQHandler
XWORD POWER_IRQHandler
XWORD WWDG_IRQHandler
XWORD Timer1_IRQHandler
XWORD Timer2_IRQHandler
XWORD ADC_IRQHandler
XWORD I2C_IRQHandler
XWORD BACKUP_IRQHandler
XWORD EXT_1_IRQHandler
XWORD EXT_2_IRQHandler
XWORD EXT_3_IRQHandler
XWORD ADCIU_1_IRQHandler
XWORD ADCIU_2_IRQHandler
XWORD ADCIU_3_IRQHandler
XWORD L_BLOCK_IRQHandler
XWORD unexpected_handler
XWORD SENSORS_IRQHandler
XWORD CLK_MEASURE_IRQHandler
XWORD RANDOM_IRQHandler
XWORD ISO7816_IRQHandler
XWORD UART3_IRQHandler
XWORD SSP2_IRQHandler
XWORD SSP3_IRQHandler
XWORD Timer3_IRQHandler
XWORD Timer4_IRQHandler
XWORD UART4_IRQHandler
XWORD OTP_Corrupt_IRQHandler

.data
.align 3
.globl brk_base
brk_base:
.dword 0x0

.globl brk_size
brk_size:
.dword 0x0