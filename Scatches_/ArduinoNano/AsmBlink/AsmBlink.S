.global D13OnOff
.equ DDRB, 0x04
.equ PORTB, 0x05

D13OnOff:
ldi R16, 0b00100000
out DDRB, R16
out PORTB, R24
ret