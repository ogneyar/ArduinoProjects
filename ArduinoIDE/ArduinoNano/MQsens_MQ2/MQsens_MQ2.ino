
// Nano

#include <MQ2.h>  // библиотека для датчика

#define PIN_MQ2   A0   // пин для подключения MQ2
#define LED       13   // пин для подключения светодиода
MQ2 mq2(PIN_MQ2);   // создаём объект для работы с датчиком

int lpg, co, smoke;

void setup() {
  Serial.begin(9600);
  mq2.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
   float* values = mq2.read(true);

   // получаем информацию с датчика
   // выводим данные на монитор порта
   lpg = mq2.readLPG();
   co = mq2.readCO();
   smoke = mq2.readSmoke();
  
   // включаем светодиод при превышении концентрации CO
   if (co > 1000) { digitalWrite(LED, HIGH); }
   else { digitalWrite(LED, LOW); }

   delay(200);
}

//