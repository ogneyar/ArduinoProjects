
// Lolin_S2_mini

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

#ifndef STASSID
#define STASSID "MyWiFi)"
#define STAPSK  "11111111"
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 15
#endif

const char* host = "webled";
const char* ssid = STASSID;
const char* password = STAPSK;

WebServer server(80);


void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    MDNS.begin(host);
    server.on("/", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", homePage());
    });
    server.on("/led_on", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", led_on());
    });
    server.on("/led_off", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", led_off());
    });
    server.begin();
    MDNS.addService("http", "tcp", 80);

    Serial.printf("Ready! Open http://%s.local in your browser\n", host);
    
    IPAddress myIP = WiFi.localIP();
    
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(myIP);
  
  } else {
    Serial.println("WiFi Failed");
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}


// ---------------- функция формирования домашней страницы --------------------------------------
String homePage()
{
  String web = "<html>"
    "<head>"
      "<meta name='viewport' content='width=device-width, initial-scale=1'>"
      "<meta charset='utf-8'>"
      "<title>webLedManagement</title>"      
      "<style>"
        "body{text-align:center;width:100%;}"
        "h1{margin:0 auto;}"
        "header{width:100%;}"
        "main{width:300px;padding:10px 30px;background-color:#ec1212;margin:0 auto;}"
        "div{margin:5px 0px;}"
        "button{color:black;padding:10px 27px;font-size:24px;color:black;}"
      "</style>"
    "</head>"
    "<body>"
      "<h1>Добро пожаловать!</h1>"
      "<br/>"
      "<header>"
        "<main>"
          "<div>"
            "<a href='led_on'>"
              "<button>Включить Led</button>"
            "</a>"    
            "<br/>"
            "<br/>"
            "<a href='led_off'>"
              "<button>Выключить Led</button>"
            "</a>"
          "</div>"
        "</main>"
      "</header>"    
    "</body>"
  "</html>";

  return(web);
}
//------------------------------------------------------------------------------------------

// ---------------- функция формирования страницы включения света --------------------------------------
String led_on()
{
  String web = "led_on: ok";
  
  digitalWrite(LED_BUILTIN, HIGH);

  return(web);
}
//------------------------------------------------------------------------------------------

// ---------------- функция формирования страницы выключения света --------------------------------------
String led_off()
{
  String web = "led_off: ok";
  
  digitalWrite(LED_BUILTIN, LOW);

  return(web);
}
//------------------------------------------------------------------------------------------


