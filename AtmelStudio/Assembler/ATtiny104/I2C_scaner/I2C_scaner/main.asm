;
; I2C_scaner.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; ������������ I2C �� ���������������� ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; ����������� ����� � ���������

;=================================================
; ����� ���������, � ����� ��������� ���������
	.equ 	F_CPU 					= 1000000		; ������� �� ATtiny104
	.equ 	DIVIDER					= 8				; 8 ��� U2X = 1, 16 ��� U2X = 0
	.equ 	BAUD 					= 9600			; �������� ������ �� UART
	.equ 	UBRR 					= F_CPU/DIVIDER/BAUD-1
	
	.equ 	I2C_DIVIDER				= 1				; ��������
	.equ 	I2C_BAUD 				= 100000		; �������� ������ �� I2C
	.equ 	I2C_UBRR				= F_CPU/I2C_DIVIDER/I2C_BAUD ; ���������� ����� � 10 ��� (1�������/100 000) ����� 100 KHz
	
;=================================================
	.def 	Data					= R16			; ������� ������ USART
	.def 	Ask						= R17			; ������� ������
	.def 	I2C_Address				= R18			; ������� ������
	.def 	Counter					= R19			; ������� �������
	.def 	Delay 					= R22			; ������� ��������
	.def 	Null 					= R23 			; ������� ��� �����

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
	Program_name: .db "Test I2C scaner on ATtiny104 ",0

;=================================================
	; ����������� ���������
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\delay.asm"    ; ����������� ����� '��������'
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; ����������� ���������� USART (�� ��������� UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c.asm"    	 ; ����������� ���������� I2C (�� ��������� I2C_UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c_scan.asm" ; ����������� ���������� I2C_SCAN (�� ��������� ���������� I2C)

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
	RCALL 	Hello_W
	
	; ������������� I2C
	RCALL 	I2C_Init 

	; -- ����� I2C ��������� --	
	RCALL 	I2C_Scan

;=================================================
; �������� ��������� (����)
Start:	
	SBI 	PORTA, 5 ;
	RCALL 	Delay_500ms
	CBI 	PORTA, 5 ;
	RCALL 	Delay_500ms

	RJMP Start ; ������� � ����� Start, ��������� ��� � ����� 
;=================================================

