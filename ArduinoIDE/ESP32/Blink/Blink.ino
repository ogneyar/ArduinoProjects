
// Lolin_S2_mini, Lolin_C3_mini, ESP32C3_WeAct, ESP32_Lite(ESP32_Dev_Module), ESP32_WROOM(ESP32_Dev_Module)

// Lolin_S2_mini (LED_BUILTIN 15)
// ESP32C3_WeAct (LED_BUILTIN 8)
// ESP32_Lite(ESP32_Dev_Module) (LED_BUILTIN 8)
// ESP32_WROOM-DA (LED_BUILTIN 1) TX0

#ifndef LED_BUILTIN
#define LED_BUILTIN 1
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

//