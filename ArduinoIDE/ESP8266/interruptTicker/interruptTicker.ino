
// Wemos D1 mini (не проверял)

#include <Ticker.h>

uint8_t blink_loop = 0;
uint8_t blink_mode = 0;
uint8_t modes_count = 0;

Ticker blinker;

void timerIsr()
{
  if( blink_mode & 1<<(blink_loop&0x07) ) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
  blink_loop++;
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  blink_mode = 0B00000000;
  blinker.attach(0.125, timerIsr);
}

void loop() {
  blink_mode = 0B00001111; //Мигание по 0.5 сек
  delay(5000);
  blink_mode = 0B00000001; //Короткая вспышка раз в секунду
  delay(5000);
  blink_mode = 0B00000101; //Две короткие вспышки раз в секунду
  delay(5000);
  blink_mode = 0B00010101; //Три короткие вспышки раз в секунду
  delay(5000);
  blink_mode = 0B01010101; //Частые короткие вспышки (4 раза в секунду)
  delay(5000);
}
