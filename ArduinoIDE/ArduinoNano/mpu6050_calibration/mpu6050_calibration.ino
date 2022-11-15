
// Nano

// калибровка и запись в EEPROM
// при запуске настраиваем оффсеты
// послать символ в сериал - начать повторную калибровку
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <EEPROM.h>

MPU6050 mpu;
#define BUFFER_SIZE 100
#define START_BYTE 1010
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();

  //----------------- ВСПОМИНАЕМ ОФФСЕТЫ ------------------------
  int offsets[6];
  EEPROM.get(START_BYTE, offsets);

  // ставим оффсеты из памяти
  mpu.setXAccelOffset(offsets[0]);
  mpu.setYAccelOffset(offsets[1]);
  mpu.setZAccelOffset(offsets[2]);
  mpu.setXGyroOffset(offsets[3]);
  mpu.setYGyroOffset(offsets[4]);
  mpu.setZGyroOffset(offsets[5]);
  //----------------- ВСПОМИНАЕМ ОФФСЕТЫ ------------------------

  Serial.println(F("Send any character to start sketch"));
  delay(100);
  while (1) {
    //входим в бесконечный цикл
    if (Serial.available() > 0) {     // если нажата любая кнопка
      Serial.read();                  // прочитать (чтобы не висел в буфере)
      break;                          // выйти из цикла
    }
  }
  delay(1000);
}

void loop() {
  calibration();
  Serial.println("Current offsets:");
  Serial.println("accX accY accZ gyrX gyrY gyrZ");
  Serial.print(mpu.getXAccelOffset()); Serial.print(", ");
  Serial.print(mpu.getYAccelOffset()); Serial.print(", ");
  Serial.print(mpu.getZAccelOffset()); Serial.print(", ");
  Serial.print(mpu.getXGyroOffset()); Serial.print(", ");
  Serial.print(mpu.getYGyroOffset()); Serial.print(", ");
  Serial.print(mpu.getZGyroOffset()); Serial.println(" ");
  Serial.println(" ");

  // выводим значения после калибровки
  Serial.println("Readings:");
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(ax); Serial.print(" ");
  Serial.print(ay); Serial.print(" ");
  Serial.print(az); Serial.print(" ");
  Serial.print(gx); Serial.print(" ");
  Serial.print(gy); Serial.print(" ");
  Serial.println(gz);
  delay(20);
  while (1);
}

// =======  ФУНКЦИЯ КАЛИБРОВКИ И ЗАПИСИ В ЕЕПРОМ =======
void calibration() {
  long offsets[6];
  long offsetsOld[6];
  int16_t mpuGet[6];

  // используем стандартную точность
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

  // обнуляем оффсеты
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  delay(5);

  for (byte n = 0; n < 10; n++) {     // 10 итераций калибровки
    for (byte j = 0; j < 6; j++) {    // обнуляем калибровочный массив
      offsets[j] = 0;
    }
    for (byte i = 0; i < 100 + BUFFER_SIZE; i++) {
      // делаем BUFFER_SIZE измерений для усреднения
      mpu.getMotion6(&mpuGet[0], &mpuGet[1], &mpuGet[2], &mpuGet[3], &mpuGet[4], &mpuGet[5]);

      if (i >= 99) {                         // пропускаем первые 99 измерений
        for (byte j = 0; j < 6; j++) {
          offsets[j] += (long)mpuGet[j];   // записываем в калибровочный массив
        }
      }
    }

    for (byte i = 0; i < 6; i++) {
      offsets[i] = offsetsOld[i] - ((long)offsets[i] / BUFFER_SIZE); // учитываем предыдущую калибровку
      if (i == 2) offsets[i] += 16384;                               // если ось Z, калибруем в 16384
      offsetsOld[i] = offsets[i];
    }

    // ставим новые оффсеты
    mpu.setXAccelOffset(offsets[0] / 8);
    mpu.setYAccelOffset(offsets[1] / 8);
    mpu.setZAccelOffset(offsets[2] / 8);
    mpu.setXGyroOffset(offsets[3] / 4);
    mpu.setYGyroOffset(offsets[4] / 4);
    mpu.setZGyroOffset(offsets[5] / 4);
    delay(2);
  }

  // пересчитываем для хранения
  for (byte i = 0; i < 6; i++) {
    if (i < 3) offsets[i] /= 8;
    else offsets[i] /= 4;
  }

  // запись в память
  EEPROM.put(START_BYTE, offsets);
}
