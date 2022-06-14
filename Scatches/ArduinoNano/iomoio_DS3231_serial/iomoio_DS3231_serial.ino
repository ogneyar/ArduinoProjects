// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

/*
  DS3231: Real-Time Clock.
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-DS3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>             // Подключаем бибилиотеку для работы с I2C устройствами
#include <DS3231.h>           // Подключаем библиотеку для работы с RTC DS3231

DS3231 clock;                 // Связываем объект clock с библиотекой DS3231
RTCDateTime DateTime;         // Определяем сущность структуры RTCDateTime (описанной в библиотеке DS3231) для хранения считанных с часов даты и времени
RTCAlarmTime Alarm1;          // Определяем сущность структуры RTCAlarmTime (описанной в библиотеке DS3231) для хранения считанных с первого будильника настроек даты и времени

boolean isAlarm = false;      // Логическая переменная для обработки сигнала о срабатывании будильника 
boolean alarmState = false;   // Логическая переменная для обработки индикации при срабатывании будильника
int alarmLED = 4;             // Пин, к которому подключаем индикатор срабатывания будильника (светодиод)

void alarmFunction()                                  // Функция, вызываемая при срабатывании будильника
{
  isAlarm = true;                                     // Присваиваем значение "истина" переменной для обработки срабатывания будильника
}

void setup()
{
  Serial.begin(9600);               // Инициализируем вывод данных на монитор серийного порта, со скоростью 9600 бод
  clock.begin();                    // Инициализируем работу с объектом библиотеки DS3231
  clock.enableOutput(false);        // Определяем назначение вывода SQW (INT) для генерации прерываний при сработке будильников

  clock.setDateTime(__DATE__, __TIME__);                  // Устанавливаем время на часах, основываясь на времени компиляции скетча
//  clock.setDateTime(2016, 9, 15, 0, 0, 0);              // Установка времени вручную (Год, Месяц, День, Час, Минута, Секунда)
//  setAlarm1(Дата или день, Час, Минута, Секунда, Режим)
  clock.setAlarm1(0, 0, 0, 10, DS3231_MATCH_S);           // Устанавливаем первый будильник на срабатывание в 10 сек. каждой минуты. Режим DS3231_MATCH_S сообщает о том, что ориентироваться надо на секунды.
  pinMode(alarmLED, OUTPUT);                              // Определяем пин подключения питания светодиода, как исходящий
  attachInterrupt(0, alarmFunction, FALLING);             // Задаем функцию для обработки прерывания 0 (на пине 2)
}

void loop()
{
  DateTime = clock.getDateTime();                                                 // Считываем c часов текущие значения даты и времени в сущность DateTime
  Alarm1 = clock.getAlarm1();                                                     // Считываем c первого будильника текущие настройки даты и времени в сущность Alarm1
  Serial.println(clock.dateFormat("d.m.Y H:i:s - l   ", DateTime));               // Определяем формат вывода даты и выводим на монитор серийного порта
  Serial.println("Temperature: " + String(clock.readTemperature()));              // Выводим значения температуры
  Serial.println("Alarm: " + String(clock.dateFormat("__ __:__:s", Alarm1)));     // Выводим настройки будильника                                
  Serial.println();                                                               // Перевод строки
  if (isAlarm)                                                                    // Если поступил сигнал о сработке будильника
  {
    digitalWrite(alarmLED, alarmState);                                           // Отправляем логическое значение выводу питания светодиода при каждом срабатывании будильника
    alarmState = !alarmState;                                                     // Меняем это значение на противоположное
    isAlarm = false;                                                              // Отключаем сигнал о сработке будильника (меняем состояние события обработки индикатора на "ложь")
    clock.clearAlarm1();                                                          // Очищаем состояние сработки будильника
  } 
  delay(1000);                                                                    // Задержка в 1 секунду
}

/*
Date formats (Day)
------------------

 * d : Day of the month, 2 digits with leading zeros (01 to 31)
 * D : A textual representation of a day, three letters (Mon through Sun)
 * j : Day of the month without leading zeros (1 to 31)
 * l : A full textual representation of the day of the week (Sunday through Saturday)
 * N : ISO-8601 numeric representation of the day of the week (1 for Monday through 7 for Sunday)
 * S : English ordinal suffix for the day of the month, 2 characters (st, nd, rd or th. Works well with j)
 * w : Numeric representation of the day of the week (0 for Sunday through 6 for Saturday)
 * z : The day of the year (0 through 365)

Date formats (Month)
--------------------

 * F : A full textual representation of a month, such as January or March (January through December)
 * m : Numeric representation of a month, with leading zeros (01 through 12)
 * M : A short textual representation of a month, three letters (Jan through Dec)
 * n : Numeric representation of a month, without leading zeros (1 through 12)
 * t : Number of days in the given month (28 through 31)

Date formats (Year)
-------------------

 * L : Whether it's a leap year (1 if it is a leap year, 0 otherwise)
 * Y : A full numeric representation of a year, 4 digits (Examples: 1999 or 2003)
 * y : A two digit representation of a year (Examples: 99 or 03)

Date formats (Time)
-------------------

 * a : Lowercase Ante meridiem and Post meridiem (am or pm)
 * A : Uppercase Ante meridiem and Post meridiem (AM or PM)
 * g : 2-hour format of an hour without leading zeros (1 through 12)
 * G : 24-hour format of an hour without leading zeros (0 through 23)
 * h : 12-hour format of an hour with leading zeros (01 through 12)
 * H : 24-hour format of an hour with leading zeros (00 through 23)
 * i : Minutes with leading zeros (00 to 59)
 * s : Seconds, with leading zeros (00 through 59)

Dare formats (Full Date/Time)
-----------------------------

 * U : Seconds since the Unix Epoch (January 1 1970 00:00:00 GMT)



Alarm modes:
-----------------------------
  Set Alarm - Every second.
  DS3231_EVERY_SECOND is available only on Alarm1.
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 0, 0, DS3231_EVERY_SECOND);

  Set Alarm - Every full minute.
  DS3231_EVERY_MINUTE is available only on Alarm2.
  setAlarm2(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm2(0, 0, 0, 0, DS3231_EVERY_MINUTE);
  
  Set Alarm1 - Every 20s in each minute
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 0, 20, DS3231_MATCH_S);

  Set Alarm2 - Every 01m in each hour
  setAlarm2(Date or Day, Hour, Minute, Mode, Armed = true)
  clock.setAlarm2(0, 0, 1,     DS3231_MATCH_M);

  Set Alarm - Every 01m:25s in each hour
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 1, 25, DS3231_MATCH_M_S);

  Set Alarm - Every 01h:10m:30s in each day
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 1, 10, 30, DS3231_MATCH_H_M_S);

  Set Alarm - 07h:00m:00s in 25th day in month
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(25, 7, 0, 0, DS3231_MATCH_DT_H_M_S);

  Set Alarm - 10h:45m:30s in every Friday (1 - Mon, 7 - Sun)
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(5, 10, 40, 30, DS3231_MATCH_DY_H_M_S);
 */

