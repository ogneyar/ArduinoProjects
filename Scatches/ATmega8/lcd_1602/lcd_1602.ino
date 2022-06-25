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
  i = 0; // 8 байт (если 0)  
  j = 15; // 12 байт (если > 0)
  k = 0;  
  pict = (char *)" "; // 12 байт (если " ") + 2 байта за каждые 2 английских символа или 1 русских
  flag = true; // 4 байта если false и 6 байт если true  
  last_time = millis(); // 8 байт (если 0), 12 байт (если 1) и 30 байт (если millis()) 
  fi_string = (char *)first_string; // 12 байт

//  Serial.begin(9600); // 6 байт
//  Serial.println("Hell o world"); // 38 байт

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

}
