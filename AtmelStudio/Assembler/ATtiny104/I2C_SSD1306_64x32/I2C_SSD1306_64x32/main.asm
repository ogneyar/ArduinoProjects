;
; I2C_SSD1306_64x32.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; ������������ SSD1306 �� ���������������� ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; ����������� ����� � ���������
#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\defines.inc"  ; ����������� ����� '�����������'

;=================================================
; ����� ���������, � ����� ��������� ���������
	.equ 	F_CPU 					= 1000000		; ������� �� ATtiny104
	.equ 	DIVIDER					= 8				; 8 ��� U2X = 1, 16 ��� U2X = 0
	.equ 	BAUD 					= 9600			; �������� ������ �� UART
	.equ 	UBRR 					= F_CPU / DIVIDER / BAUD - 1
	
	.equ 	I2C_DIVIDER				= 1				; ��������
	.equ 	I2C_BAUD 				= 100000		; �������� ������ �� I2C
	.equ 	I2C_UBRR				= F_CPU / I2C_DIVIDER / I2C_BAUD ; ���������� ����� � 10 ��� (1�������/100 000) ����� 100 KHz
	
	.equ 	I2C_Address_Device		= 0x3c							; ����� ���������� 
	.equ 	I2C_Address_Write		= (I2C_Address_Device << 1)		; ����� ���������� �� ������
	.equ 	I2C_Address_Read		= (I2C_Address_Write & 0x01)	; ����� ���������� �� ������

	.equ 	eDelay 					= 500
	.equ 	eNumber 				= eDelay * F_CPU / 1000 / 5

;=================================================
	.def 	Data					= R16			; ������� ������ USART
	.def 	Ask						= R17			; ������� ������
	.def 	I2C_Address				= R18			; ������� ������
	;.def 	I2C_Payload				= R18			; ������� ������
	.def 	Counter					= R19			; ������� �������
	.def 	Flag					= R20			; ������� ��� �����
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
	Program_name: .db "OLED SSD1306 I2C on ATtiny104",0

;=================================================
	; ����������� ���������
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\delay.asm"    ; ����������� ����� '��������'
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; ����������� ���������� USART (�� ��������� UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c.asm"    	 ; ����������� ���������� I2C (�� ��������� I2C_UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c_scan.asm" ; ����������� ���������� I2C_SCAN (�� ��������� ���������� I2C)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\ssd1306.asm"  ; ����������� ���������� ssd1306 (�� ��������� ���������� I2C)

;=================================================
; ���������� �� ������, ��������� ������������� 
RESET:	
	
;==============================================================
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
		
	; ������������� SSD1306
	RCALL 	SSD1306_Init

	; ������� ������
	RCALL	SSD1306_Clear
	
	RCALL 	Delay_500ms

	; ����� ������ �� �����
	LDI 	R16, 0xff
	RCALL 	SSD1306_Send_Data

	RCALL 	Delay_1000ms

	; ������� ������
	RCALL	SSD1306_Clear
	
	RCALL 	Delay_500ms

	; ����� ������ �� �����
	LDI 	R16, 0x55
	RCALL 	SSD1306_Send_Data

	; -- ������������� ��� 5 ����� A �� ����� -- 
	SBI 	DDRA, 5 ;

;=================================================
; �������� ��������� (����)
Start:	
	SBI 	PORTA, 5 ;
	RCALL 	Delay_500ms
	CBI 	PORTA, 5 ;
	RCALL 	Delay_500ms

	RJMP Start ; ������� � ����� Start, ��������� ��� � ����� 
;=================================================


