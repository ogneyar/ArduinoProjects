
// Nano, Nrf-Nano, LGT8F328P

#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+
// #include <Servo.h>                                        // Подключаем библиотеку  для работы с сервоприводами

// для Nrf-Nano: CE (Chip Enable) - D10, CS/CSN (Chip Select) - D9
RF24 radio(10, 9); // Создаём объект radio   для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
// Servo servo;    // Создаём объект myservo для работы с функциями библиотеки Servo
byte data[128];      // Создаём массив для приёма данных


void setup(){
    Serial.begin(9600);
    delay(1000);
    // servo.attach(4);                                      // Подключаем объект myservo к 4 выводу Arduino
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setChannel(5);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openReadingPipe (1, 0x1234567890LL);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу
//  radio.stopListening   ();                             // Выключаем приёмник, если потребуется передать данные
}

void loop(){
    if(radio.available()){                                // Если в буфере имеются принятые данные
        radio.read(&data, sizeof(data));                  // Читаем данные в массив data и указываем сколько байт читать
        // servo.write(map(data[1],0,1023,0,180));           // Поворачиваем сервопривод на угол заданный потенциометром
        // Serial.println(data[1]);
        // Serial.write(data[1]);
        for (byte i = 0; i < sizeof(data); i++) {
          if (data[i] == '\0') break;
          Serial.write(data[i]);
        }
        Serial.println();
    }
}
