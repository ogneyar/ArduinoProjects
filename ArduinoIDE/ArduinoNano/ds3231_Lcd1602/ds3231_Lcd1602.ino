
// Arduino NANO

//#define DEBUG_ON 1

#include <microDS3231.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

MicroDS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int address = 0;  // адрес ключа
byte key;         // ключ для проверки первого запуска
char date[11]; // буфер минимум на 11 символов (10 данные + 1 нулевой)

// setup function
void setup() {
#ifdef DEBUG_ON
  Serial.begin(9600);
#endif    
  // проверка наличия модуля на линии i2c
  // вызов rtc.begin() не обязателен для работы
  if (!rtc.begin()) {
#ifdef DEBUG_ON
    Serial.println("DS3231 not found");
#endif
    for(;;);
  } 
  lcd.init(); // инициализируем дисплей 
  lcd.backlight(); // Включаем подсветку дисплея
//  lcd.setCursor(0, 0); // переходим на позицию - первый ноль это позиция символа, второй ноль это позиция строки
//  lcd.print("Time is"); // выводим надпись  
  
  key = EEPROM.read(address);
  if (key != 251) { // значение ключа
      EEPROM.write(address, 251);
      // установить время == времени компиляции
//      rtc.setTime(COMPILE_TIME); // так
      rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR); // или так    
  }
  
  if (rtc.lostPower()) { // выполнится при сбросе батарейки
#ifdef DEBUG_ON
    Serial.println("lost power!");
#endif
    rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  }
}

// loop function
void loop() {
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeString());
  lcd.setCursor(11, 0);
  lcd.print("temp");
  
  lcd.setCursor(0, 1);
  rtc.getDateChar(date);
  for(byte i = 0; i < 10; i++) 
    if ((i != 6) && (i != 7)) lcd.print(date[i]);
  lcd.setCursor(11, 1);
  lcd.print((String)rtc.getTemperatureFloat());
  
#ifdef DEBUG_ON
  Serial.print(rtc.getTimeString() + " ");
  Serial.println(rtc.getDateString());
  Serial.println("t = " + (String)rtc.getTemperatureFloat());   
  Serial.println();
#endif

  delay(1000);
  
}
