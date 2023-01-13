 
 // ATmega328

#define LED   PD0   // PC4   // PB1
#define PORT  PORTD // PORTC // PORTB
#define DDR   DDRD  // DDRC  // DDRB


// функция мигания диода
void _delay(uint32_t del){
  for(uint32_t i=0; i< (del << 7); i++) asm("nop");
}

int main(void) {
  DDR |= (1 << LED);
    
  while (1) {
    PORT ^= (1 << LED); 
    _delay(100);
  }
}
