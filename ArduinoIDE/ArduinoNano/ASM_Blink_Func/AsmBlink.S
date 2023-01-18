.global D13OnOff
.equ DDRB, 0x04
.equ PORTB, 0x05

D13OnOff:
ldi R16, 1<<5 ; 0b00100000 ; DDRB = (1 << 5)
out DDRB, R16
out PORTB, R24
ret
