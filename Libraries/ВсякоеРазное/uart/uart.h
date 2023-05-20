
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define DELIMETER 8 // 16 // если U2X = 0 то делим на 16, иначе на 8
#define MYUBRR FOSC/DELIMETER/BAUD-1 

// 8 бит в пакете, бит четности - нет, 1 стоп бит. битрейт 9600
void uart_ini(void){
    UBRRH = (MYUBRR>>8);
    UBRRL = MYUBRR; // UBRRL = 12; // 12 (или 0x0c) - для 9600 при 1MHz и U2X = 1
    UCSRA |= (1<<U2X);// бит в 1 (двухскоростная работа)
    UCSRB |= (1<<RXEN) | (1<<TXEN); // разрешить работу передатчика и приемника
    // UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); // 8 бит данных в посылке (по умолчанию)
}

// отправка строки в порт
void uart_send(char* str){
    uint8_t i=0;        
    while (str[i])
    {    
        while ( !( UCSRA & (1<<UDRE)) ); // ждем пока не освободится регистр передатчика
        UDR = str[i];// пишем данные в регистр передатчика для отправки 
        i++;
    }
}