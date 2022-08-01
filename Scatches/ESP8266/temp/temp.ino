
//#include<stdio.h>
//#include <util/delay.h>

void test(char * str) {
  uint16_t one = 'а'; 
//  if ( (str[0] & 0x00ff == 'а' >> 8) && ((byte)str[1] & 0x00ff == (byte)'а' & 0x00ff) ) 
  if (str[0]<<8 | str[1] == 'а')
    Serial.println("равны");
  
  Serial.print("Первая часть: ");
  Serial.println(str[0] & 0x00ff);
  Serial.print("Вторая часть: ");
  Serial.println(str[1] & 0x00ff);
  
//  Serial.println(strlen(str));

  Serial.println(str[0]<<8 | str[1]);

  Serial.println('а');

  Serial.print("Первая часть: ");
  Serial.println('а' >> 8 & 0x00ff);
  
  Serial.print("Вторая часть: ");
  Serial.println('а' & 0x00ff);

  Serial.println("-----------------");
  
    switch(str[0]<<8 | str[1]) {
        case 'а': 
//            a(x, y);
          Serial.println("это а!");
        break;
        case 'б': 
//            b(x, y);
          Serial.println("это б!");
        break;
        case 'в': 
//            v(x, y);
          Serial.println("это в!");
        break;
        case 'г': 
//            g(x, y);
          Serial.println("это г!");
        break;
        case 'д': 
//            d(x, y);
          Serial.println("это д!");
        break;
    }
    Serial.println("-----------------");
}

void setup() {
    Serial.begin(9600);
    delay(500);
    
    Serial.println("Привет :)");
    
    char c[] = "абвгд";
      
    test(c);    
}

void loop() {
  
}
