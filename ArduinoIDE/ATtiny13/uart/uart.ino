
// AtTiny13 
// UART 1200 битрейт (Serial.begin(1200);)

#define F_CPU 9600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t temp, count, start;
volatile uint8_t c;

#define BAUD_C 123
#define TxD PB4

#define T_START TCCR0B = (1 << CS01) // F_CPU/8
#define T_STOP TCCR0B = 0
#define T_RESET TCNT0 = 0

ISR(TIM0_COMPA_vect){
  OCR0A = BAUD_C;
  c = 1;
  T_RESET;
}

void send(uint8_t data) {
  if (count >= 8) {
    PORTB |= (1<<TxD);
    start = 0; temp = 0; c = 0; count = 0;
    T_STOP;
    OCR0A = 0;
    return;
  }
  if(c == 1) {
    if (start == 0) {
      temp = 0x80;
      start = 1;
      count--;
    }
    else {
      temp = data;
      temp = temp >> count;
      temp = temp << 7;
    }
    switch(temp) {
      case 0x80 : PORTB &= ~(1 << TxD); break;
      case 0 : PORTB |= (1 << TxD); break;
    }
    count++;
    c = 0;
  }
}

void send_ch(uint8_t data){
  uint8_t f;
  data = ~data;
  T_START;
  for(f = 0; f < 10; f++){
    while(c == 0);
    send(data);
  }
}

void send_str(char *text){
  while(*text) {
    send_ch(*text++);
  }
}

 void itoa(uint16_t n, char s[]) {
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
 
  void send_num(char *text, uint16_t n){
  char s[6];
  itoa((uint16_t)n, s);
  send_str(text);
  send_str(s);
 }

int main(void){
  DDRB |= (1 << TxD);
  TIMSK0 = (1 << OCIE0A);
  sei();
  
  while(1){
    _delay_ms(1);
    send_num("Habr:", 4242);
  }
}
 
