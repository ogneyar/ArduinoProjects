
// ProMicro
 

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;


// библиотека для работы с GPS устройством
#include <TroykaGPS.h>
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



void setup()
{ 
  // открываем последовательный порт для мониторинга действий в программе
  // и передаём скорость 115200 бод
  Serial.begin(115200);
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  while (!Serial) {
  }
  Serial.print("Serial init OK\r\n");
  

  Serial.print("Initializing SD card...\r\n");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  // открываем Serial-соединение с GPS-модулем
  GPS_SERIAL.begin(115200);
}
 
void loop()
{
  // если пришли данные с GPS-модуля
  if (gps.available()) {

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("data_GPS.txt", FILE_WRITE);

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
        if (dataFile) {
          dataFile.print("latitudeBase60: ");
          dataFile.println(latitudeBase60);
          dataFile.print("longitudeBase60: ");
          dataFile.println(longitudeBase60);
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data_GPS.txt");
        }


        break;
      // ошибка данных
      case GPS_ERROR_DATA:
        Serial.println("GPS error data");
        

        // if the file is available, write to it:
        if (dataFile) {
          dataFile.print("GPS error data");
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data_GPS.txt");
        }


        break;
      // нет соединение со спутниками
      case GPS_ERROR_SAT:
        Serial.println("GPS no connect to satellites!!!");

        

        // if the file is available, write to it:
        if (dataFile) {
          dataFile.print("GPS no connect to satellites!!!");
          dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data_GPS.txt");
        }



        break;
    }


    // while(true);
    

  }
}














