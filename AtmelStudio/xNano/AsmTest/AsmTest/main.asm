;
; AsmTest.asm
;
; Created: 19.02.2023 9:09:14
; Author : Ogneyar
;

; #include <avr/io.h>

main:
	sbi 0x01, 5 ; DDRA |= (1 << 5);
	;sbi 0x02, 5 ; PORTA |= (1 << 5);
loop:
  ; Loop forever
    rjmp loop