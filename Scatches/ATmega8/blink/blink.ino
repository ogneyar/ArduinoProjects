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

#define LED   PC5   // PB1
#define PORT  PORTC // PORTB
#define DDR   DDRC  // DDRB

byte flag = 1;
// функция мигания диода
void led_blink(void){
  if (flag) PORT|=(1<<LED);
  else PORT&=~(1<<LED);        
  flag = !flag;    
  _delay_ms(20);   
}

int main(void) {
  DDR|=(1<<LED);
    
  while (1) {
    led_blink();
  }
}
