/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// -------- название и пароль для точки доступа --------------
const char *ssid = "ledpanel";
const char *password = "1234567890";
//---------------------------------------------------------

ESP8266WebServer server(80); // сервер на порту 80, как положенно

// -----------пины для светодиодов------------
int led1 = 2;
int led2 = 0;
//--------------------------------------------

void setup(void){
  //---------------------------пины светодиодов на выход --------------------------
  pinMode(led1, OUTPUT);
  digitalWrite(led1, 0);

  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  //------------------------------------------------------------------------------

  // ---------------------запуск сервера и отчеты в порт------------------------
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
  //------------------------------------------------------------------------


    server.on("/", [](){
    server.send(200, "text/html", webPage());
    });
    
    //------------block 1-----------------------------------
    server.on("/led1", [](){
    digitalWrite(led1, !digitalRead(led1));
    server.send(200, "text/html", webPage());
    delay(100);
    });
    
    //-------------block 2-----------------------------------
    server.on("/led2", [](){
    digitalWrite(led2, !digitalRead(led2));
    server.send(200, "text/html", webPage());
    delay(100);    
    });


}


void loop(void){
  server.handleClient();
} 

// ---------------- функция формирования страницы --------------------------------------
String webPage()
{
  String web; 
  web += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <meta charset=\"utf-8\"><title>титл</title><style>button{color:black;padding: 10px 27px;}</style></head>";
  
  // -----------заголовок-----------------
  web += "<h1 style\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;\">лед онлайн</h1><div>";
  web += "<br>";
  //-------------------------------------
  
  //--------------block 1------------------
  if (digitalRead(led1) == 1)
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;\"><div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"led1\"><button>LED1</button></a></div></div>";
  }
  else 
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: grey;margin: 0 auto;\"><div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"led1\"><button>LED1</button></a></div></div>";
  }
  //----------------------------------------
  
  web += "<br>";
  //-------------------------block 2-----------------------
  if (digitalRead(led2) == 1)
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;\"><div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"led2\"><button>LED2</button></a></div></div>";
  }
  else 
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: grey;margin: 0 auto;\"><div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"led2\"><button>LED2</button></a></div></div>";
  }
  // ------------------------------------

  
  web += "<br>";
  
  // ----------reload---------------------------
  web += "<div style=\"text-align:center;margin-top: 20px;\"><a href=\"/\"><button style=\"width:158px;\">REFRESH</button></a></div>";
  // -----------------------------------------
  
  
  web += "</div>";
  return(web);
}
//------------------------------------------------------------------------------------------
