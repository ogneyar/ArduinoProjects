
// Nano

#include "MPU6050.h"
MPU6050 mpu;

void setup() {
  // запускаем всё
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();

  mpu.setInterruptMode(true);         // включаем режим прерываний
  mpu.setIntMotionEnabled(true);      // включаем прерывания движения
  mpu.setMotionDetectionThreshold(2); // порог 0..255
  mpu.setMotionDetectionDuration(2);  // таймаут 0..255
  attachInterrupt(0, isr, RISING);    // прерывание
}

volatile bool motion;
void isr() {
  motion = true;  // флаг прерывания
}

void loop() {
  // по флагу прерывания пишем в порт
  // прерыванием можно будить МК и так далее
  if (motion) {
    Serial.println("Motion!");
    motion = false;
  }
}
