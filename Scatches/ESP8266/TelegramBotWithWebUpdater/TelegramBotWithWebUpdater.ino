
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
// void handleNewMessages(uint8_t numNewMessages);
// String webPage(String route);

// инициализация переменных
#include "main.h"

// подгрузка либ после инициализации всех переменных
#include "lib/web.h"
#include "lib/bot.h"


void setup() {
    if (debag) Serial.begin(9600);
    delay(100);

    if (debag) {
      Serial.print("\r\nConnecting Wifi: ");
      Serial.println(ssid1);
    }
    
    WiFi.begin(ssid1, password);
    
    uint8_t flag = 0;
    while (WiFi.status() != WL_CONNECTED) {
      if (flag == 15) {
        WiFi.begin(ssid2, password);
        if (debag) {
          Serial.print("\r\nConnecting Wifi: ");
          Serial.println(ssid2);
        }
      }else if (flag == 30) {
        WiFi.begin(ssid3, password);
        if (debag) {
          Serial.print("\r\nConnecting Wifi: ");
          Serial.println(ssid3);
        }
      }else if (flag == 45) {
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
    
    quantity=sizeof(pin)/sizeof(uint8_t);
    
    for (uint8_t i=0; i<quantity; i++) {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], LOW);
    }

    for (uint8_t i=0; i<quantity; i++) {
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
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);

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
