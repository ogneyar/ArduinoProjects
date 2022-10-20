// ESP8266

/* Создаём точку доступа к WiFi и web server на нём. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESP"
#define APPSK  "11111111"
#endif

/* Устанавливаем логин и пароль. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* http://192.168.4.1 */
void handleRoot() {
  char body[] = 
    "<html>"
      "<head>"
        "<meta charset='UTF-8'>"
        "<title>ESP WiFi Server</title>"
      "</head>"
      "<body>"
        "<h1>Привет Мир!</h1>"
      "</body>"
    "</html>";
  server.send(200, "text/html", body);
  //server.send(200, "text/html", "<head><meta charset='UTF-8'><title>ESP WiFi Server</title></head><body><h1>Привет Мир!</h1></body>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Создаём точку доступа...");
  /* Можно удалить пароль, если нужно сделать доступ открытым. */
  WiFi.softAP(ssid, password);

  Serial.print("Точка доступа '");
  Serial.print(ssid);
  Serial.println("' создана.");
  
  server.on("/", handleRoot);
  server.begin();
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HTTP сервер запущен и доступен по адресу http://");
  Serial.println(myIP);
}

void loop() {
  server.handleClient();
}
