;
; USART.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; Тестирование USART на микроконтроллере ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; подключение файла с макросами

;=================================================
; Имена регистров, а также различные константы
	.equ 	F_CPU 					= 1000000		; Частота МК ATtiny104
	.equ 	DIVIDER					= 8				; 8 при U2X = 1, 16 при U2X = 0
	.equ 	BAUD 					= 9600			; Скорость обмена по UART
	.equ 	UBRR 					= F_CPU/DIVIDER/BAUD-1

	.equ 	Delay 					= 500
	.equ 	Number 					= Delay * F_CPU / 1000 / 5

;=================================================
	.def 	Data					= R16			; регистр данных USART
	.def 	Temp					= R17			; регистр для временных данных
	.def 	Flag 					= R25 			; регистр для флага

;=================================================
; Сегмент SRAM памяти
.DSEG	
;=================================================
; Сегмент FLASH памяти
.CSEG
;=================================================
; Таблица прерываний
	.ORG 0x00
		RJMP	RESET

;=================================================
	; Переменные во флеш памяти		
	Program_name: .db "Test USART Transmit-Reseive on ATtiny104 ",0
	; Hello_String: 
	; 	.db '\n',"Hello Чел! ",'\n','\n'
	; 	.db "Чтобы включить LED, пришли 1 ",'\n'
	; 	.db "Чтобы погасить LED, пришли 0 ",'\n','\n',0
	; LedOn: .db "LED включен! ",'\n','\n',0
	; LedOff: .db "LED погашен! ",'\n','\n',0

;=================================================
	; Подключение библиотек
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; подключение библиотеки USART (ей требуется UBRR)

;=================================================
; Прерывание по сбросу, стартовая инициализация 
RESET:	
	
;==============================================================
	; -- устанавливаем пин 5 порта A на вывод -- 
	SBI 	DDRA, 5 ;

	; -- инициализация USART --	
	LDI 	ZL, LOW(UBRR)
	LDI 	ZH, HIGH(UBRR)
	RCALL 	USART_Init 
	
	; вывод в порт приветствия
	;mSetStr	Hello_String
	;RCALL 	USART_Print_String

;=================================================
; Основная программа (цикл)
Start:	
	SBI 	PORTA, 5 ;

	LDI 	R16, 'H'
	RCALL 	USART_Transmit
	LDI 	R16, 'e'
	RCALL 	USART_Transmit
	LDI 	R16, 'l'
	RCALL 	USART_Transmit
	LDI 	R16, 'l'
	RCALL 	USART_Transmit
	LDI 	R16, 'o'
	RCALL 	USART_Transmit
	LDI 	R16, ' '
	RCALL 	USART_Transmit

	RCALL 	Wait

	CBI 	PORTA, 5 ;
		
	LDI 	R16, 'W'
	RCALL 	USART_Transmit
	LDI 	R16, 'o'
	RCALL 	USART_Transmit
	LDI 	R16, 'r'
	RCALL 	USART_Transmit
	LDI 	R16, 'l'
	RCALL 	USART_Transmit
	LDI 	R16, 'd'
	RCALL 	USART_Transmit
	LDI 	R16, '!'
	RCALL 	USART_Transmit
	LDI 	R16, '\n'
	RCALL 	USART_Transmit

	RCALL 	Wait

	;RCALL 	USART_Receive
	; сравнение пришедших данных с \n и \r
	;CPI 	USART_Data, 0xa ; NL (\n)
	;BREQ	Start
	;CPI 	USART_Data, 0xd ; CR (\r)
	;BREQ	Start
	; сравнение пришедших данных с 0 и 1
	;CPI 	USART_Data, '1'
	;BREQ	Led_ON
	;CPI 	USART_Data, '0'
	;BREQ	Led_OFF
	;RJMP	Continuation
;Led_ON:
	;SBI 	PORTA, PA5 ; подача на пин PA5 высокого уровня 
	;mSetStr LedOn
	;RCALL 	USART_Print_String
	;RJMP	Continuation
;Led_OFF:
	;CBI 	PORTA, PA5 ; подача на пин PA5 низкого уровня
	;mSetStr LedOff
	;RCALL 	USART_Print_String
;Continuation:	
	RJMP Start ; возврат к метке Start, повторяем все в цикле 
;=================================================


;==============================================================
; -- подпрограмма задержки по времени -- 
; N = Delay*Fcpu/(r+2) // где r — число регистров  
; N = D*F/5 // D = 500ms = 0,5s ; F = 1000000 (1 МГц)
; N = 100 000 = 0,5 * 1 000 000 / 5    или  500мс * 1000 / 5  
Wait: ; N = 100000 = 0x0186a0 (500 милисекунд)
	LDI 	R18, BYTE3(Number) ; 0x01 ; старший байт N
	LDI 	R17, HIGH(Number) ; 0x86 ; средний байт N
	LDI 	R16, LOW(Number) ; 0xa0 ; младший байт N
Loop_Wait: 
	SUBI 	R16, 1 
	SBCI 	R17, 0
	SBCI 	R18, 0
	BRCC 	Loop_Wait
RET ; возврат из подпрограммы Wait 

