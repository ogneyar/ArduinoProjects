
// Nano, LGT8F328

#define STRIP_PIN 3     // пин ленты
#define NUMLEDS 1       // кол-во светодиодов

#include <microLED.h>   // подключаем библу

microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

void setup() {
  strip.setBrightness(60);
}

void loop() {
  strip.set(0, mRGB(255, 255, 255));  // диод 0, цвет RGB (255 255 255) (белый)
  strip.show();                       // выводим все изменения на ленту
  delay(1000);
  strip.set(0, mRGB(255, 0, 0));      // диод 0, цвет RGB (255 0 0) (красный)
  strip.show();
  delay(1000);
  strip.set(0, mRGB(0, 255, 0));      // диод 0, цвет RGB (0 255 0) (зелёный)
  strip.show();
  delay(1000);
  strip.set(0, mRGB(0, 0, 255));      // диод 0, цвет RGB (0 0 255) (синий)
  strip.show();
  delay(1000);
  strip.leds[0] = mAqua;              // диод 0, цвет aqua
  strip.show();
  delay(1000);  
  strip.set(0, mWheel(1200));         // диод 0, цвет 1200
  strip.show();
  delay(1000);
  strip.set(0, mKelvin(3500));         // диод 0, цветовая температура 3500К
  strip.show();
  delay(1000);
}
