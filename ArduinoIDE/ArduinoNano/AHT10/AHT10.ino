
// LGT8F328

//#define AHT10_ADDRESS 0x38

#include <Adafruit_AHT10.h>

Adafruit_AHT10 aht;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit AHT10 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 found");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");
  Serial.println();
  delay(500);
}
