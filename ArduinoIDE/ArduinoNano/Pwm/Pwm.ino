
// Nano

void timerCounter0(void);
void timerCounter2(int = 1024);


int main(void) {  
  timerCounter0();
  timerCounter2(128);
  
  while (1) {
    
  }
}

void timerCounter0(void) // Timer Counter 0 (не работает)
{
  //Timer Counter 0 Control Register A
  TCCR0A |= (1<<WGM01) | (1<<WGM00); // выбор режима - Fast PWM
  //TCCR0A |=(1<<WGM00); // выбор режима - fase correct PWM

  TCCR0A|=(1<<COM0B1);
  //TCCR0A|=(1<<COM0B1) | (1<<COM0B0);

    // Timer Counter 0 Control Register B
//    TCCR0B |= (1<<CS01); // делитель на 8
//    TCCR0B |= (1<<CS00) | (1<<CS01); // делитель на 32
//    TCCR0B |= (1<<CS02); // делитель на 64
//    TCCR0B |= (1<<CS00) | (1<<CS02); // делитель на 128
//    TCCR0B |= (1<<CS01) | (1<<CS02); // делитель на 256
    TCCR0B |= (1<<CS00) | (1<<CS01) | (1<<CS02); // делитель на 1024

  //Oscillator Calibration Register
  OSCCAL = 200; // регистр сравнения

  DDRB |= (1<<PD5);// пин OC0B на выход (5 пин ардуины))
}

void timerCounter2(int divider) // Timer Counter 2
{  
    // Timer Counter 2 Control Register A
  TCCR2A |= (1<<WGM21) | (1<<WGM20); // выбор режима - Fast PWM
  //TCCR2A |=(1<<WGM20); // выбор режима - fase correct PWM
  
  TCCR2A|=(1<<COM2A1); // сброс по совпадению 
  //TCCR2A|=(1<<COM2A1) | (1<<COM2A0); // установка по сопадению 
  
  // Timer Counter 2 Control Register B
  if (divider == 8) TCCR2B |= (1<<CS21); // делитель на 8
  else
  if (divider == 32) TCCR2B |= (1<<CS20) | (1<<CS21); // делитель на 32
  else
  if (divider == 64) TCCR2B |= (1<<CS22); // делитель на 64
  else
  if (divider == 128) TCCR2B |= (1<<CS20) | (1<<CS22); // делитель на 128
  else
  if (divider == 256) TCCR2B |= (1<<CS21) | (1<<CS22); // делитель на 256
  else 
    TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22); // делитель на 1024
  
    // Oscillator Calibration Register
//    OSCCAL = 10; // регистр сравнения (не пойму зачем)
         
    DDRB |= (1<<PB3);// пин OC2A на выход (11 пин ардуины)
}
