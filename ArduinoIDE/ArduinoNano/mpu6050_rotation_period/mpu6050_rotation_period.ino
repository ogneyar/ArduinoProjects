
// Nano

// скетч определения периода вращения акселерометра
#define DEADZONE 700
#define MIN_LOOP 100
#define MAX_LOOP 900
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
float k = 0.2;
int16_t ax, ay, az, ay_f;
int16_t gx, gy, gz;
int last_acc, level;
boolean rising_flag = true, falling_flag = false, toggle_flag;
unsigned long maxTimer, analyzeTimer;
int loopTime;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // Acceleration range: ± 2   ± 4  ± 8  ± 16 g
  // 1G value:           16384 8192 4096 2048
  // MAX G value:        32768
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);

  // Gyroscope range: 250   500  1000 2000 °/s
  // MAX value:       32768
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
}

void loop() {
  if (millis() - analyzeTimer > 3) {                   // шаг анализа периода
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);      // запросить данные
    ay_f += (ay - ay_f) * k;                           // отфильтровать
    if (rising_flag)   // поднимаемся
      // ждём падения сигнала на величину DEADZONE
      if (last_acc < ay_f + DEADZONE) {
        // если сигнал не упал, принять величину как точку для следующего сравнения
        last_acc = ay_f;
        toggle_flag = true;
      } else {
        // если есть падение, и прошёл минимальный период
        // (защита от всяких случайных ударов и дёрганий)
        if (toggle_flag && (millis() - maxTimer > MIN_LOOP)) {
          toggle_flag = false;
          rising_flag = false;
          falling_flag = true;
          loopTime = millis() - maxTimer;   // расчёт периода движения
          maxTimer = millis();
          //level = last_acc;
        }
      }
    if (falling_flag) {  // опускается
      // ждём прироста сигнала на величину DEADZONE
      if (last_acc > ay_f - DEADZONE) {  // падаем
        // если сигнал не вырос, принять величину как точку для следующего сравнения
        last_acc = ay_f;
        toggle_flag = true;
      } else {
        // если есть прирост, и прошёл минимальный период
        // (защита от всяких случайных ударов и дёрганий)
        if (toggle_flag && (millis() - maxTimer > MIN_LOOP)) {
          toggle_flag = false;
          rising_flag = true;
          falling_flag = false;
          //level = last_acc;
        }
      }
    }
    /*
        Serial.print("$");
        Serial.print(ay_f);
        Serial.print(" ");
        Serial.print(level);
        Serial.print(" ");
        Serial.print(loopTime*10);
        Serial.println(";");
    */
    if (millis() - maxTimer > MAX_LOOP) loopTime = 0;
    Serial.println(loopTime);
    analyzeTimer = millis();
  }
}
