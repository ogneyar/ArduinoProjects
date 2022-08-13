
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <UniversalTelegramBot.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <FS.h>
#include <LittleFS.h>


// functions
String test();
void handleNewMessages(int numNewMessages);
String webPage(String route);


#define BOTtoken "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0" 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

ESP8266WebServer httpServer(80); // сервер на порту 80, как положенно
ESP8266HTTPUpdateServer httpUpdater;


// если необходимо выводить данные в консоль
bool debag = true; // false; // 

char host[] = "esp8266";
char ssid1[] = "MyWiFi)"; // SSID (имя) вашей WiFi сети
char ssid2[] = "WiFiSH";
char ssid3[] = "Redmi9T";
char password[] = "11111111"; // пароль wifi сети
String buttons[] = { "light" };//{ "light", "Socket" };     // имена подключенных устройств, с кириллицей НЕ РАБОТАЕТ!
uint8_t led1 = 2; // 4 - D2 (GPIO4) // 2 - D4 (GPIO2) - встроенный диод
uint8_t pin[] = { led1 };//{2, 3};                               // номер вывода, к которому подключено исполняющее устройство (реле, транзистор и т.д.)

bool protection = 0;                                    // права доступа: 0 - доступно всем пользователям, 1 - доступ по Chat ID, если оно внесено в chatID_acces.
int chatID_acces[] = {};                                // Chat ID, которым разрешен доступ, игнорируется, если protection = 0.
                                                        // Примечание: по команде /start в Telegram, если у пользователя нет прав доступа на управление устройством, бот выдаст Chat ID

String off_symbol = "❌ off "; // Индикатор выключенного состояния.
String on_symbol = "✅ on ";  // Индикатор включенного состояния.

int quantity;
int Bot_mtbs = 3000;
long Bot_lasttime;   
bool Start = false;
const int ledPin = 2;
int ledStatus = 0;
String keyboardJson = "";

IPAddress myIP;


// подгрузка либ после инициализации всех переменных
#include "lib/web.h"
#include "lib/bot.h"


void setup() {
    if (debag) Serial.begin(9600);

//    WiFi.mode(WIFI_STA);
//    WiFi.disconnect();
    delay(100);

    if (debag) {
      Serial.print("\r\nConnecting Wifi: ");
      Serial.println(ssid1);
    }
    
    WiFi.begin(ssid1, password);
    int flag = 0;
    while (WiFi.status() != WL_CONNECTED) {
      if (flag == 11) {
        //WiFi.disconnect();
        WiFi.begin(ssid2, password);
        if (debag) {
          Serial.print("\r\nConnecting Wifi: ");
          Serial.println(ssid2);
        }
      }else if (flag == 22) {
        //WiFi.disconnect();
        WiFi.begin(ssid3, password);
        if (debag) {
          Serial.print("\r\nConnecting Wifi: ");
          Serial.println(ssid3);
        }
      }else if (flag == 33) {
        flag = 0;
        WiFi.begin(ssid1, password);
        if (debag) {
          Serial.print("\r\nConnecting Wifi: ");
          Serial.println(ssid1);
        }
      }
      if (debag) Serial.print(".");
      delay(500);
      flag++;
    }
    	
	  myIP = WiFi.localIP();
    
    if (debag) {
      Serial.println("");
      Serial.println("WiFi connected");  
      Serial.print("IP address: ");
      Serial.println(myIP);
      Serial.println("");
    }    
    
    quantity=sizeof(pin)/sizeof(int);
    for (int i=0; i<quantity; i++) {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], LOW);
    }

    for (int i=0; i<quantity; i++) {
        if(i==0) keyboardJson += "[";
        keyboardJson += "[{ \"text\" : \"";
        keyboardJson += buttons[i];
        keyboardJson += "\", \"callback_data\" : \"";
        keyboardJson += buttons[i];
        keyboardJson += "\" }]";
        if(i==quantity-1){
            keyboardJson += "]";
        }else{
            keyboardJson += ",";  
        }
    }
    delay(10);
    client.setInsecure();

    MDNS.begin(host);
    
    httpUpdater.setup(&httpServer);
    httpServer.begin();
        
    MDNS.addService("http", "tcp", 80);
      
    if (debag) {
      if (!LittleFS.begin()) Serial.println("LittleFS mount failed...");
      Serial.println("HTTP server started");
      Serial.printf("Open http://%s.local/update in your browser\n", host);
      Serial.println("or");
      Serial.print("Open http://");
      Serial.print(myIP);
      Serial.println("/update in your browser\n");
    }    
    
    //---------------- routes ----------------------
    httpServer.on("/", [](){
        httpServer.send(200, "text/html", webPage("/"));
        // httpServer.send(200, "text/html", test());
    });
    
    httpServer.on("/led1", [](){
        digitalWrite(led1, !digitalRead(led1));
        httpServer.sendHeader("Location", "/", true);   // Redirect
        httpServer.send(302, "text/plane","");
    });
    //-----------------------------------------------
  
}

void loop() {
    if (millis() > Bot_lasttime + Bot_mtbs)  {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) {
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        Bot_lasttime = millis();
    }

    httpServer.handleClient();
    MDNS.update();
}


// ---------------- тест работы библиотеки LittleFS.h --------------------------------------
String test() {
    File file;    
    file = LittleFS.open("/test.txt", "w");
    file.print("Hell o!"); 
    delay(2000); 
    file.close();     
    file = LittleFS.open("test.txt", "r");    
    if(!file) { 
        if (debag) Serial.println("No Saved Data!"); 
    }     
    while(file.available()) {
        if (debag) Serial.write(file.read());
        //return file.read();
    }    
    file.close();     
    return "eee";
}
// -----------------------------------------------------------------------------------------------


