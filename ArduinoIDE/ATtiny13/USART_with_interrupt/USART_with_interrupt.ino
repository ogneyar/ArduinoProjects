
// AtTiny13 
// UART 9600 битрейт (Serial.begin(9600);)

#define F_CPU 9600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t temp = 0, count = 0, start = 0;
volatile uint8_t flag;

// F_CPU/DIVIDER/BAUD-1 == 9600000 / 8 / 9600 - 1 = 124
#define BAUD_C 123 // 9600 при F_CPU = 9,6MHz
#define TxD PB4

ISR(TIM0_COMPA_vect){
  flag = 1;
  TCNT0 = 0;
}


int main(void)
{
  DDRB |= (1 << TxD); // пин передатчика на выход
  TIMSK0 = (1 << OCIE0A); // разрешаем прерывания по совпадению
  OCR0A = BAUD_C; // заполняем регистр сравнения
  sei();
  
  while(1){
    _delay_ms(1000);
    send_num("Example: ", 4231);
    send_str("\n");
  }
}
 

void send(uint8_t data) {
  if (count >= 8) {
    PORTB |= (1<<TxD); // команда СТОП
    start = 0; 
    temp = 0; 
    flag = 0; 
    count = 0;
    TCCR0B = 0;
    return;
  }
  if(flag == 1) {
    if (start == 0) { // команда СТАРТ
      start = 1;
      count--;
    }
    else {
      temp = data;
      temp = temp >> count;
      temp = temp & 0x01; // маска оставит только первый бит
    }
    switch(temp) {
      case 1: 
        PORTB |= (1 << TxD); break;
      case 0: 
        PORTB &= ~(1 << TxD); break;
    }
    count++;
    flag = 0;
  }
}

void send_ch(uint8_t data)
{
  TCCR0B = (1 << CS01); // F_CPU/8 - T_START
  for(uint8_t f = 0; f < 10; f++){
    while(flag == 0) 
      ;
    send(data);
  }
}

void send_str(char *text)
{
  while(*text) {
    send_ch(*text++);
  }
}

 void itoa(uint16_t n, char s[]) 
 {
   uint8_t i = 0;
   do { s[i++] = n % 10 + '0'; } 
   while ((n /= 10) > 0);
   s[i] = '\0';
   // Reversing
   uint8_t j;
   char c;
   for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
     c = s[i];
     s[i] = s[j];
     s[j] = c;
   }
 }
 
  void send_num(char *text, uint16_t n)
  {
  char s[6];
  itoa((uint16_t)n, s);
  send_str(text);
  send_str(s);
 }
 