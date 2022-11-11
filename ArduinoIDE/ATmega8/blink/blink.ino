 //ATmega8

//byte LED1 = 5; // 9 - 15pin (PB1) // 5 - 28pin (PC5)
//byte period = 30;
//
//void setup() {
//  pinMode(LED1, OUTPUT);
//}
//
//void loop() {
//  digitalWrite(LED1, HIGH);
//  delay(period);
//  digitalWrite(LED1, LOW);
//  delay(period);
//}

#define LED   PD0   // PC4   // PB1
#define PORT  PORTD // PORTC // PORTB
#define DDR   DDRD  // DDRC  // DDRB


// функция мигания диода
void led_blink(){
  PORT ^= (1<<LED); 
  //_delay_ms(200);   
  for(uint32_t i=0; i<2000000; i++) asm("nop");
}

int main(void) {
  DDR |= (1<<LED);
    
  while (1) {
    led_blink();
  }
}
