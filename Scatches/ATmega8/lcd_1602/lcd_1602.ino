#include <Wire.h>                  // подключаем библиотеку I2C
#include <LiquidCrystal_I2C.h>     // подключаем библиотеку дисплея 

LiquidCrystal_I2C lcd(0x27, 16, 2); // Устанавливаем какой дисплей

bool flag;
int i, j, k, m, r, s; 
char * pict, * fi_string; 
const char first_string[17] = "-=Hell o World=-";
word last_time;

void setup()
{
  pinMode(13, OUTPUT);
  // инициализируем дисплей
  lcd.init();
  // Включаем подсветку дисплея
  lcd.backlight();
  // переходим на позицию - первый ноль это позиция символа
  // второй ноль это позиция строки
  lcd.setCursor(0, 0);
  // выводим надпись  
  lcd.print(first_string);
  
//  delay(3000);
}


void loop()
{


}
