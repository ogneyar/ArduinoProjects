
// Seeed ESP32C3 (через UART - RX-D7, TX-D6)

#include <Arduino.h>


void setup(void) {
    pinMode(4, OUTPUT); // GPIO2 = D0 // GPIO3 = D1 // GPIO4 = D2 // GPIO5 = D3
}

void loop(void) {
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(100);
}

