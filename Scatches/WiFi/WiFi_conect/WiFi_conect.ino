
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

char ssid[] = "MyWiFi)";                    // SSID (имя) вашей WiFi сети
char password[] = "11111111";               // пароль wifi сети


WiFiClientSecure client;


void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    
}
