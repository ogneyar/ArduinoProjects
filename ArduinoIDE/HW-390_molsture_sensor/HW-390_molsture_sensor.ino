
// LGT8F328

// порог срабатывания
#define DRY_SIGNAL 230
#define SENSOR_POWER 7 // D7
#define SENSOR_PIN 0 // A0

void setup() {
  // пин светодиода как выход
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(SENSOR_POWER, OUTPUT);
  // изначально держим датчик выключенным
  digitalWrite(SENSOR_POWER, LOW);
}

void loop() {  
  int value = readSensor();
  Serial.print("Analog Output: ");
  Serial.println(value);
  // если земля сухая - включаем светодиод
  if (value > DRY_SIGNAL) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Status: Dry"); // сухо
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Status: Wetly"); // влажно
  }
  delay(1000);
}

// эта функция возвращает значение на выходе датчика
int readSensor() {
  digitalWrite(SENSOR_POWER, HIGH);   // включить датчик
  delay(10);                         // дать время питанию установиться
  int val = analogRead(SENSOR_PIN);  // прочитать выходной сигнал датчика
  digitalWrite(SENSOR_POWER, LOW);    // выключить датчик
  return val;                        // вернуть значение
}
