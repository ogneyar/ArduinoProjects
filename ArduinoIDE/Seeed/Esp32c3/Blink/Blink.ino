
// Seeed ESP32C3 (через UART - RX-D7, TX-D6)

void setup() {
  pinMode(4, OUTPUT); // GPIO2 = D0 // GPIO3 = D1 // GPIO4 = D2 // GPIO5 = D3
}

void loop() {
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
}
