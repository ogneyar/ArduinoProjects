
// Uno

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9        // Пин rfid модуля RST
#define SS_PIN          10       // Пин rfid модуля SS

MFRC522 rfid(SS_PIN, RST_PIN);   // Объект rfid модуля
MFRC522::MIFARE_Key key;         // Объект ключа
MFRC522::StatusCode status;      // Объект статуса

void setup() {
  Serial.begin(9600);              // Инициализация Serial
  SPI.begin();                     // Инициализация SPI
  rfid.PCD_Init();                 // Инициализация модуля
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);  // Установка усиления антенны
  rfid.PCD_AntennaOff();           // Перезагружаем антенну
  rfid.PCD_AntennaOn();            // Включаем антенну

  for (byte i = 0; i < 6; i++) {   // Наполняем ключ
    //key.keyByte[i] = 0xFF;         // Ключ по умолчанию 0xFFFFFFFFFFFF
    key.keyByte[i] = 0xAB;         // Новый ключ 0xABABABABABAB
    // отныне для сектора 1 (блоков 4…7) мы используем только ключ B
  }
}

void loop() {
  // Занимаемся чем угодно
  
  static uint32_t rebootTimer = millis(); // Важный костыль против зависания модуля!
  if (millis() - rebootTimer >= 1000) {   // Таймер с периодом 1000 мс
    rebootTimer = millis();               // Обновляем таймер
    digitalWrite(RST_PIN, HIGH);          // Сбрасываем модуль
    delayMicroseconds(2);                 // Ждем 2 мкс
    digitalWrite(RST_PIN, LOW);           // Отпускаем сброс
    rfid.PCD_Init();                      // Инициализируем заного
  }

  if (!rfid.PICC_IsNewCardPresent()) return;  // Если новая метка не поднесена - вернуться в начало loop
  if (!rfid.PICC_ReadCardSerial()) return;    // Если метка не читается - вернуться в начало loop

  /* Аутентификация сектора, указываем блок безопасности #7 и ключ A */
  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 7, &key, &(rfid.uid));  
  // Аутентификация сектора новым ключом, отныне для сектора 1 (блоков 4…7) мы используем только ключ B
  //status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, 7, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {     // Если не окэй
    Serial.println("Auth error");         // Выводим ошибку
    return;
  }

  /* Запись блока, указываем блок безопасности #7 */
  uint8_t secBlockDump[16] = {                   // Дамп блока безопасности
    0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB,          // < Ключ A
    0x7F, 0x07,  0x88,                           // < Access Bits
    0xFF,                                        // < User байт (любой)
    0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB           // < Ключ B
  };
  status = rfid.MIFARE_Write(7, secBlockDump, 16); // Пишем массив в блок 7
  if (status != MFRC522::STATUS_OK) {              // Если не окэй
    Serial.println("Write error");                 // Выводим ошибку
    return;
  }
  Serial.println("Write OK");                     // Завершаем работу с меткой
  rfid.PICC_HaltA();                              
  rfid.PCD_StopCrypto1();
  
}
