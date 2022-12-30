
// Nano

#define PIN_MQ2   A0   // имя пина для подключения MQ2
#define LED       13   // имя пина для подключения светодиода

int value;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
}

void loop() {
   // записываем полученные данные с датчика
   value = analogRead(PIN_MQ2);

   // выводим информацию на монитор порта
   Serial.println("VALUE - " + String(value));
   Serial.println(" ");

   // включаем светодиод при превышении определенного значения
   if (value > 200) { digitalWrite(LED, HIGH); }
   else { digitalWrite(LED, LOW); }

   delay(200);
}

//