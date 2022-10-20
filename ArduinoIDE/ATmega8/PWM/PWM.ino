// ATmega8

// настройки ШИМ
void pwm_ini(void){
  TCCR2|=(1<<WGM20) | (1<<WGM21); // fast pwm
  TCCR2|=(1<<COM21); // пин OC2 не инверсно
  TCCR2|=(1<<CS20); // без делителя
  DDRB|=(1<<PB3); // пин OC2 на выход (PB3) 17-pin
  OCR2=1;// начальная скважность.
}

// настройки ацп
void adc_ini(void){
  ADMUX|=(1<<ADLAR);// удобнее забирать 8-битный результат преобразования
  ADMUX|=(1<<MUX0) | (1<<MUX1); // выбор канала ADC3 (PC3) 26-pin
  ADMUX|=(1<<REFS0); // AVCC with external capacitor at AREF pin
  DDRC&=~(1<<PC3); // пин ADC3 (PC3) на вход // по умолчанию
  ADCSRA|=(1<<ADEN); // включить ацп
  ADCSRA|=(1<<ADPS2); // делитель 16
}

// функция контроля скважности ШИМ в зависимости от результата АЦП
void lamp_control(void){
  ADCSRA|=(1<<ADSC); // запуск преобразования
  while((ADCSRA&(1<<ADSC)));// ожидание окончания преобразования
  OCR2=ADCH;// в регистр сравнения записать результат преобразования 
}


int main(void) {
  
  pwm_ini();// настройка таймера в режиме генерации ШИМ
  adc_ini();// настройка АЦП
    
  while (1) {
    lamp_control(); // работаем
  }

}
