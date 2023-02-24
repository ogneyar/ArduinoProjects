;
; I2C_scaner.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; Тестирование I2C на микроконтроллере ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; подключение файла с макросами

;=================================================
; Имена регистров, а также различные константы
	.equ 	F_CPU 					= 1000000		; Частота МК ATtiny104
	.equ 	DIVIDER					= 8				; 8 при U2X = 1, 16 при U2X = 0
	.equ 	BAUD 					= 9600			; Скорость обмена по UART
	.equ 	UBRR 					= F_CPU/DIVIDER/BAUD-1
	
	.equ 	I2C_DIVIDER				= 1				; делитель
	.equ 	I2C_BAUD 				= 100000		; Скорость обмена по I2C
	.equ 	I2C_UBRR				= F_CPU/I2C_DIVIDER/I2C_BAUD ; количество тиков в 10 мкс (1секунду/100 000) около 100 KHz
	
;=================================================
	.def 	Data					= R16			; регистр данных USART
	.def 	Ask						= R17			; регистр данных
	.def 	I2C_Address				= R18			; регистр адреса
	.def 	Counter					= R19			; регистр счёичик
	.def 	Delay 					= R22			; регистр задержки
	.def 	Null 					= R23 			; регистр для флага

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
	Program_name: .db "Test I2C scaner on ATtiny104 ",0

;=================================================
	; Подключение библиотек
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\delay.asm"    ; подключение файла 'задержек'
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; подключение библиотеки USART (ей требуется UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c.asm"    	 ; подключение библиотеки I2C (ей требуется I2C_UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c_scan.asm" ; подключение библиотеки I2C_SCAN (ей требуется библиотека I2C)

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
	RCALL 	Hello_W
	
	; инициализация I2C
	RCALL 	I2C_Init 

	; -- поиск I2C устройств --	
	RCALL 	I2C_Scan

;=================================================
; Основная программа (цикл)
Start:	
	SBI 	PORTA, 5 ;
	RCALL 	Delay_500ms
	CBI 	PORTA, 5 ;
	RCALL 	Delay_500ms

	RJMP Start ; возврат к метке Start, повторяем все в цикле 
;=================================================

