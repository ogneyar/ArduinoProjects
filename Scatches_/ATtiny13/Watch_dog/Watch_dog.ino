
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>

// Variable to store the counted value (uint16_t = unsigned int)
uint16_t counter = 0;

int main(void)
{
 
  DDRB |= (1 << PB2);   // Set PB2 as output, ignore the rest

  DDRB &= ~(1 << PB0);  // Set PB0 as input, ignore the rest
  
  PORTB |= (1 << PB0);    // Enable pullup on PB0

  
  while(PINB & (1 << PB0)) // Wait for PB0 to be pulled down
  {
    PORTB ^= (1 << PB2); //Toggle PB2 while waiting
    _delay_ms(100);
  }


  wdt_enable(WDTO_1S); // Enable WDT with 1 second timeout

  while( ! (PINB & (1 << PB0)) ) // Wait for PB0 to be pulled high
  {
    wdt_reset(); // Reset WDT while PB0 are pulled low
    
    counter++;

    if(counter >= 50000)
    {
      PORTB ^= (1 << PB0); // Toggle PB2 every 50000th time
      counter = 0;
    }
  }

  while(1); // The watchdog will reset the microcontroller after 1 second
}
