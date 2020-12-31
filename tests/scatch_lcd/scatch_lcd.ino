#include <Wire.h>                  // подключаем библиотеку I2C
#include <LiquidCrystal_I2C.h>     // подключаем библиотеку дисплея 

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем какой дисплей

boolean flag = true;
int i = 0;
boolean pic = true;
const char* pict;
boolean oO = true;

void setup()
{
//  pinMode(5,OUTPUT);  
    pinMode(13,OUTPUT);

  // инициализируем дисплей
  lcd.init();

  // Включаем подсветку дисплея
  lcd.backlight();

  // переходим на позицию - первый ноль это позиция символа
  // второй ноль это позиция строки
  lcd.setCursor(0, 0);
  
  // выводим надпись 
  lcd.print("-=Hell o World=-");
  
  // переходим на позицию - первый ноль это позиция символа
  // вторая единица это позиция строки
//  lcd.setCursor(7, 1);

  // выводим надпись
//  lcd.print("oO");
}
void loop()
{
//  if (pic) pict = "oO";
//  else pict = "Oo";

  if (oO) pict = "o";
  else pict = "O";

//  digitalWrite(5, flag = !flag);
  digitalWrite(13, flag = !flag);

  delay(100);
  
  // переходим на позицию
  lcd.setCursor(i, 1);
  // выводим надпись
  lcd.print(pict);
  
  i++;
  if (i > 15){
    i = 0;
    oO = !oO;
  }
  oO = !oO;
}
