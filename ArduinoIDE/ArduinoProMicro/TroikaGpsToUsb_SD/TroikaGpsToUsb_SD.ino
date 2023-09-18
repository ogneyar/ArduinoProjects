
// Micro

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

bool SDsuccessFlag = false;

// serial-порт к которому подключён GPS-модуль
#define GPS_SERIAL    Serial1

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
  }
  Serial.print("\r\nSerial init OK\r\n");
  
  GPS_SERIAL.begin(9600);

  Serial.print("Initializing SD card...\r\n");
  
  if (!(SDsuccessFlag = SD.begin(chipSelect))) {
    Serial.println("Card failed, or not present");
    // while (1);
  }else {
    Serial.println("card initialized.");
  }
}

void loop()
{
  // если приходят данные из GPS-модуля - отправим их в порт компьютера
  if (GPS_SERIAL.available()) {
    char c = GPS_SERIAL.read();
    // if (c) {      
      if (SDsuccessFlag) {
        File dataFile = SD.open("test_GPS.txt", FILE_WRITE);      
        if (dataFile) {
          dataFile.print("char: ");
          dataFile.println(c);
          dataFile.close();
        }
      }
      Serial.write(c);
    // }
  }
  // если приходят данные из компьютера - отправим их в GPS-модуль
  if (Serial.available()) {
    GPS_SERIAL.write(Serial.read());
  }
}
