
// Nano

// зуммер (buzer) на D11

void timerCounter2(int = 1024);


int main(void) {  
  timerCounter2(128);

  volatile uint8_t ocr2a = 1;
  
  while (1) {
    TCCR2B = 0;
    TCCR2A = 0;
    TCNT2 = 0;
    OCR2A = ocr2a;
    TCCR2A |= (1<<WGM20) | (1<<COM2A0);
    TCCR2B |= (1<<WGM22); // top OCRA
    TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128
    ocr2a++;
    delay(1000);
  }
}


void timerCounter2(int divider) // Timer Counter 2
{    
  // Timer Counter 2 Control Register A
  TCCR2A |= (1<<WGM20); // выбор режима - fase correct PWMOCRA  
  TCCR2A |= (1<<COM2A0); // toggle
  TCCR2B |= (1<<WGM22); // top OCRA
  // Timer Counter 2 Control Register B
  if (divider == 0) TCCR2B |= (1<<CS20); // без делителя (0b001)
  else if (divider == 8) TCCR2B |= (1<<CS21); // делитель на 8 (0b010)
  else if (divider == 32) TCCR2B |= (1<<CS20) | (1<<CS21); // делитель на 32 (0b011)
  else if (divider == 64) TCCR2B |= (1<<CS22); // делитель на 64 (0b100)
  else if (divider == 128) TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128 (0b101)
  else if (divider == 256) TCCR2B |= (1<<CS21) | (1<<CS22); // делитель на 256 (0b110)
  else TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22); // делитель на 1024 (0b111)  
  // Output Compare Register A
	OCR2A = 240; // регистр сравнения         
  DDRB |= (1<<PB3); // пин OC2A на выход (11 пин ардуины)
}
