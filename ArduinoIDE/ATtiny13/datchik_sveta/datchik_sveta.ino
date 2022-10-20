// ATtiny13

//byte sensorPin = 3;
//byte ledPin = 4;
//unsigned int sensor = 0;
//
//void setup() {
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);
//}
//
//void loop() {
//  sensor = analogRead(sensorPin);
//  if (sensor < 400) digitalWrite(ledPin, HIGH);
//  else digitalWrite(ledPin, LOW);
//}

//void settings(void) {
//  DDRB|=(1<<PB4); // пин PB4 на выход 3-pin
//  // настройка АЦП
//  ADMUX|=(1<<ADLAR);// удобнее забирать 8-битный результат преобразования
//  ADMUX|=(1<<MUX0) | (1<<MUX1); // выбор канала ADC3 (PB3) 2-pin
//  ADCSRA|=(1<<ADEN); // включить ацп
//  ADCSRA|=(1<<ADPS2); // делитель 16
//}
//
//
//int main(void) {
//
//  settings();
//    
//  while (1) {
//    ADCSRA|=(1<<ADSC); // запуск преобразования
//    while((ADCSRA&(1<<ADSC)));// ожидание окончания преобразования
//    if (ADCH < 100) PORTB|=(1<<PB4);
//    else PORTB&=~(1<<PB4);
//  }
//}
