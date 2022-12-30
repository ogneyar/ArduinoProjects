
// Nano

// Вывод сырых данных в порт

#define MICROPHONE A0

void setup() {
  Serial.begin(9600);
  // переключаем на внешнее опорное
  // его подключаем к 3.3V (3V3 подключаем к REF через резистор 10кОм)
  analogReference(EXTERNAL);  
}
void loop() {
  Serial.println(analogRead(MICROPHONE));
}

//