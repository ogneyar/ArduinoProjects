
// настройки ШИМ
void pwm_ini(void){
  TCCR0A|=(1<<WGM01) | (1<<WGM00);// fast pwm
  TCCR0A|=(1<<COM0A1); // пин OC0A не инверсно
  TCCR0B|=(1<<CS00); // без делителя
  DDRB|=(1<<PB0); // пин OC0A на выход (PB0)
  OCR0A=100;// начальная скважность.
}

// настройки ацп
void adc_ini(void){
  ADMUX|=(1<<ADLAR);// удобнее забирать 8-битный результат преобразования
  ADMUX|=MUX1; // выбор канала ADC1 (PB2)
  // DDRB&=~(1<<PB2); // пин ADC1 (PB2) на вход // по умолчанию
  ADCSRA|=(1<<ADEN); // включить ацп
  ADCSRA|=(1<<ADPS2); // делитель 16
}

// функция контроля скважности ШИМ в зависимости от результата АЦП
void lamp_control(void){
  ADCSRA|=(1<<ADSC); // запуск преобразования
  while((ADCSRA&(1<<ADSC)));// ожидание окончания преобразования
  OCR0A=ADCH;// в регистр сравнения записать результат преобразования 
}

int main(void) {
  
  pwm_ini();// настройка таймера в режиме генерации ШИМ
  adc_ini();// настройка АЦП
    
  while (1) {
    lamp_control();// работаем
    // сюда можно паузу, чтобы слишком часто не опрашивать ацп
    //delay(5);
  }
  
}
