
// WEMOS_D1_mini

#include "Arduino.h"
#include "uRTCLib.h"

#include "buildTime.h" // из библиотеки AlexGyver'a microDS3231
#include <EEPROM.h>

int address = 0;   // адрес ключа
uint8_t key = 127; // ключ для проверки первого запуска

// uRTCLib rtc;
uRTCLib rtc(0x68);


void setup() 
{
  delay (2000);
	Serial.begin(9600);
	Serial.println("Serial OK");

	#ifdef ARDUINO_ARCH_ESP8266
		URTCLIB_WIRE.begin(4, 5); // D2 (SDA) and D1 (SCL) on ESP8266
	#else
		URTCLIB_WIRE.begin();
	#endif

  EEPROM.begin(512);
  if (EEPROM.read(address) != key) 
  { // значение ключа
    EEPROM.write(address, key);
    if (EEPROM.commit()) 
    {
      Serial.println("EEPROM successfully committed");
    } 
    else 
    {
      Serial.println("ERROR! EEPROM commit failed");
    }      
    // установить время == времени компиляции
    rtc.set(BUILD_SEC, BUILD_MIN, BUILD_HOUR, 1, BUILD_DAY, BUILD_MONTH, BUILD_YEAR-2000);
    //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
    // rtc.set(0, 42, 16, 6, 2, 5, 15);
  }
  
}

void loop() {
	rtc.refresh();

	Serial.print("RTC DateTime: ");
	Serial.print(rtc.year());
	Serial.print('/');
	Serial.print(rtc.month());
	Serial.print('/');
	Serial.print(rtc.day());

	Serial.print(' ');

	Serial.print(rtc.hour());
	Serial.print(':');
	Serial.print(rtc.minute());
	Serial.print(':');
	Serial.print(rtc.second());

	Serial.print(" DOW: ");
	Serial.print(rtc.dayOfWeek());

	Serial.print(" - Temp: ");
	Serial.print(rtc.temp()  / 100);

	Serial.println();

	delay(1000);
}
