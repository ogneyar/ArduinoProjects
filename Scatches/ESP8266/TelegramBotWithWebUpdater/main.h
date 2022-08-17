
#ifndef _MAIN_H_
#define _MAIN_H_


#define BOTtoken "5328519984:AAGa4HzzxvoOZF2cGdW3G6VR0eR07ieRrW0" 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

ESP8266WebServer httpServer(80); // сервер на порту 80, как положенно
ESP8266HTTPUpdateServer httpUpdater;


// если необходимо выводить данные в консоль
bool debag = true; // false; // 

char host[] = "esp8266";
char ssid1[] = "MyWiFi)"; // SSID (имя) вашей WiFi сети
char ssid2[] = "WiFiSH";
char ssid3[] = "Redmi9T";
char password[] = "11111111"; // пароль wifi сети
String buttons[] = { "light" };//{ "light", "Socket" };     // имена подключенных устройств, с кириллицей НЕ РАБОТАЕТ!
uint8_t led1 = 2; // 4 - D2 (GPIO4) // 2 - D4 (GPIO2) - встроенный диод
uint8_t pin[] = { led1 };//{2, 3};  // номер вывода, к которому подключено исполняющее устройство (реле, транзистор и т.д.)

bool protection = 0; // права доступа: 0 - доступно всем пользователям, 1 - доступ по Chat ID, если оно внесено в chatID_acces.
int chatID_acces[] = {}; // Chat ID, которым разрешен доступ, игнорируется, если protection = 0.
                         // Примечание: по команде /start, если у пользователя нет прав доступа, бот выдаст Chat ID

String off_symbol = "❌ off "; // Индикатор выключенного состояния.
String on_symbol = "✅ on ";  // Индикатор включенного состояния.

uint8_t quantity;
int Bot_mtbs = 3000;
long Bot_lasttime;   
bool Start = false;
const uint8_t ledPin = 2;
uint8_t ledStatus = 0;
String keyboardJson = "";
uint8_t numNewMessages;

IPAddress myIP;


#endif