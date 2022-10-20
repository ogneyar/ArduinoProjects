
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef STASSID
#define STASSID "Redmi9T"
#define STAPSK  "11111111"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

byte LED1 = 2;

void setup(void) {

  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  httpUpdater.setup(&httpServer);
  httpServer.begin();


  httpServer.on("/", [](){
    httpServer.send(200, "text/html", webPage());
  });
  
  IPAddress myIP = WiFi.localIP();
  
//  Serial.print("IP address: ");
//  Serial.println(myIP);
    
  Serial.print("HTTPUpdateServer ready! Open http://");
  Serial.print(myIP);
  Serial.println("/update in your browser\n");
  
  pinMode(LED1, OUTPUT);
}

void loop(void) {
  httpServer.handleClient();

  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(50);
}


// ---------------- функция формирования страницы --------------------------------------
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
//------------------------------------------------------------------------------------------
