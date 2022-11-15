
// Nano

// Вывод сырых данных в порт

void setup() {
  Serial.begin(9600);
  // переключаем на внешнее опорное
  // его подключаем к 3.3V
  analogReference(EXTERNAL);  
}
void loop() {
  Serial.println(analogRead(0));
}
