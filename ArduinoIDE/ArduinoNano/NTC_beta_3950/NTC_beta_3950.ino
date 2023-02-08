
// LGT8F328P

#include <GyverNTC.h>

// термистор на пине А0
// сопротивление резистора 10к
// тепловой коэффициент 3950
GyverNTC therm(0, 10000, 3950);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // вывести температуру (чтение с усреднением)
  Serial.println(therm.getTempAverage());
  delay(500);
}

//
