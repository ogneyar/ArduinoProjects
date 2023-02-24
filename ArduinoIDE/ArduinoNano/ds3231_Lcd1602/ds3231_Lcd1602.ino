
// Arduino NANO, LGT8F328

//#define DEBUG_ON 1

#define USE_LGT_EEPROM_API

#include <microDS3231.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

MicroDS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// шим на PD5 (5 пин ардуины)
void timerCounter0(int = 1024, uint8_t = 240);
uint8_t ocr0b = 5; // длительность импульса (яркость экрана)

int address = 0;  // адрес ключа
byte key;         // ключ для проверки первого запуска
char date[11]; // буфер минимум на 11 символов (10 данные + 1 нулевой)

uint32_t timeMillis = 0;
uint32_t current = 0;
uint16_t target = 1000;
  
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
  lcd.backlight(); // Включаем подсветку дисплея (GND на Катод)

  timerCounter0(32, ocr0b); // шим на PD5 (5 пин ардуины к Аноду)
  
  key = EEPROM.read(address);
  if (key != 237) { // значение ключа
      EEPROM.write(address, 237);
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
  timeMillis = millis();
  if (timeMillis - current > target) {
    current = timeMillis;
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
  }
}


void timerCounter0(int divider, uint8_t ocr) // Timer Counter 0
{
  TCCR0A |= (1<<WGM01) | (1<<WGM00); // выбор режима - Fast PWM
  TCCR0A|=(1<<COM0B1); // сброс по совпадению 
  if (divider == 0) TCCR0B |= (1<<CS00); // без делителя (0b001)
  else if (divider == 8) TCCR0B |= (1<<CS01); // делитель на 8 (0b010)
  else if (divider == 32) TCCR0B |= (1<<CS00) | (1<<CS01); // делитель на 32 (0b011)
  else if (divider == 64) TCCR0B |= (1<<CS02); // делитель на 64 (0b100)
  else if (divider == 128) TCCR0B |= (1<<CS00) | (1<<CS02); // делитель на 128 (0b101)
  else if (divider == 256) TCCR0B |= (1<<CS01) | (1<<CS02); // делитель на 256 (0b110)
  else TCCR0B |= (1<<CS20) | (1<<CS01) | (1<<CS02); // делитель на 1024 (0b111)
  OCR0B = ocr; // регистр сравнения
  DDRD |= (1<<PD5); // пин OC0B на выход (5 пин ардуины))
}
