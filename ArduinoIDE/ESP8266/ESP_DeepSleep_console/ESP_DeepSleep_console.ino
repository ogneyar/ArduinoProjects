
const uint32_t sleepTime = 5000000; // 5 sec.
const uint32_t mark = 0x12345678;


extern "C" {
#include "user_interface.h"

extern struct rst_info resetInfo;
}

void setup() {
  uint32_t cnt;

  Serial.begin(9600);

  // НЕ ЗАБЫВАЕМ!!! D0 -> RST соединяем через резистор 470 Ом
  // pinMode(D0, WAKEUP_PULLUP); 

  ESP.rtcUserMemoryRead(0, &cnt, sizeof(cnt));
  if ((cnt != mark) || (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)) {
    cnt = mark;
    ESP.rtcUserMemoryWrite(0, &cnt, sizeof(cnt));
    cnt = 0;
  }
  else {
    ESP.rtcUserMemoryRead(1, &cnt, sizeof(cnt));
  }

  if (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)
    Serial.println(F("Hello!"));
  else
    Serial.println(F("Good morning!"));
    
  Serial.print(++cnt);
  Serial.print(F(" time"));
  if (cnt > 1) Serial.println('s');
  else Serial.println();
  
  ESP.rtcUserMemoryWrite(1, &cnt, sizeof(cnt));
  delay(2000);

  Serial.println(F("Good night!"));

  ESP.deepSleep(sleepTime);

  Serial.println(F("Bro!"));
}

void loop() {}
