
// Nano

// Вывод сырых данных в порт

#define MICROPHONE A0

#include <VolAnalyzer.h> // lib от AlexGyver
VolAnalyzer analyzer(MICROPHONE);

void setup() {
  Serial.begin(9600);

  // переключаем на внешнее опорное
  // его подключаем к 3.3V (3V3 подключаем к REF через резистор 10кОм)
  analogReference(EXTERNAL);
}

void loop() {
  // если анализ завершён
  if (analyzer.tick()) {
    Serial.println(analyzer.getVol());
  }
}
