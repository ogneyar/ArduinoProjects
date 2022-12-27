
// Nano

#define J_VRX 0 // A0
#define J_VRY 1 // A1
#define J_SW 3 // D3

void setup() {
  Serial.begin(9600);
  pinMode(J_SW, INPUT_PULLUP);
}

void loop() {
  Serial.print(analogRead(J_VRX));
  Serial.print(',');
  Serial.print(analogRead(J_VRY));
  Serial.print(',');
  Serial.println(digitalRead(J_SW) * 100);
}

//