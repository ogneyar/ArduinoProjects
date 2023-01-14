
// Nano, LGT8F328

// AM312 - дальность всего 2 метра :'(

// если не используешь датчик освещения
#define WITHOUT_PHOTORESISTOR

#define MOTION_SENSOR 6 // D6
#define LED_PIN 13 // D13
#define PHOTORESISTOR 0 // A0

word last_time;
word current_millis;
int wait = 100;
int pr;
boolean flag = false;


void setup() {
  Serial.begin(9600);
  
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTORESISTOR, INPUT);
  
  digitalWrite(MOTION_SENSOR, LOW);
  digitalWrite(LED_PIN, LOW);
  
  last_time = millis();
}

void loop() {
  current_millis = millis();
  if (current_millis - last_time > wait) {
      last_time = current_millis;

      sensor_polling();
  }
}


void sensor_polling() { 
#ifndef WITHOUT_PHOTORESISTOR
  if ( ! flag) pr = analogRead(PHOTORESISTOR);
  Serial.print("photoresistor: ");
  Serial.println(pr);
#endif
  if(digitalRead(MOTION_SENSOR)==HIGH) {    
#ifndef WITHOUT_PHOTORESISTOR
    if (pr > 600) {
#endif
      Serial.println("Somebody is here. Led ON.");
      digitalWrite(LED_PIN, HIGH);
      flag = true;
#ifndef WITHOUT_PHOTORESISTOR
    }else {
      Serial.println("Somebody is here. Led OFF.");
      digitalWrite(LED_PIN, LOW);
      flag = false;
    }
#endif
    wait = 3000;
  }else {
    Serial.println("Nobody.");
    digitalWrite(LED_PIN, LOW);
    flag = false;
    wait = 500;
  }
}
