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
  server.send(200, "text/html", "<h1>Привет Мир!</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  /* Можно удалить пароль, если нужно сделать доступ открытым. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started on http://192.168.4.1");
}

void loop() {
  server.handleClient();
}
