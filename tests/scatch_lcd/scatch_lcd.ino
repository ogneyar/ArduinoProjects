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

  Serial.begin(9600); // 6 байт
  Serial.println("Hell o world"); // 38 байт

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
  
  delay(3000);
}


void loop()
{

  if (millis() - last_time > 200) {

    last_time = millis();
    digitalWrite(13, flag = !flag);


    // --------------------
    // рисуем первую строку
    // --------------------

    if ( j == 15 ) {
      lcd.setCursor(0, 0);
      lcd.print("                ");
    }

    // переходим на позицию
    lcd.setCursor(j, 0);
    // выводим надпись
    lcd.print(fi_string);

    Serial.println(fi_string); // 44 байта

    if (k > 15) {
      k = 0;
      j--;
      fi_string = (char *)first_string;
    }

    if (j == 0) {
      k++;
      m = 0;
      fi_string = (char *)"";
      for (r = k; r < 16; r++) {
        fi_string[m] = first_string[r];
        m++;
      }
      for (s = m; s < 16; s++) {
        fi_string[s] = ' ';
      }
      fi_string[s] = '\0';
    } else j--;


    if ( j < 0 ) j = 15;


    // --------------------
    // рисуем вторую строку
    // --------------------

    // переходим на позицию
    lcd.setCursor(i, 1);
    // выводим надпись
    lcd.print(pict);
    if ( i != 0 || pict != " " ) {
      i++;
    }
    if ( i == 0 ) {
      pict = (char *)"O ";
    }
    if ( i > 15 ) {
      i = 0;
      pict = (char *)" ";
    }

    delay(500);

  }

}
