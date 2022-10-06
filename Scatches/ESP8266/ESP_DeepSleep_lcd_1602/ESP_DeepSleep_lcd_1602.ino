const uint32_t sleepTime = 5000000; // 5 sec.
const uint32_t mark = 0x12345678;

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x3F

extern "C" {
#include "user_interface.h"

extern struct rst_info resetInfo;
}

void setup() {
  uint32_t cnt;

//  pinMode(D0, WAKEUP_PULLUP);
  ESP.rtcUserMemoryRead(0, &cnt, sizeof(cnt));
  if ((cnt != mark) || (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)) {
    cnt = mark;
    ESP.rtcUserMemoryWrite(0, &cnt, sizeof(cnt));
    cnt = 0;
  }
  else {
    ESP.rtcUserMemoryRead(1, &cnt, sizeof(cnt));
  }
  lcd.init();
  lcd.backlight();
  if (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)
    lcd.print(F("Hello!"));
  else
    lcd.print(F("Good morning!"));
  lcd.setCursor(0, 1);
  lcd.print(++cnt);
  lcd.print(F(" time"));
  if (cnt > 1)
    lcd.print('s');
  ESP.rtcUserMemoryWrite(1, &cnt, sizeof(cnt));
  delay(2000);
  lcd.noBacklight();
  ESP.deepSleep(sleepTime);
  lcd.setCursor(0, 0);
  lcd.print(F("Good night!"));
}

void loop() {}
