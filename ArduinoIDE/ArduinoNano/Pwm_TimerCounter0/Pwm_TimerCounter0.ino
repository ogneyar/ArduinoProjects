
// Nano

// шим на PD5 (5 пин ардуины)

void timerCounter0(int = 1024, uint8_t = 240);

uint8_t ocr0b = 10; // длительность импульса


int main(void) {  
  timerCounter0(32, ocr0b);
  
  while (1) {}
}

void timerCounter0(int divider, uint8_t ocr) // Timer Counter 0
{
  TCCR0A |= (1<<WGM01) | (1<<WGM00); // выбор режима - Fast PWM
  TCCR0A|=(1<<COM0B1); // сброс по совпадению 
  if (divider == 0) TCCR0B |= (1<<CS00); // без делителя (0b001)
  else if (divider == 8) TCCR0B |= (1<<CS01); // делитель на 8 (0b010)
  else if (divider == 32) TCCR0B |= (1<<CS00) | (1<<CS01); // делитель на 32 (0b011)
  else if (divider == 64) TCCR0B |= (1<<CS02); // делитель на 64 (0b100)
  else if (divider == 128) TCCR0B |= (1<<CS00) | (1<<CS02); // делитель на 128 (0b101)
  else if (divider == 256) TCCR0B |= (1<<CS01) | (1<<CS02); // делитель на 256 (0b110)
  else TCCR0B |= (1<<CS20) | (1<<CS01) | (1<<CS02); // делитель на 1024 (0b111)
  OCR0B = ocr; // регистр сравнения
  DDRD |= (1<<PD5); // пин OC0B на выход (5 пин ардуины))
}