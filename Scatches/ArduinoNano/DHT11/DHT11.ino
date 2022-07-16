// Arduino Nano

//#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

#define DHT_DDR		DDRB
#define DHT_PIN		PINB
#define DHT_PORT	PORTB
#define DHT			  7

uint8_t _hum, _temp;// переменные для влажности и температуры

// функция передачи условия "старт" на линию и проверка ответов от датчика.
uint8_t dht_start(void){
//	DHT_DDR|=(1<<DHT);// DDR на выход, а линию притянули к земле - 0
pinMode(DHT, HIGH);
digitalWrite(DHT, LOW);
	_delay_ms(20);// пауза 20 мс 
//	DHT_DDR&=~(1<<DHT);// DDR на вход, отпустили линию - 1 // подтягивающий резистор притянул питание
pinMode(DHT, LOW);
	_delay_us(40);// ждем 40 мкс чтобы попасть в середину низкого сигнала
//	if (DHT_PIN&(1<<DHT)) return 1; // если на линии 1 ошибка - "датчик не ответил"
if (digitalRead(DHT)) return 1;
	_delay_us(110); // ждем 80 мкс чтобы попасть в середину высокого сигнала
//	if (!(DHT_PIN&(1<<DHT))) return 2; // если на линии 0 ошибка - "датчик не готов "
if ( ! digitalRead(DHT)) return 2;
//	while(DHT_PIN&(1<<DHT));// ждем пока датчик не притянет линию к земле.
while(digitalRead(DHT));
	return 0;// ошибок нет
}

// получение байта от датчика
uint8_t dht_byte(void){
	uint8_t i=8, byte=0;// переменная для цикла и под байт
	while(i--){
		while(!(DHT_PIN&(1<<DHT)));// ждем пока линия не поднимится в 1
		_delay_us(40);// отступаем 40 мкс
		if (DHT_PIN&(1<<DHT)) {// если на линии 1 = приняли 1
			byte|=(1<<i);// поднимаем итый бит в 1
			while(DHT_PIN&(1<<DHT));// ждем пока линия упадет в 0
		}
	}
	return byte;// возвращаем полученный байт
}

// общая функция опроса датчика
uint8_t dht_read(uint8_t *hum, uint8_t* temp) {
	uint8_t data[5];// массив под данные датчика
	uint8_t error=dht_start();// стартуем и получаем код ошибки в переменную

	if (error) return error; // если есть ошибки выходим с кодом ошибки
	
	// получаем 5 байт от датчика
	for (uint8_t i=0; i<5; i++)
	{
		data[i]=dht_byte();
	}
	
	if (data[0]+data[1]+data[2]+data[3]!=data[4]) return 3; // если контрольная сумма не сошлась вернем ошибку 3
	
	*hum=data[0];// пишем данные влажности 
	*temp=data[2];// пишем данные температуры 
	return 0;// вернем 0 - ошибок нет.
}

int main(void)
{
    Serial.begin(9600);
    
	  uint8_t response = dht_read(&_hum, &_temp);// опроса датчика

    Serial.println(response);
    
//    DDRD |= (1<<PD5);
 
    while (1) 
    {
//        Serial.print("hum: ");
//        Serial.println(_hum);
//        Serial.print("temp: ");
//        Serial.println(_temp);
//        _delay_us(3000000);

//      PORTD |= (1<<PD5);      
//      _delay_us(500000);      
//      PORTD &= ~(1<<PD5);
//      _delay_ms(500);
    }
}
