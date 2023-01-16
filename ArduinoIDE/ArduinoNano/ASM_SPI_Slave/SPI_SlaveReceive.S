.global SPI_SlaveReceive
.equ SPSR, 0x2D
.equ SPIF, 7
.equ SPDR, 0x2E

  
SPI_SlaveReceive:
; Ожидание завершения приема:
   in r16, SPSR
   sbrs r16, SPIF
   rjmp SPI_SlaveReceive
; Чтение принятых данных и возврат:
   in r16, SPDR
   ret 