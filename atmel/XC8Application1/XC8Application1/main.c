
#include <xc.h>
#include <avr/io.h>

int main(void)
{
	DDRC = 0b11111111;
	
    while(1)
    {
        PORTC = 0b0000001;
    }
}