
// NodeMCU

//---------------------------------------------- clock
#include <Arduino.h>
#include <U8g2lib.h>
#include <uRTCLib.h>
#include <EEPROM.h>
#include "buildTime.h"

U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE); // D1 and D2 on ESP8266
uRTCLib rtc(0x68);

int address = 0;   // адрес ключа
uint8_t key = 135; // ключ для проверки первого запуска  
uint32_t timeMillis = 0;
uint32_t current = 0;
uint16_t target = 1000;
uint8_t dots = 1;
//----------------------------------------------

//---------------------------------------------- web updater
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef STASSID
#define STASSID "MyWiFi)"
#define STASSID2 "WiFiSH)"
#define STAPSK  "11111111"
#endif

const char* host = "webupdater";
const char* ssid = STASSID;
const char* ssid2 = STASSID2;
const char* password = STAPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
//----------------------------------------------

// byte LED1 = 2;


void setup(void) {
  //---------------------------------------------- clock
  URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266  
  
  EEPROM.begin(512);  
  if (EEPROM.read(address) != key) { // значение ключа
    EEPROM.write(address, key);
    EEPROM.commit();
    // установить время == времени компиляции
    rtc.set(BUILD_SEC, BUILD_MIN+1, BUILD_HOUR, 6, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);  // 6 - dayOfWeek
  }
  
  u8g2.begin();
  u8g2.enableUTF8Print();
  //----------------------------------------------
  
  //---------------------------------------------- web updater
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  delay(1000);
  
  // while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  //   WiFi.begin(ssid, password);
  //   Serial.println("WiFi failed, retrying.");
  // }
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(ssid2, password);
    Serial.println("WiFi failed, retrying.");
    delay(1000);
  }

  MDNS.begin(host);

  httpUpdater.setup(&httpServer);
  httpServer.begin();
  
  httpServer.on("/", [](){
    httpServer.send(200, "text/html", webPage());
  });

  MDNS.addService("http", "tcp", 80);
  
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
  
  IPAddress myIP = WiFi.localIP();
  
  Serial.print("IP address: ");
  Serial.println(myIP);
  //----------------------------------------------

  // pinMode(LED1, OUTPUT);
}

void loop(void) {  
  //---------------------------------------------- clock
  timeMillis = millis();
  if (timeMillis - current > target) {    
    current = timeMillis;    
    dots = !dots;
    printTime(dots);
  }
  //----------------------------------------------
  
  //---------------------------------------------- web updater
  httpServer.handleClient();
  MDNS.update();
  //----------------------------------------------
  
  // digitalWrite(LED1, HIGH);
  // delay(500);
  // digitalWrite(LED1, LOW);
  // delay(500);
}

//---------------------------------------------- web updater
// функция формирования страницы
String webPage()
{
  String web = "<html>"
    "<head>"
      "<meta name='viewport' content='width=device-width, initial-scale=1'>"
      "<meta charset='utf-8'>"
      "<title>титл</title>"
      "<style>button{color:black;padding:10px 27px;}</style>"
    "</head>"
    "<body style='text-align:center;width:100%;'>"
      "<h1 style='text-align:center;font-family:Open sans;font-weight:700;font-size:20px;margin:0 auto;'>Добро пожаловать!</h1>"
      "<br/>"
      "<div style='text-align:center;width:100%;'>"
        "<div style='text-align:center;width:98px;color:white;padding:10px 30px;background-color:#ec1212;margin:0 20px;'>"
          "<div style='text-align:center;margin:5px 0px;'>"
            "<a href='update'>"
              "<button>Обновить прошивку</button>"
            "</a>"
          "</div>"
        "</div>"
      "</div>"        
//      "<br/>"
    "</body>"
  "</html>";

  return(web);
}
//----------------------------------------------

//---------------------------------------------- clock
// вывод времени на дисплей
void printTime(uint8_t _dots) {
  rtc.refresh();
  
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  u8g2.setCursor(4, 12);
  u8g2.print("Часы Sвенирады!");  

  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  u8g2.setCursor(2, 63);
  uint8_t hour = rtc.hour();
  if (hour < 10) u8g2.print(0);
  u8g2.print(hour);    
  uint8_t minute = rtc.minute();
  if (minute < 10) u8g2.print(0);
  u8g2.print(minute);  
  
  u8g2.setFont(u8g2_font_crox5tb_tn);
  u8g2.setCursor(59, 50);  
  if (_dots) u8g2.print(".");
  else u8g2.print(" ");  
  u8g2.setCursor(59, 38);
  if (_dots) u8g2.print(".");
  else u8g2.print(" ");    
  
  u8g2.sendBuffer();
}
//----------------------------------------------

