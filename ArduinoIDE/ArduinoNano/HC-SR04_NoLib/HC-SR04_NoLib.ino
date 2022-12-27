
// Nano, LGT8

#define HC_TRIG 3
#define HC_ECHO 2

float distanceFilter = 0;

float getDistance(int);

// настройки
void setup() {
  Serial.begin(9600);       // для связи
  pinMode(HC_TRIG, OUTPUT); // trig выход
  pinMode(HC_ECHO, INPUT);  // echo вход
}
// цикл
void loop() {
  int temperature = 24; // представим, что получили с датчика
  float distance = getDistance(temperature);   // получаем расстояние
  distanceFilter += (distance - distanceFilter) * 0.2;  // фильтруем  
  Serial.println(distanceFilter);     // выводим
  delay(50);
}

// функция возвращает дистанцию в мм
float getDistance(int temperature) {
  // импульс 10 мкс
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  // измеряем время ответного импульса
  uint32_t us = pulseIn(HC_ECHO, HIGH);

  // считаем расстояние и возвращаем
  // return (us / 5.83);
  // откуда берётся 5.83? 
  // Для прохождения 1 м звуку понадобится 1 / 343 = 0.0029 с, или 2.915 мс. 
  // Мы получаем время туда и обратно, поэтому умножаем ещё на 2 и получаем 5.83

  // для расчёта расстояния в миллиметрах с учётом температуры в °С получим формулу: 
  // S = us * V / 2000
  // S = us * (0.609 * t + 330.75) / 2000 
  // S = us * (t * 6 / 10 + 330) / 2000 

   return (us * (temperature * 6 / 10 + 330) / 2000ul);
}

//