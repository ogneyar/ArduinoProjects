// ATmega8

//#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1000000 // Clock Speed
#define BAUD 9600
#define DELIMETER 8 // 16 // если U2X = 0 то делим на 16, иначе на 8
#define MYUBRR FOSC/DELIMETER/BAUD-1 

// 8 бит в пакете, бит четности - нет, 1 стоп бит. битрейт 9600
void uart_ini(void){
    UBRRH = (MYUBRR>>8);
    UBRRL = MYUBRR; // UBRRL = 12; // 12 (или 0x0c) - для 9600 при 1MHz и U2X = 1
    UCSRA|=(1<<U2X);// бит в 1 (двухскоростная работа)
    UCSRB|=(1<<RXEN) | (1<<TXEN); // разрешить работу передатчика и приемника
}

// отправка строки в порт
void uart_send(char* str){
    uint8_t i=0;
    
//    PORTB|=(1<<PB0);
//    _delay_ms(100);    
//    PORTB&=~(1<<PB0);    
//    _delay_ms(100);  
        
    while (str[i])
    {    
        while ( !( UCSRA & (1<<UDRE)) ); // ждем пока не освободится регистр передатчика
        UDR = str[i];// пишем данные в регистр передатчика для отправки 
        
        PORTB|=(1<<PB0);
        _delay_ms(100);    
        PORTB&=~(1<<PB0);    
        _delay_ms(100);  
        
        i++;
    }
}

// чтение и выполнение команд из порта
void uart_read_com(void){
  uint8_t val;
  if (UCSRA&(1<<RXC))
  {
    val=UDR;
    if (val==48)
    {
      uart_send("\nLED OFF\n");
      PORTB&=~(1<<PB0);
    }
    
    if (val==49)
    {
      uart_send("\nLED ON\n");
      PORTB|=(1<<PB0);
    }
  }
}

int main(void)
{
    DDRB|=(1<<PB0);// пин на выход
    uart_ini(); // инициализация УАРТ
  
    PORTB|=(1<<PB0);
    _delay_ms(100);    
    PORTB&=~(1<<PB0);    
    _delay_ms(100);    

    while (1) 
    {
      uart_read_com();// ждем и выполняем команды
    }
}
