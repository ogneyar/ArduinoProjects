
// Nano

// шим на PB3 (11 пин ардуины)

void timerCounter2(int = 1024, uint8_t = 240);

uint8_t ocr2a = 100;


int main(void) {  
  timerCounter2(128, ocr2a);  
  DDRB |= (1<<PB5); // пин PB5 на выход (13 пин ардуины)
  while (1) {
    //PORTB |= ((PINB & PB3)<<PB5);
    // digitalWrite(13, digitalRead(11));
    PORTB ^= (1<<PB5);
    _delay_ms(100);
  }
}


void timerCounter2(int divider, uint8_t ocr) // Timer Counter 2
{  
  TCCR0B |= (1<<CS00); // без этого не работает Timer Counter 2
  TCCR2A |= (1<<WGM21) | (1<<WGM20); // выбор режима - Fast PWM
  TCCR2A |= (1<<COM2A1); // сброс по совпадению 
  if (divider == 0) TCCR2B |= (1<<CS20); // без делителя (0b001)
  else if (divider == 8) TCCR2B |= (1<<CS21); // делитель на 8 (0b010)
  else if (divider == 32) TCCR2B |= (1<<CS20) | (1<<CS21); // делитель на 32 (0b011)
  else if (divider == 64) TCCR2B |= (1<<CS22); // делитель на 64 (0b100)
  else if (divider == 128) TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128 (0b101)
  else if (divider == 256) TCCR2B |= (1<<CS21) | (1<<CS22); // делитель на 256 (0b110)
  else TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22); // делитель на 1024 (0b111)
	OCR2A = ocr; // регистр сравнения
  DDRB |= (1<<PB3); // пин OC2A на выход (11 пин ардуины)
}
