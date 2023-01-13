#include <Arduino.h>
#include "Buzzer.h"

//#define LED_PIN   2
#define LED_LEVEL LOW

constexpr uint8_t BUZZER_PIN = 18;
constexpr uint32_t BLINK_TIME = 25; // 25 ms.

const char *notes[] = {
  "Jingle Bells:d=8,o=5,b=125:g,e6,d6,c6,2g,g,e6,d6,c6,2a,a,f6,e6,d6,b,g,b,d6,g.6,16g6,f6,d6,2e6,g,e6,d6,c6,2g,16f#,g,e6,d6,c6,2a,a,f6,e6,d6,g6,16g6,16f#6,16g6,16f#6,16g6,16g#6,a.6,16g6,e6,d6,4c6,4g6,e6,e6,e.6,16d#6,e6,e6,e.6,16d#6,e6,g6,c.6,16d6,2e6,f6,f6,f.6,16f6,f6,e6,e6,16e6,16e6,e6,d6,d6,e6,2d6",
  "We Wish You A Merry Christmas:d=4,o=5,b=200:d,g,8g,8a,8g,8f#,e,e,e,a,8a,8b,8a,8g,f#,d,d,b,8b,8c6,8b,8a,g,e,d,e,a,f#,2g,d,g,8g,8a,8g,8f#,e,e,e,a,8a,8b,8a,8g,f#,d,d,b,8b,8c6,8b,8a,g,e,d,e,a,f#,1g,d,g,g,g,2f#,f#,g,f#,e,2d,a,b,8a,8a,8g,8g,d6,d,d,e,a,f#,2g"
};

Buzzer<> *buzzer;

void setup() {
/*
  Serial.begin(115200);
*/

#ifdef LED_PIN
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ! LED_LEVEL);
#endif

  buzzer = new Buzzer<>(BUZZER_PIN);
  if (buzzer->playRTTTL(notes[0])) {
    while (buzzer->playing()) {
#ifdef LED_PIN
      digitalWrite(LED_PIN, LED_LEVEL == (millis() % 500 < BLINK_TIME));
#endif
      delay(1);
    }
  }
#ifdef LED_PIN
  digitalWrite(LED_PIN, ! LED_LEVEL);
#endif
  delay(1000);
  if (buzzer->playRTTTL(notes[1])) {
    while (buzzer->playing()) {
#ifdef LED_PIN
      digitalWrite(LED_PIN, LED_LEVEL == (millis() % 1000 < BLINK_TIME));
#endif
      delay(1);
    }
  }
#ifdef LED_PIN
  digitalWrite(LED_PIN, ! LED_LEVEL);
#endif
}

void loop() {}
