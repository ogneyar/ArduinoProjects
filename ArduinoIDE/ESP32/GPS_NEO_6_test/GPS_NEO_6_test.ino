
//

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // скорость 9600, формат 8 бит данных,  пины RX и TX на 16 и 17 выводах
}

void loop() {
  if (Serial2.available()) {
    Serial.println("-------------------");
    String data = Serial2.readStringUntil('\n');
    Serial.println("-------------------");
    Serial.println(data);
  }
}
