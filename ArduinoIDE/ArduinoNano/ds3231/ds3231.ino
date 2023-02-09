
// NANO, LGT8F328

#include <microDS3231.h>
MicroDS3231 rtc;
#include <EEPROM.h>

int address = 0;  // адрес ключа
byte key = 138;         // ключ для проверки первого запуска


void setup() {
  Serial.begin(9600);
    
  // проверка наличия модуля на линии i2c
  // вызов rtc.begin() не обязателен для работы
  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for(;;);
  }
  
  if (EEPROM.read(address) != key) { // значение ключа
      EEPROM.write(address, key);
      // установить время == времени компиляции
      // rtc.setTime(COMPILE_TIME); // так
      rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR); // или так
  }
  
  if (rtc.lostPower()) {            // выполнится при сбросе батарейки
    Serial.println("lost power!");
    rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  }
  
  // ======== УСТАНОВКА ВРЕМЕНИ ВРУЧНУЮ ========    
  // установить время вручную можно двумя способами (подставить реальные числа)
  //rtc.setTime(SEC, MIN, HOUR, DAY, MONTH, YEAR);
  //rtc.setHMSDMY(HOUR, MIN, SEC, DAY, MONTH, YEAR);
  
  // также можно установить время через DateTime
  /*
  DateTime now;
  now.second = 0;
  now.minute = 10;
  now.hour = 50;
  now.date = 2;
  now.month = 9;
  now.year = 2021;
  
  rtc.setTime(now);  // загружаем в RTC
  */

}

void loop() {
  // получение и вывод каждой компоненты
  Serial.print((String)rtc.getHours() + ":");
  Serial.print((String)rtc.getMinutes() + ":");
  Serial.print((String)rtc.getSeconds() + " ");
  Serial.print((String)rtc.getDay() + " ");
  Serial.print((String)rtc.getDate() + "/");
  Serial.print((String)rtc.getMonth() + "/");
  Serial.println(rtc.getYear());
  
  /*
  // можно через DateTime (более оптимально):
  DateTime now = rtc.getTime();
  Serial.print(now.hour);
  Serial.print(":");
  Serial.print(now.minute);
  Serial.print(":");
  Serial.print(now.second);
  Serial.print(" ");
  Serial.print(now.day);
  Serial.print(" ");
  Serial.print(now.date);
  Serial.print("/");
  Serial.print(now.month);
  Serial.print("/");
  Serial.println(now.year);
  */
  
  // вывод температуры чипа
  Serial.println("t = " + (String)rtc.getTemperatureFloat());  
  // Serial.println(rtc.getTemperature());
  
  // вывод времени готовой строкой String
  // Serial.println(rtc.getTimeString());
  
  // вывод даты готовой строкой String
  // Serial.println(rtc.getDateString());

  // вывод времени через char array
  char time[9]; // буфер минимум на 9 символов (8 данные + 1 нулевой)
  rtc.getTimeChar(time);
  // Serial.println(time);
  
  // вывод даты через char array
  char date[11]; // буфер минимум на 11 символов (10 данные + 1 нулевой)
  rtc.getDateChar(date);
  // Serial.println(date);
  
  Serial.println();
  delay(1000);
  
}
