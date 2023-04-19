
// Nano

#include <EEPROM.h>
#include "buildTime.h"
#include "Wire.h"
#define PCF8563address 0x51 // Адрес устройства по умолчанию 

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

int address = 0;  // адрес ключа
byte key = 138;         // ключ для проверки первого запуска

// функция перевода из двоично - десятичной системы в десятичную.
byte bcdToDec(byte value)
{
  return ((value / 16) * 10 + value % 16);
}
// И обратно
byte decToBcd(byte value){
  return (value / 10 * 16 + value % 10);
}

// функция установки времени и даты в PCF8563
void setPCF8563()
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.write(decToBcd(second)); 
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));   
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(dayOfWeek)); 
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

// функция считывания времени и даты из PCF8563
void readPCF8563()
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(PCF8563address, 7);
  second   = bcdToDec(Wire.read() & B01111111); // удаление ненужных бит из данных 
  minute   = bcdToDec(Wire.read() & B01111111); 
  hour    = bcdToDec(Wire.read() & B00111111); 
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek = bcdToDec(Wire.read() & B00000111); 
  month   = bcdToDec(Wire.read() & B00011111); 
  year    = bcdToDec(Wire.read());
}
void setup()
{
  Wire.begin();
  Serial.begin(9600);

  if (EEPROM.read(address) != key) { // значение ключа
    EEPROM.write(address, key);      
    // Выставляем время и дату 
    second = BUILD_SEC;
    minute = BUILD_MIN;
    hour = BUILD_HOUR;
    dayOfWeek = 3;
    dayOfMonth = BUILD_DAY;
    month = BUILD_MONTH;
    year = BUILD_YEAR;
    setPCF8563();
  }
}
void loop()
{
  readPCF8563();
  Serial.print(days[dayOfWeek]); 
  Serial.print(" "); 
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/20");
  Serial.print(year, DEC);
  Serial.print(" - ");
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":"); 
  if (second < 10)
  {
    Serial.print("0");
  } 
  Serial.println(second, DEC); 
  delay(1000);
}