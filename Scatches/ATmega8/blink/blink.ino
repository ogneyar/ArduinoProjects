//ATmega8
//byte LED1 = 9; // 15-pin (PB1)
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


byte flag = 1;
// функция мигания диода
void led_blink(void){
  if (flag) PORTB|=(1<<PB1);
  else PORTB&=~(1<<PB1);        
  flag = !flag;    
  _delay_ms(20);   
}

int main(void) {
  DDRB|=(1<<PB1);
    
  while (1) {
    led_blink();
  }
}
