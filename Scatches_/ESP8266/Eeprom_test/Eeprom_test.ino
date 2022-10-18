
// Wemos D1 mini

#include <EEPROM.h>

int addressWrite = 0;
int addressRead = 0;
byte value;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(2,1);
  digitalWrite(2,0);
}

void loop() {

  if (addressWrite < 512) { // записываем в EEPROM
    // analogRead вернёт значение от 0 до 1023
    // а в EEPROM в одной ячейке помещается от 0 до 255
    // поэтому значение делим на 4
    //value = analogRead(A0) / 4;
    value = (byte)analogRead(A0);

    EEPROM.write(addressWrite, value+addressWrite);
    Serial.print(".");
    addressWrite++;

    delay(50);
   
  }else { // считываем из EEPROM
    if (addressWrite == 512) {
      if (EEPROM.commit()) {
        Serial.println("\r\nEEPROM successfully committed");
      } else {
        Serial.println("\r\nERROR! EEPROM commit failed");
      }
      addressWrite = 513;
    }else {
      if (addressRead < 512) {
        value = EEPROM.read(addressRead);
        digitalWrite(2,1);
  
        Serial.print(addressRead);
        Serial.print("\t");
        Serial.print(value, BIN);
        Serial.println();
  
        addressRead++;
  
      }else {
        digitalWrite(2,1);
        //while(true);
        ESP.deepSleep(10000000); // 10 секунд
      }
    }

    delay(100);
    digitalWrite(2,0);
  }
  
}
