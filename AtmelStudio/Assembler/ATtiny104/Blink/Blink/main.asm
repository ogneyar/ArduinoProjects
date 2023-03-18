;
; Blink.asm
;
; Created: 19.02.2023 11:02:52
; Author : Ogneyar
;
; ������������ ������� �� ���������������� ATtiny104
;
.INCLUDE "E:\VSCode\AsmStudy\AVRasm\ATtiny104\libs\tn104def.inc" ; �������� ��������������� ��� ATtiny104 
; #include "../../libs/macro.inc" ; ����������� ����� � ���������

;=================================================
; ����� ���������, � ����� ��������� ���������
	.equ 	F_CPU 					= 1000000		; ������� ��

	.equ 	PA5 					= 5

	.equ 	Delay 					= 100
	.equ 	Number 					= Delay * 1000 / 5
	
;=================================================
; ������� SRAM ������
.DSEG			
;=================================================
; ������� EEPROM ������
.ESEG
;=================================================
; ������� FLASH ������
.CSEG
;=================================================
; ������� ����������
	.ORG 0x000
		RJMP	RESET
		
;=================================================
; ���������� �� ���� ������
; Program_name: .db "Blink on ATtiny104",0

;=================================================
; ���������� �� ������, ��������� ������������� 
RESET:	

;=================================================
	; -- ������������� ����� -- 
	LDI R16, LOW(RAMEND) ; ������� ���� ��������� ������ ��� � R16 
	OUT SPL, R16 ; ��������� �������� ����� ��������� ����� 
	LDI R16, HIGH(RAMEND) ; ������� ���� ��������� ������ ��� � R16 
	OUT SPH, R16 ; ��������� �������� ����� ��������� ����� 

;==============================================================
; ������� ��� � ��������� R0-R31
	LDI		ZL, LOW(SRAM_START)		; ����� ������ ��� � ������
	LDI		ZH, HIGH(SRAM_START)
	CLR		R16					; ������� R16
RAM_Flush:
	ST 		Z+, R16			
	CPI		ZH, HIGH(RAMEND+1)	
	BRNE	RAM_Flush				
	CPI		ZL, LOW(RAMEND+1)	
	BRNE	RAM_Flush
	LDI		ZL, (0x1F-2)			; ����� �������� R29
	CLR		ZH
Reg_Flush:
	ST		Z, ZH
	DEC		ZL
	BRNE	Reg_Flush
	CLR		ZL
	CLR		ZH
	
;==============================================================
	; -- ������������� ��� 5 ����� A �� ����� -- 
	SBI DDRA, PA5 ; 
	
;==============================================================
; -- �������� ���� ��������� -- 
Start: 	
	SBI PORTA, PA5 ; ������ �� ��� PB0 �������� ������ 
	RCALL Wait ; �������� ������� �������� �� ������� 
	CBI PORTA, PA5 ; ������ �� ��� PB0 ������� ������ 
	RCALL Wait ; �������� ������� �������� �� ������� 	
RJMP Start ; ������� � ����� Start, ��������� ��� � ����� 

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
