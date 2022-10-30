
// Arduino Uno

#include <Gyver433.h>
Gyver433_TX<2> tx;

void setup() {
}

char data[] = "Hello from #xx"; // строка для отправки
byte count = 0;                 // счётчик для отправки

void loop() {
  // добавляем счётчик в строку
  data[12] = (count / 10) + '0';
  data[13] = (count % 10) + '0';
  if (++count >= 100) count = 0;

  // отправка данных любого типа
  tx.sendData(data);

  // отправка 10 раз в сек
  delay(100);
}
