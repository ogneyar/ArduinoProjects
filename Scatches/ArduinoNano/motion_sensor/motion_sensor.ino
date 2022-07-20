// Arduino Nano

#define motion_sensor 6
#define led_pin 2
#define photoresistor A0

word last_time;
int wait = 100;
int pr;
boolean flagON = false;

void delay_millis(int del) {      
  if (millis() - last_time > del) {
      last_time = millis();

      sensor_polling();
  }
}
void sensor_polling() {
  
  if ( ! flagON) pr = analogRead(photoresistor);
  Serial.print("photoresistor: ");
  Serial.println(pr);
  
  if(digitalRead(motion_sensor)==HIGH) {
    if (pr > 600) {
      Serial.println("Somebody is here. Led ON.");
      digitalWrite(led_pin, HIGH);
      flagON = true;
    }else {
      Serial.println("Somebody is here. Led OFF.");
      digitalWrite(led_pin, LOW);
      flagON = false;
    }
    wait = 3000;
  }
  else {
    Serial.println("Nobody.");
    digitalWrite(led_pin, LOW);
    flagON = false;
    wait = 500;
  }
}

void setup() {
  Serial.begin(9600);
  
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
