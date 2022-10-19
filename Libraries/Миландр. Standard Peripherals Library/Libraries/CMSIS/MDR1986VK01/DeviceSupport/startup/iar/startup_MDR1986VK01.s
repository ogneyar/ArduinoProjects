;/*****************************************************************************
; * @file:    startup_MLDR32F2C10.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for the
; *           Milandr MDR1986VK01 device series
; * @version: V1.0
; * @date:    13/08/2021
; *****************************************************************************
; * @copy
; *
; * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
; * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
; * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
; * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
; * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
; *
; ******************************************************************************
; * FILE startup_MLDR32F2C10.s
; */


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler              ; -15 Reset Handler
        DCD     NMI_Handler                ; -14 NMI Handler
        DCD     HardFault_Handler          ; -13 Hard Fault Handler
        DCD     0                          ; -12 MPU Fault Handler
        DCD     0                          ; -11 Bus Fault Handler
        DCD     0                          ; -10 Usage Fault Handler
        DCD     0                          ; -9  Reserved
        DCD     0                          ; -8  Reserved
        DCD     0                          ; -7  Reserved
        DCD     0                          ; -6  Reserved
        DCD     SVC_Handler                ; -5  SVCall Handler
        DCD     0                          ; -4  Debug Monitor Handler
        DCD     0                          ; -3  Reserved
        DCD     PendSV_Handler             ; -2  PendSV Handler
        DCD     SysTick_Handler            ; -1  SysTick Handler

         ; External Interrupts
        DCD     0                          ; 0   Reserved
        DCD     0                          ; 1   Reserved
        DCD     0                          ; 2   Reserved
        DCD     0                          ; 3   Reserved
        DCD     0                          ; 4   Reserved
        DCD     0                          ; 5   Reserved
        DCD     0                          ; 6   Reserved
        DCD     0                          ; 7   Reserved
        DCD     0                          ; 8   Reserved
        DCD     0                          ; 9   Reserved
        DCD     0                          ; 10  Reserved
        DCD     0                          ; 11  Reserved
        DCD     0                          ; 12  Reserved
        DCD     0                          ; 13  Reserved
        DCD     0                          ; 14  Reserved
        DCD     0                          ; 15  Reserved
        DCD     0                          ; 16  Reserved
        DCD     0                          ; 17  Reserved
        DCD     0                          ; 18  Reserved
        DCD     0                          ; 19  Reserved
        DCD     0                          ; 20  Reserved
        DCD     0                          ; 21  Reserved
        DCD     0                          ; 22  Reserved
        DCD     0                          ; 23  Reserved
        DCD     0                          ; 24  Reserved
        DCD     0                          ; 25  Reserved
        DCD     0                          ; 26  Reserved
        DCD     0                          ; 27  Reserved
        DCD     0                          ; 28  Reserved
        DCD     0                          ; 29  Reserved
        DCD     0                          ; 30  Reserved
        DCD     0                          ; 31  Reserved
        DCD     FT_IF0_IRQHandler          ; 32
        DCD     FT_IF1_IRQHandler          ; 33
        DCD     FT_IF2_IRQHandler          ; 34
        DCD     FT_IF3_IRQHandler          ; 35
        DCD     CLK_IF_IRQHandler          ; 36
        DCD     0                          ; 37  Reserved
        DCD     RTC_IF_IRQHandler          ; 38
        DCD     BKP_IF_IRQHandler          ; 39
        DCD     EXT_INTERROR0_IRQHandler   ; 40
        DCD     EXT_INTERROR1_IRQHandler   ; 41
        DCD     EXT_INTERROR2_IRQHandler   ; 42
        DCD     EXT_INTERROR3_IRQHandler   ; 43
        DCD     EXT_INTERROR4_IRQHandler   ; 44
        DCD     EXT_INTERROR5_IRQHandler   ; 45
        DCD     EXT_INTERROR6_IRQHandler   ; 46
        DCD     EXT_INTERROR7_IRQHandler   ; 47
        DCD     IF_ERR_SCR_IRQHandler      ; 48
        DCD     IF_FIN_SCR_IRQHandler      ; 49
        DCD     DMA_ERR_IRQHandler         ; 50
        DCD     DMA_DONE0_IRQHandler       ; 51
        DCD     DMA_DONE1_IRQHandler       ; 52
        DCD     DMA_DONE2_IRQHandler       ; 53
        DCD     DMA_DONE3_IRQHandler       ; 54
        DCD     DMA_DONE4_IRQHandler       ; 55
        DCD     DMA_DONE5_IRQHandler       ; 56
        DCD     DMA_DONE6_IRQHandler       ; 57
        DCD     DMA_DONE7_IRQHandler       ; 58
        DCD     DMA_DONE8_IRQHandler       ; 59
        DCD     DMA_DONE9_IRQHandler       ; 60
        DCD     DMA_DONE10_IRQHandler      ; 61
        DCD     DMA_DONE11_IRQHandler      ; 62
        DCD     DMA_DONE12_IRQHandler      ; 63
        DCD     DMA_DONE13_IRQHandler      ; 64
        DCD     DMA_DONE14_IRQHandler      ; 65
        DCD     DMA_DONE15_IRQHandler      ; 66
        DCD     DMA_DONE16_IRQHandler      ; 67
        DCD     DMA_DONE17_IRQHandler      ; 68
        DCD     DMA_DONE18_IRQHandler      ; 69
        DCD     DMA_DONE19_IRQHandler      ; 70
        DCD     DMA_DONE20_IRQHandler      ; 71
        DCD     DMA_DONE21_IRQHandler      ; 72
        DCD     DMA_DONE22_IRQHandler      ; 73
        DCD     DMA_DONE23_IRQHandler      ; 74
        DCD     DMA_DONE24_IRQHandler      ; 75
        DCD     DMA_DONE25_IRQHandler      ; 76
        DCD     DMA_DONE26_IRQHandler      ; 77
        DCD     DMA_DONE27_IRQHandler      ; 78
        DCD     DMA_DONE28_IRQHandler      ; 79
        DCD     DMA_DONE29_IRQHandler      ; 80
        DCD     DMA_DONE30_IRQHandler      ; 81
        DCD     DMA_DONE31_IRQHandler      ; 82
        DCD     IRQ_PORTA_IRQHandler       ; 83
        DCD     IRQ_PORTB_IRQHandler       ; 84
        DCD     IRQ_PORTC_IRQHandler       ; 85
        DCD     IRQ_PORTD_IRQHandler       ; 86
        DCD     0                          ; 87  Reserved
        DCD     0                          ; 88  Reserved
        DCD     ETH_IRQHandler             ; 89
        DCD     CAN0_IRQHandler            ; 90
        DCD     CAN1_IRQHandler            ; 91
        DCD     SSP0_IRQHandler            ; 92
        DCD     SSP0_RXINTR_IRQHandler     ; 93
        DCD     SSP0_TXINTR_IRQHandler     ; 94
        DCD     SSP0_RORINTR_IRQHandler    ; 95
        DCD     SSP0_RTINTR_IRQHandler     ; 96
        DCD     SSP0_RNEINTR_IRQHandler    ; 97
        DCD     SSP0_TFEINTR_IRQHandler    ; 98
        DCD     SSP0_TNBSYINTR_IRQHandler  ; 99
        DCD     SSP1_IRQHandler            ; 100
        DCD     SSP1_RXINTR_IRQHandler     ; 101
        DCD     SSP1_TXINTR_IRQHandler     ; 102
        DCD     SSP1_RORINTR_IRQHandler    ; 103
        DCD     SSP1_RTINTR_IRQHandler     ; 104
        DCD     SSP1_RNEINTR_IRQHandler    ; 105
        DCD     SSP1_TFEINTR_IRQHandler    ; 106
        DCD     SSP1_TNBSYINTR_IRQHandler  ; 107
        DCD     UART0_IRQHandler           ; 108
        DCD     UART0_TNBSYINTR_IRQHandler ; 109
        DCD     UART0_TFEINTR_IRQHandler   ; 110
        DCD     UART0_RNEINTR_IRQHandler   ; 111
        DCD     UART0_EINTR_IRQHandler     ; 112
        DCD     UART0_RTINTR_IRQHandler    ; 113
        DCD     UART0_TXINTR_IRQHandler    ; 114
        DCD     UART0_RXINTR_IRQHandler    ; 115
        DCD     UART0_MSINTR_IRQHandler    ; 116
        DCD     UART1_IRQHandler           ; 117
        DCD     UART1_TNBSYINTR_IRQHandler ; 118
        DCD     UART1_TFEINTR_IRQHandler   ; 119
        DCD     UART1_RNEINTR_IRQHandler   ; 120
        DCD     UART1_EINTR_IRQHandler     ; 121
        DCD     UART1_RTINTR_IRQHandler    ; 122
        DCD     UART1_TXINTR_IRQHandler    ; 123
        DCD     UART1_RXINTR_IRQHandler    ; 124
        DCD     UART1_MSINTR_IRQHandler    ; 125
        DCD     UART2_IRQHandler           ; 126
        DCD     UART2_TNBSYINTR_IRQHandler ; 127
        DCD     UART2_TFEINTR_IRQHandler   ; 128
        DCD     UART2_RNEINTR_IRQHandler   ; 129
        DCD     UART2_EINTR_IRQHandler     ; 130
        DCD     UART2_RTINTR_IRQHandler    ; 131
        DCD     UART2_TXINTR_IRQHandler    ; 132
        DCD     UART2_RXINTR_IRQHandler    ; 133
        DCD     UART2_MSINTR_IRQHandler    ; 134
        DCD     UART3_IRQHandler           ; 135
        DCD     UART3_TNBSYINTR_IRQHandler ; 136
        DCD     UART3_TFEINTR_IRQHandler   ; 137
        DCD     UART3_RNEINTR_IRQHandler   ; 138
        DCD     UART3_EINTR_IRQHandler     ; 139
        DCD     UART3_RTINTR_IRQHandler    ; 140
        DCD     UART3_TXINTR_IRQHandler    ; 141
        DCD     UART3_RXINTR_IRQHandler    ; 142
        DCD     UART3_MSINTR_IRQHandler    ; 143
        DCD     USB_IRQHandler             ; 144
        DCD     MIL0_IRQHandler            ; 145
        DCD     DAC0_IRQHandler            ; 146
        DCD     DAC1_IRQHandler            ; 147
        DCD     DAC2_IRQHandler            ; 148
        DCD     DAC3_IRQHandler            ; 149
        DCD     DAC0_FIFO_IRQHandler       ; 150
        DCD     DAC1_FIFO_IRQHandler       ; 151
        DCD     DAC2_FIFO_IRQHandler       ; 152
        DCD     DAC3_FIFO_IRQHandler       ; 153
        DCD     TIMER0_IRQHandler          ; 154
        DCD     TIMER1_IRQHandler          ; 155
        DCD     TIMER2_IRQHandler          ; 156
        DCD     TIMER3_IRQHandler          ; 157
        DCD     QEP0_IRQHandler            ; 158
        DCD     QEP1_IRQHandler            ; 159
        DCD     0                          ; 160  Reserved
        DCD     0                          ; 161  Reserved
        DCD     CAP0_IRQHandler            ; 162
        DCD     CAP1_IRQHandler            ; 163
        DCD     CAP2_IRQHandler            ; 164
        DCD     CAP3_IRQHandler            ; 165
        DCD     EPWM8_IRQHandler           ; 166
        DCD     EPWM7_IRQHandler           ; 167
        DCD     EPWM6_IRQHandler           ; 168
        DCD     EPWM5_IRQHandler           ; 169
        DCD     EPWM4_IRQHandler           ; 170
        DCD     EPWM3_IRQHandler           ; 171
        DCD     EPWM2_IRQHandler           ; 172
        DCD     EPWM1_IRQHandler           ; 173
        DCD     EPWM0_IRQHandler           ; 174
        DCD     EPWM_TZ8_IRQHandler        ; 175
        DCD     EPWM_TZ7_IRQHandler        ; 176
        DCD     EPWM_TZ6_IRQHandler        ; 177
        DCD     EPWM_TZ5_IRQHandler        ; 178
        DCD     EPWM_TZ4_IRQHandler        ; 179
        DCD     EPWM_TZ3_IRQHandler        ; 180
        DCD     EPWM_TZ2_IRQHandler        ; 181
        DCD     EPWM_TZ1_IRQHandler        ; 182
        DCD     EPWM_TZ0_IRQHandler        ; 183
        DCD     EPWM_FIFO8_IRQHandler      ; 184
        DCD     EPWM_FIFO7_IRQHandler      ; 185
        DCD     EPWM_FIFO6_IRQHandler      ; 186
        DCD     EPWM_FIFO5_IRQHandler      ; 187
        DCD     EPWM_FIFO4_IRQHandler      ; 188
        DCD     EPWM_FIFO3_IRQHandler      ; 189
        DCD     EPWM_FIFO2_IRQHandler      ; 190
        DCD     EPWM_FIFO1_IRQHandler      ; 191
        DCD     EPWM_FIFO0_IRQHandler      ; 192
        DCD     CMP0_IRQHandler            ; 193
        DCD     CMP1_IRQHandler            ; 194
        DCD     CMP2_IRQHandler            ; 195
        DCD     CMP3_IRQHandler            ; 196
        DCD     ADC00_IRQHandler           ; 197
        DCD     ADC_FIFO00_IRQHandler      ; 198
        DCD     ADC01_IRQHandler           ; 199
        DCD     ADC_FIFO01_IRQHandler      ; 200
        DCD     ADC02_IRQHandler           ; 201
        DCD     ADC_FIFO02_IRQHandler      ; 202
        DCD     ADC10_IRQHandler           ; 203
        DCD     ADC_FIFO10_IRQHandler      ; 204
        DCD     ADC11_IRQHandler           ; 205
        DCD     ADC_FIFO11_IRQHandler      ; 206
        DCD     ADC12_IRQHandler           ; 207
        DCD     ADC_FIFO12_IRQHandler      ; 208
        DCD     CRCD_IRQHandler            ; 209
        DCD     CANFD_IRQHandler           ; 210
        DCD     MIL1_IRQHandler            ; 211
        DCD     CRPT_FIFO0_IRQHandler      ; 212
        DCD     CRPT_REG0_IRQHandler       ; 213
        DCD     CRPT_FIFO1_IRQHandler      ; 214
        DCD     CRPT_REG1_IRQHandler       ; 215
        DCD     SDIO_IRQHandler            ; 216
        DCD 	CRPT_LOADDONE_IRQHandler   ; 217
        DCD     0                          ; 218  Reserved
	DCD	CRPT_LOCKEDUP_IRQHandler   ; 219

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0

        LDR     R0, =__vector_table
        LDR     R1, =0xE000ED08
        STR     R0, [R1]

        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK FT_IF0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
FT_IF0_IRQHandler
        B FT_IF0_IRQHandler

        PUBWEAK FT_IF1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
FT_IF1_IRQHandler
        B FT_IF1_IRQHandler

        PUBWEAK FT_IF2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
FT_IF2_IRQHandler
        B FT_IF2_IRQHandler

        PUBWEAK FT_IF3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
FT_IF3_IRQHandler
        B FT_IF3_IRQHandler

        PUBWEAK CLK_IF_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CLK_IF_IRQHandler
        B CLK_IF_IRQHandler
	
	PUBWEAK RTC_IF_IRQHandler
        SECTION .text:CODE:NOROOT(1)
RTC_IF_IRQHandler
        B RTC_IF_IRQHandler

        PUBWEAK BKP_IF_IRQHandler
        SECTION .text:CODE:NOROOT(1)
BKP_IF_IRQHandler
        B BKP_IF_IRQHandler

        PUBWEAK EXT_INTERROR0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR0_IRQHandler
        B EXT_INTERROR0_IRQHandler

        PUBWEAK EXT_INTERROR1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR1_IRQHandler
        B EXT_INTERROR1_IRQHandler

        PUBWEAK EXT_INTERROR2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR2_IRQHandler
        B EXT_INTERROR2_IRQHandler

        PUBWEAK EXT_INTERROR3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR3_IRQHandler
        B EXT_INTERROR3_IRQHandler

        PUBWEAK EXT_INTERROR4_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR4_IRQHandler
        B EXT_INTERROR4_IRQHandler

        PUBWEAK EXT_INTERROR5_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR5_IRQHandler
        B EXT_INTERROR5_IRQHandler

        PUBWEAK EXT_INTERROR6_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR6_IRQHandler
        B EXT_INTERROR6_IRQHandler

        PUBWEAK EXT_INTERROR7_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EXT_INTERROR7_IRQHandler
        B EXT_INTERROR7_IRQHandler

        PUBWEAK IF_ERR_SCR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IF_ERR_SCR_IRQHandler
        B IF_ERR_SCR_IRQHandler

        PUBWEAK IF_FIN_SCR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IF_FIN_SCR_IRQHandler
        B IF_FIN_SCR_IRQHandler

        PUBWEAK DMA_ERR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_ERR_IRQHandler
        B DMA_ERR_IRQHandler

        PUBWEAK DMA_DONE0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE0_IRQHandler
        B DMA_DONE0_IRQHandler

        PUBWEAK DMA_DONE1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE1_IRQHandler
        B DMA_DONE1_IRQHandler

        PUBWEAK DMA_DONE2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE2_IRQHandler
        B DMA_DONE2_IRQHandler

        PUBWEAK DMA_DONE3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE3_IRQHandler
        B DMA_DONE3_IRQHandler

        PUBWEAK DMA_DONE4_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE4_IRQHandler
        B DMA_DONE4_IRQHandler

        PUBWEAK DMA_DONE5_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE5_IRQHandler
        B DMA_DONE5_IRQHandler

        PUBWEAK DMA_DONE6_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE6_IRQHandler
        B DMA_DONE6_IRQHandler

        PUBWEAK DMA_DONE7_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE7_IRQHandler
        B DMA_DONE7_IRQHandler

        PUBWEAK DMA_DONE8_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE8_IRQHandler
        B DMA_DONE8_IRQHandler

        PUBWEAK DMA_DONE9_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE9_IRQHandler
        B DMA_DONE9_IRQHandler

        PUBWEAK DMA_DONE10_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE10_IRQHandler
        B DMA_DONE10_IRQHandler

        PUBWEAK DMA_DONE11_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE11_IRQHandler
        B DMA_DONE11_IRQHandler

        PUBWEAK DMA_DONE12_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE12_IRQHandler
        B DMA_DONE12_IRQHandler

        PUBWEAK DMA_DONE13_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE13_IRQHandler
        B DMA_DONE13_IRQHandler

        PUBWEAK DMA_DONE14_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE14_IRQHandler
        B DMA_DONE14_IRQHandler

        PUBWEAK DMA_DONE15_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE15_IRQHandler
        B DMA_DONE15_IRQHandler

        PUBWEAK DMA_DONE16_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE16_IRQHandler
        B DMA_DONE16_IRQHandler

        PUBWEAK DMA_DONE17_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE17_IRQHandler
        B DMA_DONE17_IRQHandler

        PUBWEAK DMA_DONE18_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE18_IRQHandler
        B DMA_DONE18_IRQHandler

        PUBWEAK DMA_DONE19_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE19_IRQHandler
        B DMA_DONE19_IRQHandler

        PUBWEAK DMA_DONE20_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE20_IRQHandler
        B DMA_DONE20_IRQHandler

        PUBWEAK DMA_DONE21_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE21_IRQHandler
        B DMA_DONE21_IRQHandler

        PUBWEAK DMA_DONE22_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE22_IRQHandler
        B DMA_DONE22_IRQHandler

        PUBWEAK DMA_DONE23_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE23_IRQHandler
        B DMA_DONE23_IRQHandler

        PUBWEAK DMA_DONE24_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE24_IRQHandler
        B DMA_DONE24_IRQHandler

        PUBWEAK DMA_DONE25_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE25_IRQHandler
        B DMA_DONE25_IRQHandler

        PUBWEAK DMA_DONE26_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE26_IRQHandler
        B DMA_DONE26_IRQHandler

        PUBWEAK DMA_DONE27_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE27_IRQHandler
        B DMA_DONE27_IRQHandler

        PUBWEAK DMA_DONE28_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE28_IRQHandler
        B DMA_DONE28_IRQHandler

        PUBWEAK DMA_DONE29_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE29_IRQHandler
        B DMA_DONE29_IRQHandler

        PUBWEAK DMA_DONE30_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE30_IRQHandler
        B DMA_DONE30_IRQHandler

        PUBWEAK DMA_DONE31_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DMA_DONE31_IRQHandler
        B DMA_DONE31_IRQHandler

        PUBWEAK IRQ_PORTA_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IRQ_PORTA_IRQHandler
        B IRQ_PORTA_IRQHandler

        PUBWEAK IRQ_PORTB_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IRQ_PORTB_IRQHandler
        B IRQ_PORTB_IRQHandler

        PUBWEAK IRQ_PORTC_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IRQ_PORTC_IRQHandler
        B IRQ_PORTC_IRQHandler

        PUBWEAK IRQ_PORTD_IRQHandler
        SECTION .text:CODE:NOROOT(1)
IRQ_PORTD_IRQHandler
        B IRQ_PORTD_IRQHandler

        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ETH_IRQHandler
        B ETH_IRQHandler

        PUBWEAK CAN0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAN0_IRQHandler
        B CAN0_IRQHandler

        PUBWEAK CAN1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAN1_IRQHandler
        B CAN1_IRQHandler

        PUBWEAK SSP0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_IRQHandler
        B SSP0_IRQHandler

        PUBWEAK SSP0_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_RXINTR_IRQHandler
        B SSP0_RXINTR_IRQHandler

        PUBWEAK SSP0_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_TXINTR_IRQHandler
        B SSP0_TXINTR_IRQHandler

        PUBWEAK SSP0_RORINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_RORINTR_IRQHandler
        B SSP0_RORINTR_IRQHandler

        PUBWEAK SSP0_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_RTINTR_IRQHandler
        B SSP0_RTINTR_IRQHandler

        PUBWEAK SSP0_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_RNEINTR_IRQHandler
        B SSP0_RNEINTR_IRQHandler

        PUBWEAK SSP0_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_TFEINTR_IRQHandler
        B SSP0_TFEINTR_IRQHandler

        PUBWEAK SSP0_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP0_TNBSYINTR_IRQHandler
        B SSP0_TNBSYINTR_IRQHandler

        PUBWEAK SSP1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_IRQHandler
        B SSP1_IRQHandler

        PUBWEAK SSP1_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_RXINTR_IRQHandler
        B SSP1_RXINTR_IRQHandler

        PUBWEAK SSP1_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_TXINTR_IRQHandler
        B SSP1_TXINTR_IRQHandler

        PUBWEAK SSP1_RORINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_RORINTR_IRQHandler
        B SSP1_RORINTR_IRQHandler

        PUBWEAK SSP1_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_RTINTR_IRQHandler
        B SSP1_RTINTR_IRQHandler

        PUBWEAK SSP1_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_RNEINTR_IRQHandler
        B SSP1_RNEINTR_IRQHandler

        PUBWEAK SSP1_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_TFEINTR_IRQHandler
        B SSP1_TFEINTR_IRQHandler

        PUBWEAK SSP1_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SSP1_TNBSYINTR_IRQHandler
        B SSP1_TNBSYINTR_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART0_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_TNBSYINTR_IRQHandler
        B UART0_TNBSYINTR_IRQHandler

        PUBWEAK UART0_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_TFEINTR_IRQHandler
        B UART0_TFEINTR_IRQHandler

        PUBWEAK UART0_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_RNEINTR_IRQHandler
        B UART0_RNEINTR_IRQHandler

        PUBWEAK UART0_EINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_EINTR_IRQHandler
        B UART0_EINTR_IRQHandler

        PUBWEAK UART0_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_RTINTR_IRQHandler
        B UART0_RTINTR_IRQHandler

        PUBWEAK UART0_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_TXINTR_IRQHandler
        B UART0_TXINTR_IRQHandler

        PUBWEAK UART0_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_RXINTR_IRQHandler
        B UART0_RXINTR_IRQHandler

        PUBWEAK UART0_MSINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART0_MSINTR_IRQHandler
        B UART0_MSINTR_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK UART1_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_TNBSYINTR_IRQHandler
        B UART1_TNBSYINTR_IRQHandler

        PUBWEAK UART1_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_TFEINTR_IRQHandler
        B UART1_TFEINTR_IRQHandler

        PUBWEAK UART1_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_RNEINTR_IRQHandler
        B UART1_RNEINTR_IRQHandler

        PUBWEAK UART1_EINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_EINTR_IRQHandler
        B UART1_EINTR_IRQHandler

        PUBWEAK UART1_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_RTINTR_IRQHandler
        B UART1_RTINTR_IRQHandler

        PUBWEAK UART1_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_TXINTR_IRQHandler
        B UART1_TXINTR_IRQHandler

        PUBWEAK UART1_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_RXINTR_IRQHandler
        B UART1_RXINTR_IRQHandler

        PUBWEAK UART1_MSINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART1_MSINTR_IRQHandler
        B UART1_MSINTR_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK UART2_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_TNBSYINTR_IRQHandler
        B UART2_TNBSYINTR_IRQHandler

        PUBWEAK UART2_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_TFEINTR_IRQHandler
        B UART2_TFEINTR_IRQHandler

        PUBWEAK UART2_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_RNEINTR_IRQHandler
        B UART2_RNEINTR_IRQHandler

        PUBWEAK UART2_EINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_EINTR_IRQHandler
        B UART2_EINTR_IRQHandler

        PUBWEAK UART2_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_RTINTR_IRQHandler
        B UART2_RTINTR_IRQHandler

        PUBWEAK UART2_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_TXINTR_IRQHandler
        B UART2_TXINTR_IRQHandler

        PUBWEAK UART2_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_RXINTR_IRQHandler
        B UART2_RXINTR_IRQHandler

        PUBWEAK UART2_MSINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART2_MSINTR_IRQHandler
        B UART2_MSINTR_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK UART3_TNBSYINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_TNBSYINTR_IRQHandler
        B UART3_TNBSYINTR_IRQHandler

        PUBWEAK UART3_TFEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_TFEINTR_IRQHandler
        B UART3_TFEINTR_IRQHandler

        PUBWEAK UART3_RNEINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_RNEINTR_IRQHandler
        B UART3_RNEINTR_IRQHandler

        PUBWEAK UART3_EINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_EINTR_IRQHandler
        B UART3_EINTR_IRQHandler

        PUBWEAK UART3_RTINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_RTINTR_IRQHandler
        B UART3_RTINTR_IRQHandler

        PUBWEAK UART3_TXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_TXINTR_IRQHandler
        B UART3_TXINTR_IRQHandler

        PUBWEAK UART3_RXINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_RXINTR_IRQHandler
        B UART3_RXINTR_IRQHandler

        PUBWEAK UART3_MSINTR_IRQHandler
        SECTION .text:CODE:NOROOT(1)
UART3_MSINTR_IRQHandler
        B UART3_MSINTR_IRQHandler

        PUBWEAK USB_IRQHandler
        SECTION .text:CODE:NOROOT(1)
USB_IRQHandler
        B USB_IRQHandler

        PUBWEAK MIL0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
MIL0_IRQHandler
        B MIL0_IRQHandler

        PUBWEAK DAC0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC0_IRQHandler
        B DAC0_IRQHandler

        PUBWEAK DAC1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC1_IRQHandler
        B DAC1_IRQHandler

        PUBWEAK DAC2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC2_IRQHandler
        B DAC2_IRQHandler

        PUBWEAK DAC3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC3_IRQHandler
        B DAC3_IRQHandler

        PUBWEAK DAC0_FIFO_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC0_FIFO_IRQHandler
        B DAC0_FIFO_IRQHandler

        PUBWEAK DAC1_FIFO_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC1_FIFO_IRQHandler
        B DAC1_FIFO_IRQHandler

        PUBWEAK DAC2_FIFO_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC2_FIFO_IRQHandler
        B DAC2_FIFO_IRQHandler

        PUBWEAK DAC3_FIFO_IRQHandler
        SECTION .text:CODE:NOROOT(1)
DAC3_FIFO_IRQHandler
        B DAC3_FIFO_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

        PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

        PUBWEAK QEP0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
QEP0_IRQHandler
        B QEP0_IRQHandler

        PUBWEAK QEP1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
QEP1_IRQHandler
        B QEP1_IRQHandler

        PUBWEAK CAP0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAP0_IRQHandler
        B CAP0_IRQHandler

        PUBWEAK CAP1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAP1_IRQHandler
        B CAP1_IRQHandler

        PUBWEAK CAP2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAP2_IRQHandler
        B CAP2_IRQHandler

        PUBWEAK CAP3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CAP3_IRQHandler
        B CAP3_IRQHandler

        PUBWEAK EPWM8_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM8_IRQHandler
        B EPWM8_IRQHandler

        PUBWEAK EPWM7_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM7_IRQHandler
        B EPWM7_IRQHandler

        PUBWEAK EPWM6_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM6_IRQHandler
        B EPWM6_IRQHandler

        PUBWEAK EPWM5_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM5_IRQHandler
        B EPWM5_IRQHandler

        PUBWEAK EPWM4_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM4_IRQHandler
        B EPWM4_IRQHandler

        PUBWEAK EPWM3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM3_IRQHandler
        B EPWM3_IRQHandler

        PUBWEAK EPWM2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM2_IRQHandler
        B EPWM2_IRQHandler

        PUBWEAK EPWM1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM1_IRQHandler
        B EPWM1_IRQHandler

        PUBWEAK EPWM0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM0_IRQHandler
        B EPWM0_IRQHandler

        PUBWEAK EPWM_TZ8_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ8_IRQHandler
        B EPWM_TZ8_IRQHandler

        PUBWEAK EPWM_TZ7_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ7_IRQHandler
        B EPWM_TZ7_IRQHandler

        PUBWEAK EPWM_TZ6_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ6_IRQHandler
        B EPWM_TZ6_IRQHandler

        PUBWEAK EPWM_TZ5_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ5_IRQHandler
        B EPWM_TZ5_IRQHandler

        PUBWEAK EPWM_TZ4_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ4_IRQHandler
        B EPWM_TZ4_IRQHandler

        PUBWEAK EPWM_TZ3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ3_IRQHandler
        B EPWM_TZ3_IRQHandler

        PUBWEAK EPWM_TZ2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ2_IRQHandler
        B EPWM_TZ2_IRQHandler

        PUBWEAK EPWM_TZ1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ1_IRQHandler
        B EPWM_TZ1_IRQHandler

        PUBWEAK EPWM_TZ0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_TZ0_IRQHandler
        B EPWM_TZ0_IRQHandler

        PUBWEAK EPWM_FIFO8_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO8_IRQHandler
        B EPWM_FIFO8_IRQHandler

        PUBWEAK EPWM_FIFO7_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO7_IRQHandler
        B EPWM_FIFO7_IRQHandler

        PUBWEAK EPWM_FIFO6_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO6_IRQHandler
        B EPWM_FIFO6_IRQHandler

        PUBWEAK EPWM_FIFO5_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO5_IRQHandler
        B EPWM_FIFO5_IRQHandler

        PUBWEAK EPWM_FIFO4_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO4_IRQHandler
        B EPWM_FIFO4_IRQHandler

        PUBWEAK EPWM_FIFO3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO3_IRQHandler
        B EPWM_FIFO3_IRQHandler

        PUBWEAK EPWM_FIFO2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO2_IRQHandler
        B EPWM_FIFO2_IRQHandler

        PUBWEAK EPWM_FIFO1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO1_IRQHandler
        B EPWM_FIFO1_IRQHandler

        PUBWEAK EPWM_FIFO0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
EPWM_FIFO0_IRQHandler
        B EPWM_FIFO0_IRQHandler

        PUBWEAK CMP0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CMP0_IRQHandler
        B CMP0_IRQHandler

        PUBWEAK CMP1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CMP1_IRQHandler
        B CMP1_IRQHandler

        PUBWEAK CMP2_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CMP2_IRQHandler
        B CMP2_IRQHandler

        PUBWEAK CMP3_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CMP3_IRQHandler
        B CMP3_IRQHandler

        PUBWEAK ADC12_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC12_IRQHandler
        B ADC12_IRQHandler

        PUBWEAK ADC_FIFO12_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO12_IRQHandler
        B ADC_FIFO12_IRQHandler

        PUBWEAK ADC11_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC11_IRQHandler
        B ADC11_IRQHandler

        PUBWEAK ADC_FIFO11_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO11_IRQHandler
        B ADC_FIFO11_IRQHandler

        PUBWEAK ADC10_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC10_IRQHandler
        B ADC10_IRQHandler

        PUBWEAK ADC_FIFO10_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO10_IRQHandler
        B ADC_FIFO10_IRQHandler

        PUBWEAK ADC02_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC02_IRQHandler
        B ADC02_IRQHandler

        PUBWEAK ADC_FIFO02_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO02_IRQHandler
        B ADC_FIFO02_IRQHandler

        PUBWEAK ADC01_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC01_IRQHandler
        B ADC01_IRQHandler

        PUBWEAK ADC_FIFO01_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO01_IRQHandler
        B ADC_FIFO01_IRQHandler

        PUBWEAK ADC00_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC00_IRQHandler
        B ADC00_IRQHandler

        PUBWEAK ADC_FIFO00_IRQHandler
        SECTION .text:CODE:NOROOT(1)
ADC_FIFO00_IRQHandler
        B ADC_FIFO00_IRQHandler

        PUBWEAK CRCD_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CRCD_IRQHandler
        B CRCD_IRQHandler

        PUBWEAK CANFD_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CANFD_IRQHandler
        B CANFD_IRQHandler

        PUBWEAK MIL1_IRQHandler
        SECTION .text:CODE:NOROOT(1)
MIL1_IRQHandler
        B MIL1_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler
        
        PUBWEAK CRPT_FIFO0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CRPT_FIFO0_IRQHandler
        B CRPT_FIFO0_IRQHandler
        
        PUBWEAK CRPT_REG0_IRQHandler
        SECTION .text:CODE:NOROOT(1)
CRPT_REG0_IRQHandler
        B CRPT_REG0_IRQHandler
        
        PUBWEAK CRPT_FIFO1_IRQHandler      
        SECTION .text:CODE:NOROOT(1)
CRPT_FIFO1_IRQHandler      
        B CRPT_FIFO1_IRQHandler      
        
        PUBWEAK CRPT_REG1_IRQHandler      
        SECTION .text:CODE:NOROOT(1)
CRPT_REG1_IRQHandler      
        B CRPT_REG1_IRQHandler 
        
        PUBWEAK CRPT_LOADDONE_IRQHandler      
        SECTION .text:CODE:NOROOT(1)
CRPT_LOADDONE_IRQHandler      
        B CRPT_LOADDONE_IRQHandler
        
        PUBWEAK CRPT_LOCKEDUP_IRQHandler      
        SECTION .text:CODE:NOROOT(1)
CRPT_LOCKEDUP_IRQHandler      
        B CRPT_LOCKEDUP_IRQHandler  

        END
;/******************* (C) COPYRIGHT 2022 Milandr *******************************
;*
;* END OF FILE startup_MLDR32F2C10.s */
