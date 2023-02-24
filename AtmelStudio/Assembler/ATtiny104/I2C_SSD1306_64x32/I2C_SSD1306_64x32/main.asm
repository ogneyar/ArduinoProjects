;
; I2C_SSD1306_64x32.asm
;
; Created: 19.02.2023 11:32:07
; Author : Ogneyar
;
; Тестирование SSD1306 на микроконтроллере ATtiny104

;#pragma AVRPART CORE NEW_INSTRUCTIONS lpm rd,z+

#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\macro.inc" ; подключение файла с макросами
#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\defines.inc"  ; подключение файла 'определений'

;=================================================
; Имена регистров, а также различные константы
	.equ 	F_CPU 					= 1000000		; Частота МК ATtiny104
	.equ 	DIVIDER					= 8				; 8 при U2X = 1, 16 при U2X = 0
	.equ 	BAUD 					= 9600			; Скорость обмена по UART
	.equ 	UBRR 					= F_CPU / DIVIDER / BAUD - 1
	
	.equ 	I2C_DIVIDER				= 1				; делитель
	.equ 	I2C_BAUD 				= 100000		; Скорость обмена по I2C
	.equ 	I2C_UBRR				= F_CPU / I2C_DIVIDER / I2C_BAUD ; количество тиков в 10 мкс (1секунду/100 000) около 100 KHz
	
	.equ 	I2C_Address_Device		= 0x3c							; адрес устройства 
	.equ 	I2C_Address_Write		= (I2C_Address_Device << 1)		; адрес устройства на запись
	.equ 	I2C_Address_Read		= (I2C_Address_Write & 0x01)	; адрес устройства на чтение

	.equ 	eDelay 					= 500
	.equ 	eNumber 				= eDelay * F_CPU / 1000 / 5

;=================================================
	.def 	Data					= R16			; регистр данных USART
	.def 	Ask						= R17			; регистр данных
	.def 	I2C_Address				= R18			; регистр адреса
	;.def 	I2C_Payload				= R18			; регистр данных
	.def 	Counter					= R19			; регистр счёичик
	.def 	Flag					= R20			; регистр для флага
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
	Program_name: .db "OLED SSD1306 I2C on ATtiny104",0

;=================================================
	; Подключение библиотек
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\delay.asm"    ; подключение файла 'задержек'
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\usart.asm"    ; подключение библиотеки USART (ей требуется UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c.asm"    	 ; подключение библиотеки I2C (ей требуется I2C_UBRR)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\i2c_scan.asm" ; подключение библиотеки I2C_SCAN (ей требуется библиотека I2C)
	#include "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\ssd1306.asm"  ; подключение библиотеки ssd1306 (ей требуется библиотека I2C)

;=================================================
; Прерывание по сбросу, стартовая инициализация 
RESET:	
	
;==============================================================
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
		
	; инициализация SSD1306
	RCALL 	SSD1306_Init

	; очистка экрана
	RCALL	SSD1306_Clear
	
	RCALL 	Delay_500ms

	; вывод данных на экран
	LDI 	R16, 0xff
	RCALL 	SSD1306_Send_Data

	RCALL 	Delay_1000ms

	; очистка экрана
	RCALL	SSD1306_Clear
	
	RCALL 	Delay_500ms

	; вывод данных на экран
	LDI 	R16, 0x55
	RCALL 	SSD1306_Send_Data

	; -- устанавливаем пин 5 порта A на вывод -- 
	SBI 	DDRA, 5 ;

;=================================================
; Основная программа (цикл)
Start:	
	SBI 	PORTA, 5 ;
	RCALL 	Delay_500ms
	CBI 	PORTA, 5 ;
	RCALL 	Delay_500ms

	RJMP Start ; возврат к метке Start, повторяем все в цикле 
;=================================================


