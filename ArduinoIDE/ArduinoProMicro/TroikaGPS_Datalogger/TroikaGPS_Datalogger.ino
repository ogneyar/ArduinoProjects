
// ProMicro
 

#include <SPI.h>
#include <SD.h>
#include <nRF24L01.h>  // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>      // Подключаем библиотеку для работы с nRF24L01+
#include <TroykaGPS.h> // библиотека для работы с GPS устройством

const int chipSelect = 4;

bool SDsuccessFlag = false;

// serial-порт к которому подключён GPS-модуль
#define GPS_SERIAL    Serial1
// создаём объект класса GPS и передаём в него объект Serial1 
GPS gps(GPS_SERIAL);
// задаём размер массива для времени, даты, широты и долготы
#define MAX_SIZE_MASS 16
// массив для хранения текущего времени
char strTime[MAX_SIZE_MASS];
// массив для хранения текущей даты
char strDate[MAX_SIZE_MASS];
// массив для хранения широты в градусах, минутах и секундах
char latitudeBase60[MAX_SIZE_MASS];
// массив для хранения долготы в градусах, минутах и секундах
char longitudeBase60[MAX_SIZE_MASS];


// для Nrf-Nano: CE (Chip Enable) - D10, CS/CSN (Chip Select) - D9
RF24 radio(10, 9); // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
char data[] = "Hello, bro!";       // Создаём массив для передачи данных



void setup()
{ 
  Serial.begin(9600);
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  // while (!Serial) ;
  delay(6000);

  Serial.print("Serial init OK\r\n");
  

  Serial.print("Initializing SD card...\r\n");

  // see if the card is present and can be initialized:
  if (!(SDsuccessFlag = SD.begin(chipSelect))) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    // while (1);
  }else {
    Serial.println("card initialized.");
  }

  // открываем Serial-соединение с GPS-модулем
  GPS_SERIAL.begin(9600);
  
  radio.begin();                                        // Инициируем работу nRF24L01+
  radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe (0x1234567890LL);               // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
}
 
void loop()
{
  // если пришли данные с GPS-модуля
  if (gps.available()) {

    Serial.println("GPS available");

    File dataFile;
    if (SDsuccessFlag) dataFile = SD.open("dataGPS.txt", FILE_WRITE);

    // считываем данные и парсим
    gps.readParsing();

    // проверяем состояние GPS-модуля
    switch(gps.getState()) {
      // всё OK
      case GPS_OK:
        Serial.println("GPS is OK");
        // выводим координаты широты и долготы
        // 1. в градусах, минутах и секундах
        // 2. градусах в виде десятичной дроби
        Serial.println("GPS Coordinates: ");
        gps.getLatitudeBase60(latitudeBase60, MAX_SIZE_MASS);
        gps.getLongitudeBase60(longitudeBase60, MAX_SIZE_MASS);
        Serial.print("Latitude\t");
        Serial.print(latitudeBase60);
        Serial.print("\t\t");
        Serial.println(gps.getLatitudeBase10(), 6);
        Serial.print("Longitude\t");
        Serial.print(longitudeBase60);
        Serial.print("\t\t");
        Serial.println(gps.getLongitudeBase10(), 6);
        // выводим количество видимых спутников
        Serial.print("Sat: ");
        Serial.println(gps.getSat());
        // выводим текущую скорость
        Serial.print("Speed: ");
        Serial.println(gps.getSpeedKm());
        // выводим высоту над уровнем моря
        Serial.print("Altitude: ");
        Serial.println(gps.getAltitude());
        // выводим текущее время
        Serial.print("Time: ");
        gps.getTime(strTime, MAX_SIZE_MASS);
        gps.getDate(strDate, MAX_SIZE_MASS);
        Serial.write(strTime);
        Serial.println();
        // выводим текущую дату
        Serial.print("Date: ");
        Serial.write(strDate);
        Serial.println("\r\n");
        // каждую переменную дату и времени можно выводить отдельно
  /*    Serial.print(gps.getHour());
        Serial.print(gps.getMinute());
        Serial.print(gps.getSecond());
        Serial.print(gps.getDay());
        Serial.print(gps.getMonth());
        Serial.print(gps.getYear());
  */   
  
        // if the file is available, write to it:
        if (dataFile && SDsuccessFlag) {
          dataFile.println("---------------------------------");
          dataFile.print("latitudeBase60: ");
          dataFile.println(latitudeBase60);
          dataFile.print("longitudeBase60: ");
          dataFile.println(longitudeBase60);
          dataFile.print("getLatitudeBase10: ");
          dataFile.println(String(gps.getLatitudeBase10(), 6));
          dataFile.print("getLongitudeBase10: ");
          dataFile.println(String(gps.getLongitudeBase10(), 6));
          dataFile.print("Sat: ");
          dataFile.println(gps.getSat());
          dataFile.print("Speed: ");
          dataFile.println(gps.getSpeedKm());
          dataFile.print("Altitude: ");
          dataFile.println(gps.getAltitude());
          dataFile.print("Time: ");
          dataFile.println(strTime);
          dataFile.print("Date: ");
          dataFile.println(strDate);
          dataFile.println("---------------------------------\r\n");
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          // Serial.println("error opening data_GPS.txt");
        }


        break;
      // ошибка данных
      case GPS_ERROR_DATA:
        Serial.println("GPS error data");
        

        // if the file is available, write to it:
        if (dataFile && SDsuccessFlag) {
          dataFile.println("GPS error data");
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          // Serial.println("error opening data_GPS.txt");
        }


        break;
      // нет соединение со спутниками
      case GPS_ERROR_SAT:
        Serial.println("GPS no connect to satellites!!!");

        

        // if the file is available, write to it:
        if (dataFile && SDsuccessFlag) {
          dataFile.println("GPS no connect to satellites!!!");
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          // Serial.println("error opening data_GPS.txt");
        }

      break;

      default:
        Serial.println("case default");
        delay(1000);
      break;
    } 

  }else {
    Serial.println("send data at nRF module");
    delay(1000);
    radio.write(&data, sizeof(data));
  }
}


