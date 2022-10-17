#include "LuatOS_C3.h"
#include <Arduino.h>

TFT_eSPI tft = TFT_eSPI();
char buf[32] = {0};
unsigned long lastMs = 0;
long check1s = 0;
TFT_eSprite drawBuf(&tft);

void setup() {
  disableCore0WDT();
  Serial.begin(115200);
  Serial.println("Hello ESP32C3!!");
  initTFT();
  initLEDs();
  tft.println("Start Config WiFi!");
  autoConfigWifi();
  tft.println("Wifi Connected!");
  sprintf(buf, "IP: %s", WiFi.localIP().toString().c_str());
  tft.println(buf);
  configTime(TZ_SEC, DST_SEC, "ntp.ntsc.ac.cn", "ntp1.aliyun.com");
  delay(2000);
  drawBuf.createSprite(TFT_HEIGHT, TFT_WIDTH);
  setupOTAConfig();
  tft.fillScreen(TFT_BLACK);
}

inline void showCurrentTime() {
  struct tm info;
  getLocalTime(&info);
  strftime(buf, 32, "%T", &info);
  drawBuf.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_BLACK);
  drawBuf.setTextColor(TFT_CYAN);
  drawBuf.setFreeFont(&FreeSerifBold18pt7b);
  drawBuf.drawCentreString(buf, 80, 10, 1);
  strftime(buf, 32, "%F", &info);
  drawBuf.setTextColor(TFT_GREEN);
  digitalWrite(PIN_LED1, HIGH);
  drawBuf.setFreeFont(&FreeSerifBold12pt7b);
  drawBuf.drawCentreString(buf, 80, 50, 1);
  digitalWrite(PIN_LED1, LOW);
  drawBuf.pushSprite(0, 0);
}

void loop() {
  auto ms = millis();
  if (ms - check1s > 1000) {
    check1s = ms;
    showCurrentTime();
    ArduinoOTA.handle();
  }
}