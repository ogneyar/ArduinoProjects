;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size        EQU     0x00003800
SCB_BASE         EQU     0xE000ED00
;BKP_KEY         EQU     0x8555aaa1
;BKP_BASE_KEY    EQU     0x400010F0
;BKP_RG60_0      EQU     0x40001100
;BKP_RG60_1      EQU     0x40001110
;BKP_RG60_2      EQU     0x40001120


                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB
                
; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                ; Top of Stack
                DCD     Reset_Handler               ; Reset Handler
                DCD     NMI_Handler                 ; NMI Handler
                DCD     HardFault_Handler           ; Hard Fault Handler
                DCD     Default_IRQHandler          ; MPU Fault Handler
                DCD     Default_IRQHandler          ; Bus Fault Handler
                DCD     Default_IRQHandler          ; Usage Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVC_Handler                 ; SVCall Handler
                DCD     Default_IRQHandler          ; Debug Monitor Handler
                DCD     0                           ; Reserved
                DCD     PendSV_Handler              ; PendSV Handler
                DCD     SysTick_Handler             ; SysTick Handler

                ; External interrupts
                DCD     0                           ; 0   Reserved
                DCD     0                           ; 1   Reserved
                DCD     0                           ; 2   Reserved
                DCD     0                           ; 3   Reserved
                DCD     0                           ; 4   Reserved
                DCD     0                           ; 5   Reserved
                DCD     0                           ; 6   Reserved
                DCD     0                           ; 7   Reserved
                DCD     0                           ; 8   Reserved
                DCD     0                           ; 9   Reserved
                DCD     0                           ; 10  Reserved
                DCD     0                           ; 11  Reserved
                DCD     0                           ; 12  Reserved
                DCD     0                           ; 13  Reserved
                DCD     0                           ; 14  Reserved
                DCD     0                           ; 15  Reserved
                DCD     0                           ; 16  Reserved
                DCD     0                           ; 17  Reserved
                DCD     0                           ; 18  Reserved
                DCD     0                           ; 19  Reserved
                DCD     0                           ; 20  Reserved
                DCD     0                           ; 21  Reserved
                DCD     0                           ; 22  Reserved
                DCD     0                           ; 23  Reserved
                DCD     0                           ; 24  Reserved
                DCD     0                           ; 25  Reserved
                DCD     0                           ; 26  Reserved
                DCD     0                           ; 27  Reserved
                DCD     0                           ; 28  Reserved
                DCD     0                           ; 29  Reserved
                DCD     0                           ; 30  Reserved
                DCD     0                           ; 31  Reserved
                DCD     FT_IF0_IRQHandler           ; 32
                DCD     FT_IF1_IRQHandler           ; 33
                DCD     FT_IF2_IRQHandler           ; 34
                DCD     FT_IF3_IRQHandler           ; 35
                DCD     CLK_IF_IRQHandler           ; 36
                DCD     0                           ; 37  Reserved
                DCD     RTC_IF_IRQHandler           ; 38
                DCD     BKP_IF_IRQHandler           ; 39
                DCD     EXT_INTERROR0_IRQHandler    ; 40
                DCD     EXT_INTERROR1_IRQHandler    ; 41
                DCD     EXT_INTERROR2_IRQHandler    ; 42
                DCD     EXT_INTERROR3_IRQHandler    ; 43
                DCD     EXT_INTERROR4_IRQHandler    ; 44
                DCD     EXT_INTERROR5_IRQHandler    ; 45
                DCD     EXT_INTERROR6_IRQHandler    ; 46
                DCD     EXT_INTERROR7_IRQHandler    ; 47
                DCD     IF_ERR_SCR_IRQHandler       ; 48
                DCD     IF_FIN_SCR_IRQHandler       ; 49
                DCD     DMA_ERR_IRQHandler          ; 50
                DCD     DMA_DONE0_IRQHandler        ; 51
                DCD     DMA_DONE1_IRQHandler        ; 52
                DCD     DMA_DONE2_IRQHandler        ; 53
                DCD     DMA_DONE3_IRQHandler        ; 54
                DCD     DMA_DONE4_IRQHandler        ; 55
                DCD     DMA_DONE5_IRQHandler        ; 56
                DCD     DMA_DONE6_IRQHandler        ; 57
                DCD     DMA_DONE7_IRQHandler        ; 58
                DCD     DMA_DONE8_IRQHandler        ; 59
                DCD     DMA_DONE9_IRQHandler        ; 60
                DCD     DMA_DONE10_IRQHandler       ; 61
                DCD     DMA_DONE11_IRQHandler       ; 62
                DCD     DMA_DONE12_IRQHandler       ; 63
                DCD     DMA_DONE13_IRQHandler       ; 64
                DCD     DMA_DONE14_IRQHandler       ; 65
                DCD     DMA_DONE15_IRQHandler       ; 66
                DCD     DMA_DONE16_IRQHandler       ; 67
                DCD     DMA_DONE17_IRQHandler       ; 68
                DCD     DMA_DONE18_IRQHandler       ; 69
                DCD     DMA_DONE19_IRQHandler       ; 70
                DCD     DMA_DONE20_IRQHandler       ; 71
                DCD     DMA_DONE21_IRQHandler       ; 72
                DCD     DMA_DONE22_IRQHandler       ; 73
                DCD     DMA_DONE23_IRQHandler       ; 74
                DCD     DMA_DONE24_IRQHandler       ; 75
                DCD     DMA_DONE25_IRQHandler       ; 76
                DCD     DMA_DONE26_IRQHandler       ; 77
                DCD     DMA_DONE27_IRQHandler       ; 78
                DCD     DMA_DONE28_IRQHandler       ; 79
                DCD     DMA_DONE29_IRQHandler       ; 80
                DCD     DMA_DONE30_IRQHandler       ; 81
                DCD     DMA_DONE31_IRQHandler       ; 82
                DCD     IRQ_PORTA_IRQHandler        ; 83
                DCD     IRQ_PORTB_IRQHandler        ; 84
                DCD     IRQ_PORTC_IRQHandler        ; 85
                DCD     IRQ_PORTD_IRQHandler        ; 86
                DCD     0                           ; 87  Reserved
                DCD     0                           ; 88  Reserved
                DCD     ETH_IRQHandler              ; 89
                DCD     CAN0_IRQHandler             ; 90
                DCD     CAN1_IRQHandler             ; 91
                DCD     SSP0_IRQHandler             ; 92
                DCD     SSP0_RXINTR_IRQHandler      ; 93
                DCD     SSP0_TXINTR_IRQHandler      ; 94
                DCD     SSP0_RORINTR_IRQHandler     ; 95
                DCD     SSP0_RTINTR_IRQHandler      ; 96
                DCD     SSP0_RNEINTR_IRQHandler     ; 97
                DCD     SSP0_TFEINTR_IRQHandler     ; 98
                DCD     SSP0_TNBSYINTR_IRQHandler   ; 99
                DCD     SSP1_IRQHandler             ; 100
                DCD     SSP1_RXINTR_IRQHandler      ; 101
                DCD     SSP1_TXINTR_IRQHandler      ; 102
                DCD     SSP1_RORINTR_IRQHandler     ; 103
                DCD     SSP1_RTINTR_IRQHandler      ; 104
                DCD     SSP1_RNEINTR_IRQHandler     ; 105
                DCD     SSP1_TFEINTR_IRQHandler     ; 106
                DCD     SSP1_TNBSYINTR_IRQHandler   ; 107
                DCD     UART0_IRQHandler            ; 108
                DCD     UART0_TNBSYINTR_IRQHandler  ; 109
                DCD     UART0_TFEINTR_IRQHandler    ; 110
                DCD     UART0_RNEINTR_IRQHandler    ; 111
                DCD     UART0_EINTR_IRQHandler      ; 112
                DCD     UART0_RTINTR_IRQHandler     ; 113
                DCD     UART0_TXINTR_IRQHandler     ; 114
                DCD     UART0_RXINTR_IRQHandler     ; 115
                DCD     UART0_MSINTR_IRQHandler     ; 116
                DCD     UART1_IRQHandler            ; 117
                DCD     UART1_TNBSYINTR_IRQHandler  ; 118
                DCD     UART1_TFEINTR_IRQHandler    ; 119
                DCD     UART1_RNEINTR_IRQHandler    ; 120
                DCD     UART1_EINTR_IRQHandler      ; 121
                DCD     UART1_RTINTR_IRQHandler     ; 122
                DCD     UART1_TXINTR_IRQHandler     ; 123
                DCD     UART1_RXINTR_IRQHandler     ; 124
                DCD     UART1_MSINTR_IRQHandler     ; 125
                DCD     UART2_IRQHandler            ; 126
                DCD     UART2_TNBSYINTR_IRQHandler  ; 127
                DCD     UART2_TFEINTR_IRQHandler    ; 128
                DCD     UART2_RNEINTR_IRQHandler    ; 129
                DCD     UART2_EINTR_IRQHandler      ; 130
                DCD     UART2_RTINTR_IRQHandler     ; 131
                DCD     UART2_TXINTR_IRQHandler     ; 132
                DCD     UART2_RXINTR_IRQHandler     ; 133
                DCD     UART2_MSINTR_IRQHandler     ; 134
                DCD     UART3_IRQHandler            ; 135
                DCD     UART3_TNBSYINTR_IRQHandler  ; 136
                DCD     UART3_TFEINTR_IRQHandler    ; 137
                DCD     UART3_RNEINTR_IRQHandler    ; 138
                DCD     UART3_EINTR_IRQHandler      ; 139
                DCD     UART3_RTINTR_IRQHandler     ; 140
                DCD     UART3_TXINTR_IRQHandler     ; 141
                DCD     UART3_RXINTR_IRQHandler     ; 142
                DCD     UART3_MSINTR_IRQHandler     ; 143
                DCD     USB_IRQHandler              ; 144
                DCD     MIL0_IRQHandler             ; 145
                DCD     DAC0_IRQHandler             ; 146
                DCD     DAC1_IRQHandler             ; 147
                DCD     DAC2_IRQHandler             ; 148
                DCD     DAC3_IRQHandler             ; 149
                DCD     DAC0_FIFO_IRQHandler        ; 150
                DCD     DAC1_FIFO_IRQHandler        ; 151
                DCD     DAC2_FIFO_IRQHandler        ; 152
                DCD     DAC3_FIFO_IRQHandler        ; 153
                DCD     TIMER0_IRQHandler           ; 154
                DCD     TIMER1_IRQHandler           ; 155
                DCD     TIMER2_IRQHandler           ; 156
                DCD     TIMER3_IRQHandler           ; 157
                DCD     QEP0_IRQHandler             ; 158
                DCD     QEP1_IRQHandler             ; 159
                DCD     0                           ; 160 Reserved
                DCD     0                           ; 161 Reserved
                DCD     CAP0_IRQHandler             ; 162
                DCD     CAP1_IRQHandler             ; 163
                DCD     CAP2_IRQHandler             ; 164
                DCD     CAP3_IRQHandler             ; 165
                DCD     EPWM8_IRQHandler            ; 166
                DCD     EPWM7_IRQHandler            ; 167
                DCD     EPWM6_IRQHandler            ; 168
                DCD     EPWM5_IRQHandler            ; 169
                DCD     EPWM4_IRQHandler            ; 170
                DCD     EPWM3_IRQHandler            ; 171
                DCD     EPWM2_IRQHandler            ; 172
                DCD     EPWM1_IRQHandler            ; 173
                DCD     EPWM0_IRQHandler            ; 174
                DCD     EPWM_TZ8_IRQHandler         ; 175
                DCD     EPWM_TZ7_IRQHandler         ; 176
                DCD     EPWM_TZ6_IRQHandler         ; 177
                DCD     EPWM_TZ5_IRQHandler         ; 178
                DCD     EPWM_TZ4_IRQHandler         ; 179
                DCD     EPWM_TZ3_IRQHandler         ; 180
                DCD     EPWM_TZ2_IRQHandler         ; 181
                DCD     EPWM_TZ1_IRQHandler         ; 182
                DCD     EPWM_TZ0_IRQHandler         ; 183
                DCD     EPWM_FIFO8_IRQHandler       ; 184
                DCD     EPWM_FIFO7_IRQHandler       ; 185
                DCD     EPWM_FIFO6_IRQHandler       ; 186
                DCD     EPWM_FIFO5_IRQHandler       ; 187
                DCD     EPWM_FIFO4_IRQHandler       ; 188
                DCD     EPWM_FIFO3_IRQHandler       ; 189
                DCD     EPWM_FIFO2_IRQHandler       ; 190
                DCD     EPWM_FIFO1_IRQHandler       ; 191
                DCD     EPWM_FIFO0_IRQHandler       ; 192
                DCD     CMP0_IRQHandler             ; 193
                DCD     CMP1_IRQHandler             ; 194
                DCD     CMP2_IRQHandler             ; 195
                DCD     CMP3_IRQHandler             ; 196
                DCD     ADC00_IRQHandler            ; 197
                DCD     ADC_FIFO00_IRQHandler       ; 198
                DCD     ADC01_IRQHandler            ; 199
                DCD     ADC_FIFO01_IRQHandler       ; 200
                DCD     ADC02_IRQHandler            ; 201
                DCD     ADC_FIFO02_IRQHandler       ; 202
                DCD     ADC10_IRQHandler            ; 203
                DCD     ADC_FIFO10_IRQHandler       ; 204
                DCD     ADC11_IRQHandler            ; 205
                DCD     ADC_FIFO11_IRQHandler       ; 206
                DCD     ADC12_IRQHandler            ; 207
                DCD     ADC_FIFO12_IRQHandler       ; 208
                DCD     CRDC_IRQHandler             ; 209
                DCD     CANFD_IRQHandler            ; 210
                DCD     MIL1_IRQHandler             ; 211
                DCD     CRPT_FIFO0_IRQHandler       ; 212
                DCD     CRPT_REG0_IRQHandler        ; 213
                DCD     CRPT_FIFO1_IRQHandler       ; 214
                DCD     CRPT_REG1_IRQHandler        ; 215
                DCD     SDIO_IRQHandler             ; 216
                DCD     CRPT_LOADDONE_IRQHandler    ; 217
                DCD     0                           ; 218 Reserved
                DCD     CRPT_LOCKEDUP_IRQHandler    ; 219

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler           [WEAK]
                IMPORT  __main

                LDR     r1, =(SCB_BASE)
                
                LDR     r0, [r1, #0x88]
                ORR     R0,R0,#(3 << 20) ; SCB_CPACR_FPU
                STR     r0, [r1, #0x88]

                LDR     R0,=__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP

HardFault_Handler     PROC
                EXPORT  HardFault_Handler				[WEAK]
                B       .
                ENDP

Default_IRQHandler PROC
                EXPORT  Default_IRQHandler      [WEAK]
                BKPT #01
;                B       .
				BX      LR
                ENDP
					
SVC_Handler     PROC
                EXPORT  SVC_Handler						[WEAK]
                B       .
                ENDP

PendSV_Handler     PROC
                EXPORT  PendSV_Handler					[WEAK]
                B       .
                ENDP

SysTick_Handler     PROC
                EXPORT  SysTick_Handler					[WEAK]
                B       .
                ENDP					
					
					
FT_IF0_IRQHandler	PROC
                EXPORT  FT_IF0_IRQHandler	[WEAK]
				B       .
                ENDP		

FT_IF1_IRQHandler	PROC
                EXPORT  FT_IF1_IRQHandler	[WEAK]
				B       .
                ENDP	
					
FT_IF2_IRQHandler	PROC
                EXPORT  FT_IF2_IRQHandler	[WEAK]
				B       .
                ENDP	
					
FT_IF3_IRQHandler	PROC
                EXPORT  FT_IF3_IRQHandler	[WEAK]
				B       .
                ENDP	

CLK_IF_IRQHandler	PROC
                EXPORT  CLK_IF_IRQHandler	[WEAK]
				B       .
                ENDP
					
RTC_IF_IRQHandler	PROC
                EXPORT  RTC_IF_IRQHandler	[WEAK]
				B       .
                ENDP
					
BKP_IF_IRQHandler	PROC
                EXPORT  BKP_IF_IRQHandler	[WEAK]
				B       .
                ENDP

EXT_INTERROR0_IRQHandler	PROC
                EXPORT  EXT_INTERROR0_IRQHandler	[WEAK]
				B       .
                ENDP
					
EXT_INTERROR1_IRQHandler	PROC
                EXPORT  EXT_INTERROR1_IRQHandler	[WEAK]
				B       .
                ENDP

EXT_INTERROR2_IRQHandler	PROC
                EXPORT  EXT_INTERROR2_IRQHandler	[WEAK]
				B       .
                ENDP
					
EXT_INTERROR3_IRQHandler	PROC
                EXPORT  EXT_INTERROR3_IRQHandler	[WEAK]
				B       .
                ENDP

EXT_INTERROR4_IRQHandler	PROC
                EXPORT  EXT_INTERROR4_IRQHandler	[WEAK]
				B       .
                ENDP
					
EXT_INTERROR5_IRQHandler	PROC
                EXPORT  EXT_INTERROR5_IRQHandler	[WEAK]
				B       .
                ENDP

EXT_INTERROR6_IRQHandler	PROC
                EXPORT  EXT_INTERROR6_IRQHandler	[WEAK]
				B       .
                ENDP
					
EXT_INTERROR7_IRQHandler	PROC
                EXPORT  EXT_INTERROR7_IRQHandler	[WEAK]
				B       .
                ENDP					

IF_ERR_SCR_IRQHandler	PROC
                EXPORT  IF_ERR_SCR_IRQHandler	[WEAK]
				B       .
                ENDP	
					
IF_FIN_SCR_IRQHandler	PROC
                EXPORT  IF_FIN_SCR_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_ERR_IRQHandler	PROC
                EXPORT  DMA_ERR_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE0_IRQHandler	PROC
                EXPORT  DMA_DONE0_IRQHandler	[WEAK]
				B       .
                ENDP					

DMA_DONE1_IRQHandler	PROC
                EXPORT  DMA_DONE1_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE2_IRQHandler	PROC
                EXPORT  DMA_DONE2_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE3_IRQHandler	PROC
                EXPORT  DMA_DONE3_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE4_IRQHandler	PROC
                EXPORT  DMA_DONE4_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE5_IRQHandler	PROC
                EXPORT  DMA_DONE5_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE6_IRQHandler	PROC
                EXPORT  DMA_DONE6_IRQHandler	[WEAK]
				B       .
                ENDP					

DMA_DONE7_IRQHandler	PROC
                EXPORT  DMA_DONE7_IRQHandler	[WEAK]
				B       .
                ENDP	 
 
DMA_DONE8_IRQHandler	PROC
                EXPORT  DMA_DONE8_IRQHandler	[WEAK]
				B       .
                ENDP	

DMA_DONE9_IRQHandler	PROC
                EXPORT  DMA_DONE9_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE10_IRQHandler	PROC
                EXPORT  DMA_DONE10_IRQHandler	[WEAK]
				B       .
                ENDP						
 
DMA_DONE11_IRQHandler	PROC
                EXPORT  DMA_DONE11_IRQHandler	[WEAK]
				B       .
                ENDP 
 
DMA_DONE12_IRQHandler	PROC
                EXPORT  DMA_DONE12_IRQHandler	[WEAK]
				B       .
                ENDP 

DMA_DONE13_IRQHandler	PROC
                EXPORT  DMA_DONE13_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE14_IRQHandler	PROC
                EXPORT  DMA_DONE14_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE15_IRQHandler	PROC
                EXPORT  DMA_DONE15_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE16_IRQHandler	PROC
                EXPORT  DMA_DONE16_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE17_IRQHandler	PROC
                EXPORT  DMA_DONE17_IRQHandler	[WEAK]
				B       .
                ENDP			

DMA_DONE18_IRQHandler	PROC
                EXPORT  DMA_DONE18_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE19_IRQHandler	PROC
                EXPORT  DMA_DONE19_IRQHandler	[WEAK]
				B       .
                ENDP		

DMA_DONE20_IRQHandler	PROC
                EXPORT  DMA_DONE20_IRQHandler	[WEAK]
				B       .
                ENDP
					
DMA_DONE21_IRQHandler	PROC
                EXPORT  DMA_DONE21_IRQHandler	[WEAK]
				B       .
                ENDP		

DMA_DONE22_IRQHandler	PROC
                EXPORT  DMA_DONE22_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE23_IRQHandler	PROC
                EXPORT  DMA_DONE23_IRQHandler	[WEAK]
				B       .
                ENDP		

DMA_DONE24_IRQHandler	PROC
                EXPORT  DMA_DONE24_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE25_IRQHandler	PROC
                EXPORT  DMA_DONE25_IRQHandler	[WEAK]
				B       .
                ENDP

DMA_DONE26_IRQHandler	PROC
                EXPORT  DMA_DONE26_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE27_IRQHandler	PROC
                EXPORT  DMA_DONE27_IRQHandler	[WEAK]
				B       .
                ENDP	

DMA_DONE28_IRQHandler	PROC
                EXPORT  DMA_DONE28_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE29_IRQHandler	PROC
                EXPORT  DMA_DONE29_IRQHandler	[WEAK]
				B       .
                ENDP		

DMA_DONE30_IRQHandler	PROC
                EXPORT  DMA_DONE30_IRQHandler	[WEAK]
				B       .
                ENDP	
					
DMA_DONE31_IRQHandler	PROC
                EXPORT  DMA_DONE31_IRQHandler	[WEAK]
				B       .
                ENDP						

IRQ_PORTA_IRQHandler	PROC
                EXPORT  IRQ_PORTA_IRQHandler	[WEAK]
				B       .
                ENDP
					
IRQ_PORTB_IRQHandler	PROC
                EXPORT  IRQ_PORTB_IRQHandler	[WEAK]
				B       .
                ENDP

IRQ_PORTC_IRQHandler	PROC
                EXPORT  IRQ_PORTC_IRQHandler	[WEAK]
				B       .
                ENDP
					
IRQ_PORTD_IRQHandler	PROC
                EXPORT  IRQ_PORTD_IRQHandler	[WEAK]
				B       .
                ENDP					

ETH_IRQHandler	PROC
                EXPORT  ETH_IRQHandler	[WEAK]
				B       .
                ENDP	
					
CAN0_IRQHandler	PROC
                EXPORT  CAN0_IRQHandler	[WEAK]
				B       .
                ENDP	

CAN1_IRQHandler	PROC
                EXPORT  CAN1_IRQHandler	[WEAK]
				B       .
                ENDP	
    
SSP0_IRQHandler	PROC
                EXPORT  SSP0_IRQHandler	[WEAK]
				B       .
                ENDP	
					
SSP0_RXINTR_IRQHandler	PROC
                EXPORT  SSP0_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP	

SSP0_TXINTR_IRQHandler	PROC
                EXPORT  SSP0_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP	

SSP0_RORINTR_IRQHandler	PROC
                EXPORT  SSP0_RORINTR_IRQHandler	[WEAK]
				B       .
                ENDP
   
SSP0_RTINTR_IRQHandler	PROC
                EXPORT  SSP0_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP

SSP0_RNEINTR_IRQHandler	PROC
                EXPORT  SSP0_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP
    
SSP0_TFEINTR_IRQHandler	PROC
                EXPORT  SSP0_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP

SSP0_TNBSYINTR_IRQHandler	PROC
                EXPORT  SSP0_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP

SSP1_IRQHandler	PROC
                EXPORT  SSP1_IRQHandler	[WEAK]
				B       .
                ENDP   

SSP1_RXINTR_IRQHandler	PROC
                EXPORT  SSP1_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP   
           
SSP1_TXINTR_IRQHandler	PROC
                EXPORT  SSP1_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP 

SSP1_RORINTR_IRQHandler	PROC
                EXPORT  SSP1_RORINTR_IRQHandler	[WEAK]
				B       .
                ENDP 
 
SSP1_RTINTR_IRQHandler	PROC
                EXPORT  SSP1_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

SSP1_RNEINTR_IRQHandler	PROC
                EXPORT  SSP1_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

SSP1_TFEINTR_IRQHandler	PROC
                EXPORT  SSP1_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP 

SSP1_TNBSYINTR_IRQHandler	PROC
                EXPORT  SSP1_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP 
   
UART0_IRQHandler	PROC
                EXPORT  UART0_IRQHandler	[WEAK]
				B       .
                ENDP   

UART0_TNBSYINTR_IRQHandler	PROC
                EXPORT  UART0_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP  
  
UART0_TFEINTR_IRQHandler	PROC
                EXPORT  UART0_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP    

UART0_RNEINTR_IRQHandler	PROC
                EXPORT  UART0_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP   
					
UART0_EINTR_IRQHandler	PROC
                EXPORT  UART0_EINTR_IRQHandler	[WEAK]
				B       .
                ENDP   					
 
UART0_RTINTR_IRQHandler	PROC
                EXPORT  UART0_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

UART0_TXINTR_IRQHandler	PROC
                EXPORT  UART0_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP  
					
UART0_RXINTR_IRQHandler	PROC
                EXPORT  UART0_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP  					
  
UART0_MSINTR_IRQHandler	PROC
                EXPORT  UART0_MSINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

UART1_IRQHandler	PROC
                EXPORT  UART1_IRQHandler	[WEAK]
				B       .
                ENDP  
					
UART1_TNBSYINTR_IRQHandler	PROC
                EXPORT  UART1_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP  					
   
UART1_TFEINTR_IRQHandler	PROC
                EXPORT  UART1_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

UART1_RNEINTR_IRQHandler	PROC
                EXPORT  UART1_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP  
					
UART1_EINTR_IRQHandler	PROC
                EXPORT  UART1_EINTR_IRQHandler	[WEAK]
				B       .
                ENDP  					
   
UART1_RTINTR_IRQHandler	PROC
                EXPORT  UART1_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

UART1_TXINTR_IRQHandler	PROC
                EXPORT  UART1_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP  
					
UART1_RXINTR_IRQHandler	PROC
                EXPORT  UART1_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP  					
          
UART1_MSINTR_IRQHandler	PROC
                EXPORT  UART1_MSINTR_IRQHandler	[WEAK]
				B       .
                ENDP 

UART2_IRQHandler	PROC
                EXPORT  UART2_IRQHandler	[WEAK]
				B       .
                ENDP 
					
UART2_TNBSYINTR_IRQHandler	PROC
                EXPORT  UART2_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP 					
  
UART2_TFEINTR_IRQHandler	PROC
                EXPORT  UART2_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP 	

UART2_RNEINTR_IRQHandler	PROC
                EXPORT  UART2_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP 	
    
UART2_EINTR_IRQHandler	PROC
                EXPORT  UART2_EINTR_IRQHandler	[WEAK]
				B       .
                ENDP    
   
UART2_RTINTR_IRQHandler	PROC
                EXPORT  UART2_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP    
   
UART2_TXINTR_IRQHandler	PROC
                EXPORT  UART2_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP           
 
UART2_RXINTR_IRQHandler	PROC
                EXPORT  UART2_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP   

UART2_MSINTR_IRQHandler	PROC
                EXPORT  UART2_MSINTR_IRQHandler	[WEAK]
				B       .
                ENDP   
					
UART3_IRQHandler	PROC
                EXPORT  UART3_IRQHandler	[WEAK]
				B       .
                ENDP   					
  
UART3_TNBSYINTR_IRQHandler	PROC
                EXPORT  UART3_TNBSYINTR_IRQHandler	[WEAK]
				B       .
                ENDP  

UART3_TFEINTR_IRQHandler	PROC
                EXPORT  UART3_TFEINTR_IRQHandler	[WEAK]
				B       .
                ENDP  
					
UART3_RNEINTR_IRQHandler	PROC
                EXPORT  UART3_RNEINTR_IRQHandler	[WEAK]
				B       .
                ENDP  					
   
UART3_EINTR_IRQHandler	PROC
                EXPORT  UART3_EINTR_IRQHandler	[WEAK]
				B       .
                ENDP 

UART3_RTINTR_IRQHandler	PROC
                EXPORT  UART3_RTINTR_IRQHandler	[WEAK]
				B       .
                ENDP 
					
UART3_TXINTR_IRQHandler	PROC
                EXPORT  UART3_TXINTR_IRQHandler	[WEAK]
				B       .
                ENDP 					
   
UART3_RXINTR_IRQHandler	PROC
                EXPORT  UART3_RXINTR_IRQHandler	[WEAK]
				B       .
                ENDP    
          
UART3_MSINTR_IRQHandler	PROC
                EXPORT  UART3_MSINTR_IRQHandler	[WEAK]
				B       .
                ENDP 
  
USB_IRQHandler	PROC
                EXPORT  USB_IRQHandler	[WEAK]
				B       .
                ENDP   
    
MIL0_IRQHandler	PROC
                EXPORT  MIL0_IRQHandler	[WEAK]
				B       .
                ENDP 

DAC0_IRQHandler	PROC
                EXPORT  DAC0_IRQHandler	[WEAK]
				B       .
                ENDP 
					
DAC1_IRQHandler	PROC
                EXPORT  DAC1_IRQHandler	[WEAK]
				B       .
                ENDP 	

DAC2_IRQHandler	PROC
                EXPORT  DAC2_IRQHandler	[WEAK]
				B       .
                ENDP 
					
DAC3_IRQHandler	PROC
                EXPORT  DAC3_IRQHandler	[WEAK]
				B       .
                ENDP 

DAC0_FIFO_IRQHandler	PROC
                EXPORT  DAC0_FIFO_IRQHandler	[WEAK]
				B       .
                ENDP 
   
DAC1_FIFO_IRQHandler	PROC
                EXPORT  DAC1_FIFO_IRQHandler	[WEAK]
				B       .
                ENDP 

DAC2_FIFO_IRQHandler	PROC
                EXPORT  DAC2_FIFO_IRQHandler	[WEAK]
				B       .
                ENDP 
					
DAC3_FIFO_IRQHandler	PROC
                EXPORT  DAC3_FIFO_IRQHandler	[WEAK]
				B       .
                ENDP 					
           
TIMER0_IRQHandler	PROC
                EXPORT  TIMER0_IRQHandler	[WEAK]
				B       .
                ENDP 

TIMER1_IRQHandler	PROC
                EXPORT  TIMER1_IRQHandler	[WEAK]
				B       .
                ENDP 
					
TIMER2_IRQHandler	PROC
                EXPORT  TIMER2_IRQHandler	[WEAK]
				B       .
                ENDP 					
      
TIMER3_IRQHandler	PROC
                EXPORT  TIMER3_IRQHandler	[WEAK]
				B       .
                ENDP       
      
QEP0_IRQHandler	PROC
                EXPORT  QEP0_IRQHandler	[WEAK]
				B       .
                ENDP   

QEP1_IRQHandler	PROC
                EXPORT  QEP1_IRQHandler	[WEAK]
				B       .
                ENDP   
					
CAP0_IRQHandler	PROC
                EXPORT  CAP0_IRQHandler	[WEAK]
				B       .
                ENDP   

CAP1_IRQHandler	PROC
                EXPORT  CAP1_IRQHandler	[WEAK]
				B       .
                ENDP   
           
CAP2_IRQHandler	PROC
                EXPORT  CAP2_IRQHandler	[WEAK]
				B       .
                ENDP  

CAP3_IRQHandler	PROC
                EXPORT  CAP3_IRQHandler	[WEAK]
				B       .
                ENDP  
					
EPWM8_IRQHandler	PROC
                EXPORT  EPWM8_IRQHandler	[WEAK]
				B       .
                ENDP  					
           
EPWM7_IRQHandler	PROC
                EXPORT  EPWM7_IRQHandler	[WEAK]
				B       .
                ENDP  

EPWM6_IRQHandler	PROC
                EXPORT  EPWM6_IRQHandler	[WEAK]
				B       .
                ENDP  
					
EPWM5_IRQHandler	PROC
                EXPORT  EPWM5_IRQHandler	[WEAK]
				B       .
                ENDP  

EPWM4_IRQHandler	PROC
                EXPORT  EPWM4_IRQHandler	[WEAK]
				B       .
                ENDP  
					
EPWM3_IRQHandler	PROC
                EXPORT  EPWM3_IRQHandler	[WEAK]
				B       .
                ENDP  

EPWM2_IRQHandler	PROC
                EXPORT  EPWM2_IRQHandler	[WEAK]
				B       .
                ENDP  
					
EPWM1_IRQHandler	PROC
                EXPORT  EPWM1_IRQHandler	[WEAK]
				B       .
                ENDP  

EPWM0_IRQHandler	PROC
                EXPORT  EPWM0_IRQHandler	[WEAK]
				B       .
                ENDP  
           
EPWM_TZ8_IRQHandler	PROC
                EXPORT  EPWM_TZ8_IRQHandler	[WEAK]
				B       .
                ENDP       

EPWM_TZ7_IRQHandler	PROC
                EXPORT  EPWM_TZ7_IRQHandler	[WEAK]
				B       .
                ENDP
					
EPWM_TZ6_IRQHandler	PROC
                EXPORT  EPWM_TZ6_IRQHandler	[WEAK]
				B       .
                ENDP

EPWM_TZ5_IRQHandler	PROC
                EXPORT  EPWM_TZ5_IRQHandler	[WEAK]
				B       .
                ENDP
					
EPWM_TZ4_IRQHandler	PROC
                EXPORT  EPWM_TZ4_IRQHandler	[WEAK]
				B       .
                ENDP

EPWM_TZ3_IRQHandler	PROC
                EXPORT  EPWM_TZ3_IRQHandler	[WEAK]
				B       .
                ENDP
					
EPWM_TZ2_IRQHandler	PROC
                EXPORT  EPWM_TZ2_IRQHandler	[WEAK]
				B       .
                ENDP

EPWM_TZ1_IRQHandler	PROC
                EXPORT  EPWM_TZ1_IRQHandler	[WEAK]
				B       .
                ENDP
					
EPWM_TZ0_IRQHandler	PROC
                EXPORT  EPWM_TZ0_IRQHandler	[WEAK]
				B       .
                ENDP					

EPWM_FIFO8_IRQHandler	PROC
                EXPORT  EPWM_FIFO8_IRQHandler	[WEAK]
				B       .
                ENDP 
					
EPWM_FIFO7_IRQHandler	PROC
                EXPORT  EPWM_FIFO7_IRQHandler	[WEAK]
				B       .
                ENDP 

EPWM_FIFO6_IRQHandler	PROC
                EXPORT  EPWM_FIFO6_IRQHandler	[WEAK]
				B       .
                ENDP 
					
EPWM_FIFO5_IRQHandler	PROC
                EXPORT  EPWM_FIFO5_IRQHandler	[WEAK]
				B       .
                ENDP 

EPWM_FIFO4_IRQHandler	PROC
                EXPORT  EPWM_FIFO4_IRQHandler	[WEAK]
				B       .
                ENDP 
					
EPWM_FIFO3_IRQHandler	PROC
                EXPORT  EPWM_FIFO3_IRQHandler	[WEAK]
				B       .
                ENDP 

EPWM_FIFO2_IRQHandler	PROC
                EXPORT  EPWM_FIFO2_IRQHandler	[WEAK]
				B       .
                ENDP 
					
EPWM_FIFO1_IRQHandler	PROC
                EXPORT  EPWM_FIFO1_IRQHandler	[WEAK]
				B       .
                ENDP 

EPWM_FIFO0_IRQHandler	PROC
                EXPORT  EPWM_FIFO0_IRQHandler	[WEAK]
				B       .
                ENDP 

CMP0_IRQHandler	PROC
                EXPORT  CMP0_IRQHandler	[WEAK]
				B       .
                ENDP 
					
CMP1_IRQHandler	PROC
                EXPORT  CMP1_IRQHandler	[WEAK]
				B       .
                ENDP 

CMP2_IRQHandler	PROC
                EXPORT  CMP2_IRQHandler	[WEAK]
				B       .
                ENDP 
					
CMP3_IRQHandler	PROC
                EXPORT  CMP3_IRQHandler	[WEAK]
				B       .
                ENDP 					

ADC00_IRQHandler	PROC
                EXPORT  ADC00_IRQHandler	[WEAK]
				B       .
                ENDP 

ADC_FIFO00_IRQHandler	PROC
                EXPORT  ADC_FIFO00_IRQHandler	[WEAK]
				B       .
                ENDP 
					
ADC01_IRQHandler	PROC
                EXPORT  ADC01_IRQHandler	[WEAK]
				B       .
                ENDP 					
     
ADC_FIFO01_IRQHandler	PROC
                EXPORT  ADC_FIFO01_IRQHandler	[WEAK]
				B       .
                ENDP 	

ADC02_IRQHandler	PROC
                EXPORT  ADC02_IRQHandler	[WEAK]
				B       .
                ENDP 	
					
ADC_FIFO02_IRQHandler	PROC
                EXPORT  ADC_FIFO02_IRQHandler	[WEAK]
				B       .
                ENDP 						
 
ADC10_IRQHandler	PROC
                EXPORT  ADC10_IRQHandler	[WEAK]
				B       .
                ENDP 

ADC_FIFO10_IRQHandler	PROC
                EXPORT  ADC_FIFO10_IRQHandler	[WEAK]
				B       .
                ENDP 
					
ADC11_IRQHandler	PROC
                EXPORT  ADC11_IRQHandler	[WEAK]
				B       .
                ENDP 					
 
ADC_FIFO11_IRQHandler	PROC
                EXPORT  ADC_FIFO11_IRQHandler	[WEAK]
				B       .
                ENDP 	

ADC12_IRQHandler	PROC
                EXPORT  ADC12_IRQHandler	[WEAK]
				B       .
                ENDP 	
					
ADC_FIFO12_IRQHandler	PROC
                EXPORT  ADC_FIFO12_IRQHandler	[WEAK]
				B       .
                ENDP 						
 
CRDC_IRQHandler	PROC
                EXPORT  CRDC_IRQHandler	[WEAK]
				B       .
                ENDP       
 
CANFD_IRQHandler	PROC
                EXPORT  CANFD_IRQHandler	[WEAK]
				B       .
                ENDP       
 
MIL1_IRQHandler	PROC
                EXPORT  MIL1_IRQHandler	[WEAK]
				B       .
                ENDP 
		
CRPT_FIFO0_IRQHandler	PROC
                EXPORT  CRPT_FIFO0_IRQHandler	[WEAK]
				B       .
                ENDP 		
		
CRPT_REG0_IRQHandler	PROC
                EXPORT  CRPT_REG0_IRQHandler	[WEAK]
				B       .
                ENDP 
		
CRPT_FIFO1_IRQHandler	PROC
                EXPORT  CRPT_FIFO1_IRQHandler	[WEAK]
				B       .
                ENDP 	
		
CRPT_REG1_IRQHandler	PROC
                EXPORT  CRPT_REG1_IRQHandler	[WEAK]
				B       .
                ENDP 		
 
SDIO_IRQHandler	PROC
                EXPORT  SDIO_IRQHandler	[WEAK]
				B       .
                ENDP     
		
CRPT_LOADDONE_IRQHandler	PROC
                EXPORT  CRPT_LOADDONE_IRQHandler	[WEAK]
				B       .
                ENDP	
		
CRPT_LOCKEDUP_IRQHandler	PROC
                EXPORT  CRPT_LOCKEDUP_IRQHandler	[WEAK]
				B       .
                ENDP	     
       
       


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


              END
