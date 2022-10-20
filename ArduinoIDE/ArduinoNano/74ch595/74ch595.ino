 //Arduino Nano 

byte takt = 3;
byte ds = 4;
byte enter = 5;
byte period = 5;
boolean flag = true;

void setup() {
  pinMode(takt, OUTPUT);
  pinMode(ds, OUTPUT);
  pinMode(enter, OUTPUT);
}

void loop() {
  if (flag) {
    digitalWrite(ds, HIGH);
    delay(period);
  }else {
    digitalWrite(ds, LOW);
    delay(period);
  }
  
  digitalWrite(takt, HIGH);
  delay(period);
  digitalWrite(takt, LOW);
  delay(period);

  
  digitalWrite(enter, HIGH);
  delay(period);
  digitalWrite(enter, LOW);
  delay(period);

  
  flag = !flag;
  
//  delay(period);
}


// так ещё не пробовал
//#define LED   PC4   // PB1
//#define PORT  PORTC // PORTB
//#define DDR   DDRC  // DDRB
//
//byte flag = 1;
//// функция мигания диода
//void led_blink(void){
//  if (flag) PORT|=(1<<LED);
//  else PORT&=~(1<<LED);        
//  flag = !flag;    
//  _delay_ms(200);   
//}
//
//int main(void) {
//  DDR|=(1<<LED);
//    
//  while (1) {
//    led_blink();
//  }
//}
