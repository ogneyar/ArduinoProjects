
// Lolin_C3_mini, ESP32-WROOM, Lolin_S2_mini

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
#define LED_BUILTIN 1
#endif

const char* host = "esp32-webupdate";
const char* ssid = STASSID;
const char* password = STAPSK;

WebServer server(80);

void setup(void) {
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
    server.on("/updater", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", updaterPage());
    });
    server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin()) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      } else {
        Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
      }
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
  pinMode(LED_BUILTIN, OUTPUT);
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
      "<title>титл</title>"
      "<style>button{color:black;padding:10px 27px;}</style>"
    "</head>"
    "<body style='text-align:center;width:100%;'>"
      "<h1 style='text-align:center;font-family:Open sans;font-weight:700;font-size:20px;margin:0 auto;'>Добро пожаловать!</h1>"
      "<br/>"
      "<div style='text-align:center;width:100%;'>"
        "<div style='text-align:center;width:98px;color:white;padding:10px 30px;background-color:#ec1212;margin:0 20px;'>"
          "<div style='text-align:center;margin:5px 0px;'>"
            "<a href='updater'>"
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

// ---------------- функция формирования страницы обновления прошивки --------------------------------------
String updaterPage()
{
  // const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
  String web = "<form method='POST' action='/update' enctype='multipart/form-data'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Update'>"
  "</form>";

  return(web);
}
//------------------------------------------------------------------------------------------


