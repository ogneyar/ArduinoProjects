// #include <xc.h>
#include <avr/io.h>

// ATtiny13
int main(void)
{
	// 6 pin i/o
	DDRB = 0b00000001; // первый порт на ввод // достаточно 6ти бит 0b000001
	
    while(1)
    {
        // PORTB = 0b000001
		PORTB |= (1 << 0); // PORTB |= 0b00000001 -  нулевой бит в 1
		
		// PORTB = 0b000000;
		PORTB &= ~(1 << 0); // PORTB &= ~0b00000001 - DDRB &= 0b11111110 - нулевой бит в 0
		
    }
}