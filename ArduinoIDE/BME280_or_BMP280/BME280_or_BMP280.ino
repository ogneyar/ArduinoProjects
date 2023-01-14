
// LGT8F328

// если bme.readHumidity() = 0.00, значит датчик BMP280 без датчика влажности, иначе BME280

#define BME280 0x76

#include <GyverBME280.h>

GyverBME280 bme;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");  
  // запуск датчика и проверка на работоспособность
  if (!bme.begin(BME280)) Serial.println("Error!");
}

void loop() {
  // температура
  Serial.print("Temperature: ");
  Serial.println(bme.readTemperature());
  // влажность
  Serial.print("Humidity: ");
  Serial.println(bme.readHumidity());
  // давление
  Serial.print("Pressure: ");
  Serial.println(bme.readPressure());
  Serial.println();
  delay(1000);
}
