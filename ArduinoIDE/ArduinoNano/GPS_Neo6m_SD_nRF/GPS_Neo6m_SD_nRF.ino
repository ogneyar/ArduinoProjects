
// Nano

#include <SPI.h>            // Подключаем библиотеку для работы с SPI устройствами
#include <SD.h>             // Подключаем библиотеку для работы с SD картой
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <nRF24L01.h>       // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>           // Подключаем библиотеку для работы с nRF24L01+

#define RF_BUFFER_SIZE 128

// для Nrf-Nano: CE (Chip Enable) - D10, CS/CSN (Chip Select) - D9
RF24 radio(10, 9); // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
// char data[] = "Hello, bro!";       // Создаём массив для передачи данных
// char * data;
char data[RF_BUFFER_SIZE];
// String data;

// Указываем пин подключения chipSelect (CS), в соответствии со схемой сборки, модулем или шилдом;
const int chipSelect = 4;         // Пин к которому подсоединен вывод модуля CS
static const int TXPin = 2, RXPin = 3;
static const uint32_t GPSBaud = 9600;

bool SDsuccessFlag = false;

TinyGPSPlus gps;

SoftwareSerial SerialGPS(TXPin, RXPin);


void setup() {  
  Serial.begin(GPSBaud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  SerialGPS.begin(GPSBaud);
  
  radio.begin();                          // Инициируем работу nRF24L01+
  radio.setChannel(5);                    // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);     // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);   // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe (0x1234567890LL); // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)


  Serial.println("Initializing SD card...");
  sendText("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!(SDsuccessFlag = SD.begin(chipSelect))) {
    Serial.println("Card failed, or not present");
    sendText("Card failed, or not present");
    // don't do anything more:
    // while (1);
  }else {
    Serial.println("Card initialized.");  
    sendText("Card initialized.");
  }
  
}

void loop() {
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      displayInfo();
      delay(1000);
    }    
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    datalog("No GPS detected: check wiring.");
    sendText("No GPS detected: check wiring.");
    while(true);
  }
}


// отправка текста через радио модуль nRF
void sendText(char *string) {
  radio.write(string, RF_BUFFER_SIZE);
}


void datalog(String dataString) {
  if (SDsuccessFlag) {
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      
      Serial.println(dataString);
    }
    else {
      Serial.println("Error opening datalog.txt");
      sendText("Error opening datalog.txt");
    }
  }
}

void displayInfo()
{
  String response = "Location: ";

  if (gps.location.isValid())
  {
    response += String(gps.location.lat(),6);
    response += ",";
    response += String(gps.location.lng(),6);
  }
  else
  {
    response += "INVALID";
  }

  response += "  Date: ";    
  if (gps.date.isValid())
  {
    response += gps.date.month();    
    response += "/";    
    response += gps.date.day();    
    response += "/";    
    response += gps.date.year();
  }
  else
  {
    response += "INVALID";
  }

  response += "  Time: ";    
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) {
      response += "0";
    }
    response += gps.time.hour();
    response += ":";

    if (gps.time.minute() < 10) {
      response += "0";
    }
    response += gps.time.minute();
    response += ":";

    if (gps.time.second() < 10) {
      response += "0";
    }
    response += gps.time.second();
    response += ".";

    if (gps.time.centisecond() < 10) {
      response += "0";
    }
    response += gps.time.centisecond();
  }
  else
  {
    response += "INVALID";
  }

  Serial.println(response);
  datalog(response + "\r\n");   
  // sendText(response);
  
  response.toCharArray(data, RF_BUFFER_SIZE);
  
  int length = response.length();

  int quantity = (length / 32) + 1;

  for (int i = 0; i < quantity; i++) {
    radio.write(data + i*32, 32);
  }

}



