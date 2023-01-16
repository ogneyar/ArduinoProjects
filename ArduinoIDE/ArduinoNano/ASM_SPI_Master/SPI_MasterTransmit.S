.global SPI_MasterTransmit
.equ SPIF, 7
.equ SPDR, 0x2E
.equ SPSR, 0x2D
   
SPI_MasterTransmit:
; Запуск передачи данных (r16): or R24
   out SPDR, r24
Wait_Transmit:
; Ожидание завершения передачи
   in r24, SPSR
   sbrs r24, SPIF
   rjmp Wait_Transmit
   ret
