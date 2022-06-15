
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

#define HOST "api.telegram.org"
#define PORT 443
WiFiClientSecure client;

//#define HOST "192.168.0.244"
//#define PORT 5000
//WiFiClient client;

#define TOKEN "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0"

String command = "";
String mess = "";

char ssid[] = "MyWiFi)";    //  your network SSID (name)
char pass[] = "11111111";   // your network password 

bool headerEnd = false;
bool avail = false;
long now;// = millis();
int ch_count = 0;
int longPoll = 0;
int waitForResponse = 1500;
int maxMessageLength = 1300;



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
    if (HOST == "api.telegram.org") client.setInsecure();

    Serial.println("\nStarting connection to server...");
    Serial.print("HOST: ");
    Serial.println(HOST);
    Serial.print("PORT: ");
    Serial.println(PORT);
    Serial.println();

    if (client.connect(HOST, PORT)) {

        Serial.println("Connected to server!");
        Serial.println();
        
        if (HOST == "api.telegram.org") command = "bot" + (String)TOKEN + "/getMe";
        else command = "api/test";
        
        // Make a HTTP request:
        client.print("GET /");
        client.print(command);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(HOST);
        client.println("Accept: application/json");
        client.println("User-Agent: ESP2866");
        client.println("Cache-Control: no-cache");
        client.println();

        Serial.println(command);
        
        now = millis();

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

                DynamicJsonBuffer jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject(mess);

                //closeClient();
            
                if (root.success()) {
                    if (root.containsKey("result") && root["result"]["id"]) {
                        unsigned int id = root["result"]["id"];
                        String name = root["result"]["first_name"];
                        String username = root["result"]["username"];
                        
                        Serial.println();
                        Serial.print("id = ");
                        Serial.println(id);
                        Serial.print("name = ");
                        Serial.println(name);
                        Serial.print("username = ");
                        Serial.println(username);
                        Serial.println();
                    }else {
                        // JsonObject result = root["result"];
                        String article = root["result"]["article"];
                        String url = root["result"]["url"];
                        unsigned int price = root["result"]["price"];
                        
                        Serial.println();
                        Serial.print("article = ");
                        Serial.println(article);
                        Serial.print("url = ");
                        Serial.println(url);
                        Serial.print("price = ");
                        Serial.println(price);
                        Serial.println();
                    }
                }
                break;
            }
        }

    }else {
        Serial.println();
        Serial.println("NO connecting from server.");
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
