// Arduino Nano

#include "iarduino_DHT.h"

iarduino_DHT sensor(3);     // объявляем  переменную для работы с датчиком DHT, указывая номер цифрового вывода к которому подключён датчик (сейчас 2pin)

void setup(){
  Serial.begin(9600);       // открываем последовательный порт на скорости 9600 бод
  delay(1000);              // выполняем задержку для перехода датчика в активное состояние
}

void loop(){
  switch(sensor.read()){    // читаем показания датчика
    case DHT_OK:               Serial.println((String) "CEHCOP B KOMHATE: " + sensor.hum + "% - " + sensor.tem + "*C");  break;
    case DHT_ERROR_CHECKSUM:   Serial.println(         "CEHCOP B KOMHATE: HE PABEHCTBO KC");                     break;
    case DHT_ERROR_DATA:       Serial.println(         "CEHCOP B KOMHATE: OTBET HE COOTBETCTB. CEHCOPAM 'DHT'"); break;
    case DHT_ERROR_NO_REPLY:   Serial.println(         "CEHCOP B KOMHATE: HET OTBETA");                          break;
    default:                   Serial.println(         "CEHCOP B KOMHATE: ERROR");                               break;
  }

  delay(2000);
}
