// ATmega8

//#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


// 8 бит в пакете, бит четности - нет, 1 стоп бит. битрейт 9600
void uart_ini(void){
    UBRRL=12; // 12 - для 9600 при 1MHz
    UCSRA|=(1<<U2X);// бит в 1
    UCSRB|=(1<<RXEN) | (1<<TXEN); // разрешить работу передатчика и приемника
}

// отправка строки в порт
void uart_send(char* str){
    uint8_t i=0;
    
    PORTB|=(1<<PB0);
    _delay_ms(100);    
    PORTB&=~(1<<PB0);    
    _delay_ms(100);  
    
    while (str[i])
    {    
        while ( !( UCSRA & (1<<UDRE)) ); // ждем пока не освободится регистр передатчика
        UDR = str[i];// пишем данные в регистр передатчика для отправки 
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
//      uart_send("\n\r");
      uart_send("LED OFF");
//      uart_send("\n\r");
      PORTB&=~(1<<PB0);
    }
    
    if (val==49)
    {
//      uart_send("\n\r");
      uart_send("LED ON");
//      uart_send("\n\r");
      PORTB|=(1<<PB0);
    }
  }
}

int main(void)
{
    DDRB|=(1<<PB0);// пин на выход
    uart_ini(); // инициализация УАРТ
  
//    uart_send("\n\r");
    uart_send("LED ON");
//    uart_send("\n\r");
    PORTB|=(1<<PB0);

    _delay_ms(100);
    
    PORTB&=~(1<<PB0);
//    uart_send("\n\r");
    uart_send("LED OFF");
//    uart_send("\n\r");
    
    _delay_ms(100);    

    while (1) 
    {
      uart_read_com();// ждем и выполняем команды
    }
}
