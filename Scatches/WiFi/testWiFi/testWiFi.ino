
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define HOST "api.telegram.org"
//#define HOST "localhost:5000"
#define SSL_PORT 443
#define PORT 80

//#define BOTtoken "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0"
String token = "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0";
String command = "bot" + token;
String mess = "";

char ssid[] = "MyWiFi)";    //  your network SSID (name)
char pass[] = "11111111";   // your network password 

bool headerEnd = false;
bool avail = false;
long now = millis();
int ch_count = 0;
int longPoll = 0;
int waitForResponse = 1500;
int maxMessageLength = 1300;

WiFiClientSecure client;


void setup() {
    Serial.begin(9600);
  
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    printWifiStatus();

    delay(10);
    client.setInsecure();

    Serial.println("\nStarting connection to server...");

    if (client.connect(HOST, SSL_PORT)) {

        Serial.println("connected to server");

        String command = "bot" + token + "/getMe";
        
        // Make a HTTP request:
        client.print("GET /");
        client.print(command);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(HOST);
        client.println("Accept: application/json");
        client.println("Cache-Control: no-cache");
        client.println();

        Serial.println(command);
        

        while (millis() - now < longPoll * 1000 + waitForResponse) {

            while (client.available()) {
                char c = client.read();
                // Serial.write(c);

                if (!headerEnd && c=='{')  headerEnd = true; 
            
                if (headerEnd){
                    if (ch_count < maxMessageLength) {
                        mess = mess + c;
                        ch_count++;
                    }
                }
                avail = true;
            }
            
            if (avail) {
                Serial.println();
                Serial.println(mess);
                Serial.println();

                DynamicJsonBuffer jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject(mess);

                closeClient();

            
                if (root.success()) {
                    if (root.containsKey("result")) {
                    unsigned int id = root["result"]["id"];
                    String name = root["result"]["first_name"];
                    String username = root["result"]["username"];
                    
                        Serial.print("\nid = ");
                        Serial.println(id);
                        Serial.print("\nname = ");
                        Serial.println(name);
                        Serial.print("\nusername = ");
                        Serial.println(username);
                        Serial.println();
                        
                    }
                    
                }
                
                break;
            }
        }

    }

    // if the server's disconnected, stop the client:
    // if (!client.connected()) {
    //     Serial.println();
    //     Serial.println("disconnecting from server.");
    //     client.stop();

    //     // do nothing forevermore:
    //     while (true);
    // }
    
}

void loop() {
}


void printWifiStatus() {
    Serial.println();
    Serial.println("WiFi connected");
    
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // print the received signal strength:
    Serial.print("signal strength (RSSI):");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}


void closeClient() {
  if (client.connected()) {
      Serial.println("Closing client");
      client.stop();
  }
}
