// ATmega8

//byte sensorPin = A2;
//byte ledPin = 11;
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

void settings(void) {
  DDRB|=(1<<PB3); // пин OC2 на выход (PB3) 17-pin
  // настройка АЦП
  ADMUX|=(1<<ADLAR);// удобнее забирать 8-битный результат преобразования
  ADMUX|=(1<<MUX1); // выбор канала ADC2 (PC2) 25-pin A2
  DDRC&=~(1<<PC2); // пин ADC2 (PC2) на вход
  ADMUX|=(1<<REFS0); // AVCC with external capacitor at AREF pin
  ADCSRA|=(1<<ADEN); // включить ацп
  ADCSRA|=(1<<ADPS2); // делитель 16
}


int main(void) {

  settings();
    
  while (1) {
    ADCSRA|=(1<<ADSC); // запуск преобразования
    while((ADCSRA&(1<<ADSC)));// ожидание окончания преобразования
    if (ADCH < 100) PORTB|=(1<<PB3);
    else PORTB&=~(1<<PB3);
  }
}
