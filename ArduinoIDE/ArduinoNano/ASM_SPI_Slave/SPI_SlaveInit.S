.global SPI_SlaveInit
.equ DDRB, 0x04
.equ SPCR, 0x2C
; .equ SPE, 6
; .equ MISO, 4


SPI_SlaveInit:
; Настройка ножки порта MISO как выход,
; все остальные сигналы как вход:
   ldi r17, 0b00010000 ; (1 << MISO)
   out DDRB, r17
; Разрешить работу SPI:
   ldi r17, 0b01000000 ; (1 << SPE)
   out SPCR, r17
   ret