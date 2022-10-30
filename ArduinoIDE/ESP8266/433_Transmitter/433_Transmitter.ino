
// Wemos D1 mini

#define BTN  D3
#define LED  D4

#include <Gyver433.h>
Gyver433_TX<5> tx;  // указали пин (D1)

char data[] = "Open this"; // строка для отправки

void setup() {
  Serial.begin(9600);  
  Serial.println();
  Serial.println("Start...");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  delay(300);

  tx.sendData(data);
  ESP.deepSleep(1000000);

  
  pinMode(BTN, INPUT_PULLUP);
  //digitalWrite(BTN, HIGH);
}


void loop() {
//  if (!digitalRead(BTN)) {
//    tx.sendData(data);
//    ESP.deepSleep(30e6);
//  }
  //Serial.println(data);
  //delay(100);
}
