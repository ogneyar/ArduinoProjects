#include <Wire.h>                  // подключаем библиотеку I2C
#include <LiquidCrystal_I2C.h>     // подключаем библиотеку дисплея 

LiquidCrystal_I2C lcd(0x27, 16, 2); // Устанавливаем какой дисплей

void setup()
{  
  // инициализируем дисплей
  lcd.init();
  // Включаем подсветку дисплея
  lcd.backlight();
  // переходим на позицию - первый ноль это позиция символа
  // второй ноль это позиция строки
  lcd.setCursor(0, 0);
  // выводим надпись  
  lcd.print("-=Hell o W rld=-");

  delay(100);  
  lcd.setCursor(0, 1);
  lcd.print("-=Hell o   ork=-");
  
  delay(1000);
  lcd.setCursor(11, 0);
  lcd.print("old=-");
  
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print("  old=-");
  
  delay(1000);
  lcd.setCursor(7, 0);
  lcd.print("    old=-");
  
  delay(1000);
  lcd.setCursor(7, 1);
  lcd.print("    ork=-");
}


void loop() {
}
