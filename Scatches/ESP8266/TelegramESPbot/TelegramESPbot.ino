
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <UniversalTelegramBot.h>
#include <ESP8266WebServer.h>

#define BOTtoken "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0" 

ESP8266WebServer server(80); // сервер на порту 80, как положенно

// если необходимо выводить данные в консоль
bool debag = false;

char ssid1[] = "MyWiFi)"; // SSID (имя) вашей WiFi сети
char ssid2[] = "WiFiSH";
char password[] = "11111111"; // пароль wifi сети
String buttons[] = { "light" };//{ "light", "Socket" };     // имена подключенных устройств, с кириллицей НЕ РАБОТАЕТ!
byte led1 = 4; // 4 - D2 (GPIO4) // 2 - D4 (GPIO2) 
int pin[] = { led1 };//{2, 3};                               // номер вывода, к которому подключено исполняющее устройство (реле, транзистор и т.д.)

bool protection = 0;                                    // права доступа: 0 - доступно всем пользователям, 1 - доступ по Chat ID, если оно внесено в chatID_acces.
int chatID_acces[] = {};                                // Chat ID, которым разрешен доступ, игнорируется, если protection = 0.
                                                        // Примечание: по команде /start в Telegram, если у пользователя нет прав доступа на управление устройством, бот выдаст Chat ID

String off_symbol = "❌ off "; // Индикатор выключенного состояния.
String on_symbol = "✅ on ";  // Индикатор включенного состояния.


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
int Bot_mtbs = 500;
long Bot_lasttime;   
bool Start = false;
const int ledPin = 2;
int ledStatus = 0;
String keyboardJson = "";

IPAddress myIP;


void setup() {
    if (debag) Serial.begin(9600);

//    WiFi.mode(WIFI_STA);
//    WiFi.disconnect();
    delay(100);

    if (debag) {
      Serial.print("Connecting Wifi: ");
      Serial.println(ssid1);
    }
    
    WiFi.begin(ssid1, password);
    int flag = 0;
    while (WiFi.status() != WL_CONNECTED) {
      if (flag == 11) {
        //WiFi.disconnect();
        WiFi.begin(ssid2, password);
      }
      if (debag) Serial.print(".");
      delay(500);
      flag++;
    }
	
	  myIP = WiFi.localIP();
    
    if (debag) {
      Serial.println("");
      Serial.println("WiFi connected");  
      Serial.print("IP address: ");
      Serial.println(myIP);
    }    
    
    quantity=sizeof(pin)/sizeof(int);
    for (int i=0; i<quantity; i++) {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], LOW);
    }

    for (int i=0; i<quantity; i++) {
        if(i==0) keyboardJson += "[";
        keyboardJson += "[{ \"text\" : \"";
        keyboardJson += buttons[i];
        keyboardJson += "\", \"callback_data\" : \"";
        keyboardJson += buttons[i];
        keyboardJson += "\" }]";
        if(i==quantity-1){
            keyboardJson += "]";
        }else{
            keyboardJson += ",";  
        }
    }
    delay(10);
    client.setInsecure();


    server.begin();
    
    if (debag) Serial.println("HTTP server started");
    
    server.on("/", [](){
      server.send(200, "text/html", webPage("/"));
    });
    
    //------------block 1-----------------------------------
    server.on("/led1", [](){
      digitalWrite(led1, !digitalRead(led1));
      server.send(200, "text/html", webPage("/led1"));
      delay(100);
    });
    
}

void loop() {
    if (millis() > Bot_lasttime + Bot_mtbs)  {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) {
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        Bot_lasttime = millis();
    }

    server.handleClient();
}

// ---------------- функция формирования ответа бота --------------------------------
void handleNewMessages(int numNewMessages) {
    if (debag) {
      Serial.println("New message");
      Serial.println("His number: " + String(numNewMessages));
    }

    for (int i=0; i<numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        String m_id = String(bot.messages[i].message_id);
        if (bot.messages[i].type == "callback_query") {
            String statusMessage;
            for (int i1=0; i1<quantity; i1++) {
                if (bot.messages[i].text == buttons[i1]) {
                    digitalWrite (pin[i1], !digitalRead(pin[i1]));
                }
                digitalRead(pin[i1])? statusMessage += on_symbol : statusMessage += off_symbol;
                statusMessage += buttons[i1]; 
                statusMessage += '\n';
            }
            bot.deleteMessage(bot.messages[i].chat_id, bot.messages[i].message_id);
            bot.sendMessageWithInlineKeyboard(bot.messages[i].chat_id, statusMessage, "", keyboardJson);
        
        } else {
            String text = bot.messages[i].text;
            Serial.println(m_id);
            String from_name = bot.messages[i].from_name;
            if (from_name == "") from_name = "Guest";
            int i2=0;
            do{
                if (!protection || String(chatID_acces[i2]) == chat_id) {
                    if (text == "/control") {
                        String statusMessage;
                        for (int i=0; i<quantity; i++) {
                            digitalRead(pin[i])?statusMessage+=on_symbol:statusMessage+=off_symbol;
                            statusMessage+=buttons[i];  
                            statusMessage+='\n';
                        }
                        bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
                    }

                    if (text == "/myip") {
                        String message = "ESP8266 IP: " + String(myIP[0]) + "." + String(myIP[1]) + "." + String(myIP[2]) + "." + String(myIP[3]) + "\n\n";
                        bot.sendMessage(chat_id, message);
                    }
            
                    if (text == "/start") {
                        String welcome = "Приветствую " + from_name + ".\n";
                        welcome += "Это умный выключатель на микроконтроллере ESP8266, управляемый через Telegram.\n\n";
                        welcome += "/control : перейти к управлению.\n\n";
                        welcome += "/myip : узнать локальный IP модуля ESP8266.\n\n";
                        String keyboardStart = "[[{ \"text\" : \"Ссыль на сайт Хуторянина.\", \"url\" : \"https://hutoryanin.ru\" }]]";
                        bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
                    }
                    break;
                }else{
                    if (i2==((sizeof(chatID_acces)/sizeof(int))-1)&&text == "/start"||(sizeof(chatID_acces)/sizeof(int))==0&&text == "/start") {
                        bot.sendMessage(chat_id, "No access, Chat ID: "+chat_id, "");
                    }
                }

                i2++;
            }while (i2<(sizeof(chatID_acces)/sizeof(int)));
        }
    }
}
//------------------------------------------------------------------------------------------


// ---------------- функция формирования локальной страницы --------------------------------------
String webPage(String route)
{
  String web; 
  web += "<head><meta name='viewport' content='width=device-width, initial-scale=1'> <meta charset='utf-8'><title>титл</title><style>button{color:black;padding: 10px 27px;}</style></head>";
  
  // -----------заголовок-----------------
  web += "<div style='text-align: center;width: 100%;'><h1 style'text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;margin: 0 auto;'>лед онлайн</h1></div>";
  //-------------------------------------

  web += "<div>";
  //-------------------------------------
  web += "<br>";
  
  //--------------block 1------------------
  if (digitalRead(led1) == 1) {
    web += "<div style='text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;'><div style='text-align: center;margin: 5px 0px;cursor:pointer;'><a href='led1'><button>LED1</button></a></div></div>";
  }else  {
    web += "<div style='text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: grey;margin: 0 auto;'><div style='text-align: center;margin: 5px 0px;cursor:pointer;'><a href='led1'><button>LED1</button></a></div></div>";
  }
  web += "<br>";
  //----------------------------------------
  
  // ----------reload---------------------------
  web += "<div style='text-align:center;margin-top: 20px;'><a href='/'><button style='width:158px;'>REFRESH</button></a></div>";
  // -----------------------------------------
    
  web += "</div>";

//  if (route != "/") web += "<script>window.location.href = '/'</script>";
  if (route != "/") web += "<script>window.history.pushState({}, null, '/')</script>";
  
  return(web);
}
//------------------------------------------------------------------------------------------
