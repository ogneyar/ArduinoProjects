#include <microDS18B20.h>
MicroDS18B20 sensor(2);  // Создаем термометр без адреса на пине D2
uint8_t address[8];       // Создаем массив для адреса
void setup() {
  Serial.begin(9600);
}
void loop() {
  // читаем адрес термометра в указанный массив
  sensor.readAddress(address);
  Serial.print('{');
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("0x");
    Serial.print(address[i], HEX);  // Выводим адрес
    if (i < 7) Serial.print(", ");
  }
  Serial.println('}');  
  delay(3000);
}
