
// LGT8F328

#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t queue_1;
void TaskADC(void *pvParameters);
void TaskLenta(void *pvParameters);
void TaskBlink(void *pvParameters);

void setup() {
  Serial.begin(9600);
  queue_1 = xQueueCreate(4, sizeof(int));
  if (queue_1 == NULL) {
    Serial.println("Queue can not be create");
  }

  xTaskCreate(TaskADC, "TaskADC", 128, NULL, /* Priority = */ 0,  NULL);
  xTaskCreate(TaskLenta, "TaskLenta", 128, NULL, /* Priority = */ 0,  NULL);
  xTaskCreate(TaskBlink, "TaskBlink", 128, NULL, /* Priority = */ 0,  NULL);
}

void loop() {}

void TaskADC(void *pvParameters) {
  const int analogPin = A0;
  int sensorValue = 0;
  int outputValue = 0;  
  while(1) {
    sensorValue = analogRead(analogPin);
    outputValue = map(sensorValue, 0, 1023, 0, 5);
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
    xQueueSend(queue_1, &outputValue, portMAX_DELAY);
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void TaskLenta(void *pvParameters) {
  int outputValue = 0;
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  while(1) {
    if (xQueueReceive(queue_1, &outputValue, portMAX_DELAY) == pdPASS) {
      switch(int(outputValue)) {
        case 0:
        {
          digitalWrite(1, HIGH);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;          
        }
        case 1:
        {
          digitalWrite(1, LOW);
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;          
        }
        case 2:
        {
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;          
        }
        case 3:
        {
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          break;          
        }
        case 4:
        {
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          break;          
        }
      }
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void TaskBlink(void *pvParameters) {
  pinMode(6, OUTPUT);
  while(1) {
    digitalWrite(6, HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(6, LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

//
