
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0" 

char ssid[] = "MyWiFi)";                    // SSID (имя) вашей WiFi сети
char password[] = "11111111";               // пароль wifi сети
String buttons[] = {"light", "Socket"};     // имена подключенных устройств, с кириллицей НЕ РАБОТАЕТ!
int pin[] = {2, 3};                         // номер вывода, к которому подключено исполняющее устройство (реле, транзистор и т.д.)

bool protection = 1;                        // права доступа: 0 - доступно всем пользователям, 1 - доступ по Chat ID, если оно внесено в chatID_acces.
int chatID_acces[] = {1038937592};          // Chat ID, которым разрешен доступ, игнорируется, если protection = 0.
                                            // Примечание: по команде /start в Telegram, если у пользователя нет прав доступа на управление устройством, бот выдаст Chat ID

String on_symbol="❌ "; // Индикатор выключенного состояния.
String off_symbol="✅ ";  // Индикатор включенного состояния.

//Дальше ничего интересного, но если хотите, можете посмотреть.

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
int Bot_mtbs = 500;
long Bot_lasttime;   
bool Start = false;
const int ledPin = 2;
int ledStatus = 0;
String keyboardJson = "";


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
    
    quantity=sizeof(pin)/sizeof(int);
    for (int i=0; i<quantity; i++) {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], HIGH);
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
}

// function handleNewMessages
void handleNewMessages(int numNewMessages) {
    Serial.println("New message");
    Serial.println("His number: " + String(numNewMessages));

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

                    if (text == "/start") {
                        String welcome = "Приветствую " + from_name + ".\n";
                        welcome += "Это умный выключатель на микроконтроллере ESP8266, управляемый через Telegram.\n\n";
                        welcome += "/control : перейти к управлению.\n";
                        String keyboardStart = "[[{ \"text\" : \"Ссыль на сайт\", \"url\" : \"https://hutoryanin.ru\" }]]";
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