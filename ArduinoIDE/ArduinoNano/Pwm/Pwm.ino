
// Nano

void timerCounter0(int = 1024);
void timerCounter2(int = 1024);


int main(void) {  
  timerCounter0(32);
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
    //TCCR2B ^= (1<<CS21);
//    if (ocr2a == 10) ocr2a = 240;
//    else ocr2a = 10;
    ocr2a++;
    delay(1000);
    if (ocr2a > 255 || ocr2a <= 0) ocr2a = 1;
    
    //period *= clockCyclesPerMicrosecond();
  }
}

void timerCounter0(int divider) // Timer Counter 0
{
  //Timer Counter 0 Control Register A
  //TCCR0A |= (1<<WGM01); // выбор режима - CTC on OCRA
  TCCR0A |= (1<<WGM01) | (1<<WGM00); // выбор режима - Fast PWM
  //TCCR0A |=(1<<WGM00); // выбор режима - fase correct PWM

  //TCCR0A|=(1<<COM0B0); // toggle
  TCCR0A|=(1<<COM0B1); // сброс по совпадению 
  //TCCR0A|=(1<<COM0B1) | (1<<COM0B0);  // установка по сопадению 

  // Timer Counter 0 Control Register B  
  if (divider == 0) TCCR0B |= (1<<CS00); // без делителя (0b001)
  else
  if (divider == 8) TCCR0B |= (1<<CS01); // делитель на 8 (0b010)
  else
  if (divider == 32) TCCR0B |= (1<<CS00) | (1<<CS01); // делитель на 32 (0b011)
  else
  if (divider == 64) TCCR0B |= (1<<CS02); // делитель на 64 (0b100)
  else
  if (divider == 128) TCCR0B |= (1<<CS00) | (1<<CS02); // делитель на 128 (0b101)
  else
  if (divider == 256) TCCR0B |= (1<<CS01) | (1<<CS02); // делитель на 256 (0b110)
  else 
    TCCR0B |= (1<<CS20) | (1<<CS01) | (1<<CS02); // делитель на 1024 (0b111)

  // Output Compare Register B
  OCR0B = 240; // регистр сравнения

  DDRD |= (1<<PD5); // пин OC0B на выход (5 пин ардуины))
}

void timerCounter2(int divider) // Timer Counter 2
{  
//  TIMSK2 |= OCIE2A; // разрешить прерывания для регистра А
  
  // Timer Counter 2 Control Register A
  //TCCR2A |= (1<<WGM21); // выбор режима - CTC
  //TCCR2A |= (1<<WGM21) | (1<<WGM20); // выбор режима - Fast PWM
  TCCR2A |= (1<<WGM20); // выбор режима - fase correct PWMOCRA
  
  TCCR2A |= (1<<COM2A0); // toggle
  //TCCR2A |= (1<<COM2A1); // сброс по совпадению 
  //TCCR2A |= (1<<COM2A1) | (1<<COM2A0); // установка по сопадению 

  TCCR2B |= (1<<WGM22); // top OCRA
    
  // Timer Counter 2 Control Register B
  if (divider == 0) TCCR2B |= (1<<CS20); // без делителя (0b001)
  else
  if (divider == 8) TCCR2B |= (1<<CS21); // делитель на 8 (0b010)
  else
  if (divider == 32) TCCR2B |= (1<<CS20) | (1<<CS21); // делитель на 32 (0b011)
  else
  if (divider == 64) TCCR2B |= (1<<CS22); // делитель на 64 (0b100)
  else
  if (divider == 128) TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128 (0b101)
  else
  if (divider == 256) TCCR2B |= (1<<CS21) | (1<<CS22); // делитель на 256 (0b110)
  else 
    TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22); // делитель на 1024 (0b111)
  
  // Output Compare Register A
	OCR2A = 240; // регистр сравнения
         
  DDRB |= (1<<PB3); // пин OC2A на выход (11 пин ардуины)
}
