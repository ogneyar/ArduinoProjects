;
; USART.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; ������������ USART �� ���������������� ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; ����������� ����� � ���������

;=================================================
; ����� ���������, � ����� ��������� ���������
	.equ 	F_CPU 					= 1000000		; ������� �� ATtiny104
	.equ 	DIVIDER					= 8				; 8 ��� U2X = 1, 16 ��� U2X = 0
	.equ 	BAUD 					= 9600			; �������� ������ �� UART
	.equ 	UBRR 					= F_CPU/DIVIDER/BAUD-1

	.equ 	Delay 					= 500
	.equ 	Number 					= Delay * F_CPU / 1000 / 5

;=================================================
	.def 	Data					= R16			; ������� ������ USART
	.def 	Temp					= R17			; ������� ��� ��������� ������
	.def 	Flag 					= R25 			; ������� ��� �����

;=================================================
; ������� SRAM ������
.DSEG	
;=================================================
; ������� FLASH ������
.CSEG
;=================================================
; ������� ����������
	.ORG 0x00
		RJMP	RESET

;=================================================
	; ���������� �� ���� ������		
	Program_name: .db "Test USART Transmit-Reseive on ATtiny104 ",0
	; Hello_String: 
	; 	.db '\n',"Hello ���! ",'\n','\n'
	; 	.db "����� �������� LED, ������ 1 ",'\n'
	; 	.db "����� �������� LED, ������ 0 ",'\n','\n',0
	; LedOn: .db "LED �������! ",'\n','\n',0
	; LedOff: .db "LED �������! ",'\n','\n',0

;=================================================
	; ����������� ���������
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; ����������� ���������� USART (�� ��������� UBRR)

;=================================================
; ���������� �� ������, ��������� ������������� 
RESET:	
	
;==============================================================
	; -- ������������� ��� 5 ����� A �� ����� -- 
	SBI 	DDRA, 5 ;

	; -- ������������� USART --	
	LDI 	ZL, LOW(UBRR)
	LDI 	ZH, HIGH(UBRR)
	RCALL 	USART_Init 
	
	; ����� � ���� �����������
	;mSetStr	Hello_String
	;RCALL 	USART_Print_String

;=================================================
; �������� ��������� (����)
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
	; ��������� ��������� ������ � \n � \r
	;CPI 	USART_Data, 0xa ; NL (\n)
	;BREQ	Start
	;CPI 	USART_Data, 0xd ; CR (\r)
	;BREQ	Start
	; ��������� ��������� ������ � 0 � 1
	;CPI 	USART_Data, '1'
	;BREQ	Led_ON
	;CPI 	USART_Data, '0'
	;BREQ	Led_OFF
	;RJMP	Continuation
;Led_ON:
	;SBI 	PORTA, PA5 ; ������ �� ��� PA5 �������� ������ 
	;mSetStr LedOn
	;RCALL 	USART_Print_String
	;RJMP	Continuation
;Led_OFF:
	;CBI 	PORTA, PA5 ; ������ �� ��� PA5 ������� ������
	;mSetStr LedOff
	;RCALL 	USART_Print_String
;Continuation:	
	RJMP Start ; ������� � ����� Start, ��������� ��� � ����� 
;=================================================


;==============================================================
; -- ������������ �������� �� ������� -- 
; N = Delay*Fcpu/(r+2) // ��� r � ����� ���������  
; N = D*F/5 // D = 500ms = 0,5s ; F = 1000000 (1 ���)
; N = 100 000 = 0,5 * 1 000 000 / 5    ���  500�� * 1000 / 5  
Wait: ; N = 100000 = 0x0186a0 (500 ����������)
	LDI 	R18, BYTE3(Number) ; 0x01 ; ������� ���� N
	LDI 	R17, HIGH(Number) ; 0x86 ; ������� ���� N
	LDI 	R16, LOW(Number) ; 0xa0 ; ������� ���� N
Loop_Wait: 
	SUBI 	R16, 1 
	SBCI 	R17, 0
	SBCI 	R18, 0
	BRCC 	Loop_Wait
RET ; ������� �� ������������ Wait 

