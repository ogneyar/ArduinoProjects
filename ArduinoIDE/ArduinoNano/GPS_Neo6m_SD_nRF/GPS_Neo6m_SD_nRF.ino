
// Nano

#include <SPI.h>            // Подключаем библиотеку для работы с SPI устройствами
#include <SD.h>             // Подключаем библиотеку для работы с SD картой
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <nRF24L01.h>       // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>           // Подключаем библиотеку для работы с nRF24L01+

// для Nrf-Nano: CE (Chip Enable) - D10, CS/CSN (Chip Select) - D9
RF24 radio(10, 9); // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
// char data[] = "Hello, bro!";       // Создаём массив для передачи данных
char * data;
// char data[128];
// String data;

// Указываем пин подключения chipSelect (CS), в соответствии со схемой сборки, модулем или шилдом;
const int chipSelect = 4;         // Пин к которому подсоединен вывод модуля CS
static const int TXPin = 2, RXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

SoftwareSerial SerialGPS(TXPin, RXPin);


void setup() {  
  Serial.begin(GPSBaud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  SerialGPS.begin(GPSBaud);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");  
  
  radio.begin();                          // Инициируем работу nRF24L01+
  radio.setChannel(5);                    // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);     // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);   // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe (0x1234567890LL); // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
}

void loop() {
  while (SerialGPS.available() > 0)
    if (gps.encode(SerialGPS.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    datalog("No GPS detected: check wiring.");
    while(true);
  }
  
  sendText("EEE good job bro!");
  delay(1000);
}


// отправка текста через радио модуль nRF
void sendText(char *string) {
  radio.write(string, 128);
  // radio.write(&data, sizeof(data)); // отправляем данные из массива data указывая сколько байт массива мы хотим отправить
}


void datalog(String dataString) {
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}

void displayInfo()
{
  String response = "";
  
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);

    // datalog("Location: " + String(gps.location.lat(),6) + "," + String(gps.location.lng(),6));
    response += "Location: " + String(gps.location.lat(),6) + "," + String(gps.location.lng(),6);
  }
  else
  {
    Serial.print(F("INVALID"));
    // datalog("Location: INVALID");
    response += "Location: INVALID";
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    
    // datalog(" - Date/Time: " + String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year()) + " ");
    
    response += "  Date/Time: " + String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year()) + " ";
  }
  else
  {
    Serial.print(F("INVALID"));
    // datalog(" - Date/Time: INVALID ");
    response += "  Date/Time: INVALID ";
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) {
      Serial.print(F("0"));
      // datalog("0");
      response += "0";
    }
    Serial.print(gps.time.hour());

    // datalog(String(gps.time.hour()));
    response += String(gps.time.hour());

    Serial.print(F(":"));
    // datalog(":");
    response += ":";

    if (gps.time.minute() < 10) {
      Serial.print(F("0"));
      // datalog("0");
      response += "0";
    }
    Serial.print(gps.time.minute());

    // datalog(String(gps.time.minute()));
    response += String(gps.time.minute());

    Serial.print(F(":"));
    // datalog(":");
    response += ":";

    if (gps.time.second() < 10) {
      Serial.print(F("0"));
      // datalog("0");
      response += "0";
    }
    Serial.print(gps.time.second());

    // datalog(String(gps.time.second()));
    response += String(gps.time.second());

    Serial.print(F("."));
    // datalog(".");
    response += ".";

    if (gps.time.centisecond() < 10) {
      Serial.print(F("0"));
      // datalog("0");
      response += "0";
    }
    Serial.print(gps.time.centisecond());

    // datalog(String(gps.time.centisecond()));
    response += String(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
    // datalog("INVALID");
    response += "INVALID";
  }

  Serial.println();
  datalog(response + "\r\n");
}



