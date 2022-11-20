
// Nano

void timerCounter2(int = 1024, uint8_t = 240);

uint8_t ocr2a = 10;


int main(void) {  
  timerCounter2(128, ocr2a);
  
  while (1) {}
}


void timerCounter2(int divider, uint8_t ocr) // Timer Counter 2
{  
  TCCR0B |= (1<<CS00); // без этого не работает Timer Counter 2
  // Timer Counter 2 Control Register A
  //TCCR2A |= (1<<WGM21); // выбор режима - CTC
  TCCR2A |= (1<<WGM21) | (1<<WGM20); // выбор режима - Fast PWM
  //TCCR2A |= (1<<WGM20); // выбор режима - fase correct PWMOCRA
  
  //TCCR2A |= (1<<COM2A0); // toggle
  TCCR2A |= (1<<COM2A1); // сброс по совпадению 
  //TCCR2A |= (1<<COM2A1) | (1<<COM2A0); // установка по сопадению 

  //TCCR2B |= (1<<WGM22); // top OCRA
    
  // Timer Counter 2 Control Register B
  if (divider == 0) TCCR2B |= (1<<CS20); // без делителя (0b001)
  else if (divider == 8) TCCR2B |= (1<<CS21); // делитель на 8 (0b010)
  else if (divider == 32) TCCR2B |= (1<<CS20) | (1<<CS21); // делитель на 32 (0b011)
  else if (divider == 64) TCCR2B |= (1<<CS22); // делитель на 64 (0b100)
  else if (divider == 128) TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128 (0b101)
  else if (divider == 256) TCCR2B |= (1<<CS21) | (1<<CS22); // делитель на 256 (0b110)
  else TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22); // делитель на 1024 (0b111)
  
  // Output Compare Register A
	OCR2A = ocr; // регистр сравнения
         
  DDRB |= (1<<PB3); // пин OC2A на выход (11 пин ардуины)
}
