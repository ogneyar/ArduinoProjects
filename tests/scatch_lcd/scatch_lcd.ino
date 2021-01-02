#include <Wire.h>                  // подключаем библиотеку I2C
#include <LiquidCrystal_I2C.h>     // подключаем библиотеку дисплея 

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем какой дисплей

boolean flag;
int i, j, k, m;
const char* pict;
char * first_string, * fi_string;
word last_time;

void setup()
{

  Serial.begin(9600);
  Serial.println("Hell o world");


  pinMode(13,OUTPUT);
  // инициализируем дисплей
  lcd.init();
  // Включаем подсветку дисплея
  lcd.backlight();
  // переходим на позицию - первый ноль это позиция символа
  // второй ноль это позиция строки
  lcd.setCursor(0, 0);  
  // выводим надпись 
  first_string = "-=Hell o World=-";  
  lcd.print(first_string);
  fi_string = first_string;

  delay(1000);

  i = 0;
  j = 15;
  k = 0;
  pict = " ";
  flag = true;
  last_time = millis();
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

    Serial.println(fi_string);

    if (k > 15){
      k = 0;
      j--;
      fi_string = first_string;
    } 

    if (j == 0) {
      k++;
      m = 0;
      fi_string = "";
      for (int r = k; r < 16; r++) {
        fi_string[m] = first_string[r];
        // lcd.setCursor(m, 0);
        // lcd.print(first_string[r]);
        m++;
      }
      for (int s = m; s < 16; s++) {
        fi_string[s] = ' ';
        // lcd.setCursor(m, 0);
        // lcd.print(" ");
      }
      // lcd.setCursor(0, 0);
      // lcd.print(fi_string);
      // delay(50);
    }else j--;
    

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
      pict = "O ";
    }
    if ( i > 15 ){
      i = 0;
      pict = " ";
    }

    delay(30);

  }

}
