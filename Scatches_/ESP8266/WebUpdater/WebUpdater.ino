/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef STASSID
#define STASSID "Redmi9T"
#define STAPSK  "11111111"
#endif

const char* host = "esp8266-webupdate";
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

byte LED1 = 2;

void setup(void) {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);

  httpUpdater.setup(&httpServer);
  httpServer.begin();

  MDNS.addService("http", "tcp", 80);
  
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
  
  IPAddress myIP = WiFi.localIP();
  
  Serial.print("IP address: ");
  Serial.println(myIP);

  pinMode(LED1, OUTPUT);
}

void loop(void) {
  httpServer.handleClient();
  MDNS.update();
  
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(50);
}