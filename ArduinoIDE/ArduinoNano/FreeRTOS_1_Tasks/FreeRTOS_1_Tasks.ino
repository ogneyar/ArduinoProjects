
// LGT8F328

#include <Arduino_FreeRTOS.h>
  
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void TaskBlink3( void *pvParameters );

void setup() {
  xTaskCreate(TaskBlink1, "Blink1", 128, NULL, /* Priority = */ 0,  NULL);
  xTaskCreate(TaskBlink2, "Blink2", 128, NULL, /* Priority = */ 0,  NULL);
  xTaskCreate(TaskBlink3, "Blink3", 128, NULL, /* Priority = */ 0,  NULL);
}

void loop() {}

void TaskBlink1( void *pvParameters ) {
  pinMode(1, OUTPUT);
  while(1) {
    digitalWrite(1, HIGH);
    vTaskDelay(700/portTICK_PERIOD_MS);
    digitalWrite(1, LOW);
    vTaskDelay(700/portTICK_PERIOD_MS);
  }
}

void TaskBlink2( void *pvParameters ) {
  pinMode(2, OUTPUT);
  while(1) {
    digitalWrite(2, HIGH);
    vTaskDelay(700/portTICK_PERIOD_MS);
    digitalWrite(2, LOW);
    vTaskDelay(700/portTICK_PERIOD_MS);
  }
}

void TaskBlink3( void *pvParameters ) {
  pinMode(3, OUTPUT);
  while(1) {
    digitalWrite(3, HIGH);
    vTaskDelay(700/portTICK_PERIOD_MS);
    digitalWrite(3, LOW);
    vTaskDelay(700/portTICK_PERIOD_MS);
  }
}

//
