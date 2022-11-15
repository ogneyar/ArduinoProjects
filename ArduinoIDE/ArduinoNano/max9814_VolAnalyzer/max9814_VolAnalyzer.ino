
// Nano

// Вывод сырых данных в порт

#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);  // микрофон на А0

void setup() {
  Serial.begin(9600);

  // переключаем на внешнее опорное
  // его подключаем к 3.3V
  analogReference(EXTERNAL);
}

void loop() {
  // если анализ завершён
  if (analyzer.tick()) {
    Serial.println(analyzer.getVol());
  }
}
