// ATtiny13

// ДАТЧИК ДВИЖЕНИЯ

#define motion_sensor 3
#define led_pin 4
#define photoresistor A1

word last_time;
int wait = 100;
int pr;
boolean flagON = false;
boolean debug = true;

void delay_millis(int del) {      
  if (millis() - last_time > del) {
      last_time = millis();
      sensor_polling();
  }
}

void sensor_polling() {
  if ( ! flagON) pr = analogRead(photoresistor);
  if(digitalRead(motion_sensor)==HIGH) {
    if (pr > 600) {
      digitalWrite(led_pin, HIGH);
      flagON = true;
    }else {
      digitalWrite(led_pin, LOW);
      flagON = false;
    }
    wait = 3000;
  }else {
    digitalWrite(led_pin, LOW);
    flagON = false;
    wait = 500;
  }
}

void setup() {
  pinMode(motion_sensor, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(photoresistor, INPUT);
  
  digitalWrite(motion_sensor, LOW);
  digitalWrite(led_pin, LOW);
  
  last_time = millis();
}
void loop() {
  delay_millis(wait);
}
