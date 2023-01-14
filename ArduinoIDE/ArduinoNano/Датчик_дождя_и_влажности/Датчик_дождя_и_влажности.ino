
// LGT8F328

// выводы, подключенные к датчику
#define sensorPower 7 // D7
#define sensorPinD0 8 // D8
#define sensorPinA0 0 // A0

void setup() 
{
  pinMode(sensorPower, OUTPUT);

  // изначально держим датчик выключенным
  digitalWrite(sensorPower, LOW);

  Serial.begin(9600);
}

void loop() 
{
  // получить показания из функции ниже и вывести их в печать
  int valD, valA;
  readSensor(&valD, &valA);
  Serial.print("Digital Output: ");
  Serial.println(valD);
  Serial.print("Analog Output: ");
  Serial.println(valA);

  // определить состояние дождя
  if (valD) { // дождя нет
    Serial.println("Status: Clear");
  }else { // идет дождь
    Serial.println("Status: It's raining");
  }

  // брать показания каждую секунду
  delay(1000);  
  Serial.println();
}

// эта функция возвращает значение на выходе датчика
void readSensor(int *valD0, int *valA0) {
  digitalWrite(sensorPower, HIGH);   // включить датчик
  delay(10);                         // дать время питанию установиться
  *valD0 = digitalRead(sensorPinD0);  // прочитать выходной сигнал датчика
  *valA0 = analogRead(sensorPinA0);  // прочитать выходной сигнал датчика  
  digitalWrite(sensorPower, LOW);    // выключить датчик
}

