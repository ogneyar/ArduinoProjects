.global SPI_MasterInit
.equ DDRB, 0x04
.equ SPCR, 0x2C
.equ SPSR, 0x2D
; .equ MOSI, 3
; .equ SCK, 5
; .equ SPE, 6
; .equ MSTR, 4
; .equ SPR0, 0
; .equ SPI2X, 0

SPI_MasterInit:
; Настройка MOSI и SCK как выход, все остальные сигналы как вход:
   ldi r17, 0b00101000 ; (1 << MOSI) | (1 << SCK) 
   out DDRB, r17
; Разрешить работу SPI, режим Master, установить скорость тактов fck/8 для LGT8F328:
   ldi r17, 0b01010001 ; (1 << SPE) | (1 << MSTR) | (1 << SPR1)
   out SPCR, r17   
   ldi r17, 0b00000001 ; (1 << SPI2X)
   out SPSR, r17
   ret
   