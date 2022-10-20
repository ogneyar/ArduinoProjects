
#ifndef _BOT_H_
#define _BOT_H_

// --------------- список функций -------------------
// void handleNewMessages(uint8_t numNewMessages);
// --------------------------------------------------

// ---------------- функция формирования ответа бота --------------------------------
void handleNewMessages(uint8_t numNewMessages) {//, String * buttons, uint8_t * pin, bool debag) {
    if (debag) {
      Serial.println("New message");
      Serial.print("His number: ");// + String(numNewMessages));
    }

    for (uint8_t i=0; i<numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        String m_id = String(bot.messages[i].message_id);
        if (bot.messages[i].type == "callback_query") {
            String statusMessage;
            for (uint8_t i1=0; i1<quantity; i1++) {
                if (bot.messages[i].text == buttons[i1]) {
                    digitalWrite (pin[i1], !digitalRead(pin[i1]));
                }
                digitalRead(pin[i1]) ? statusMessage += on_symbol : statusMessage += off_symbol;
                statusMessage += buttons[i1]; 
                statusMessage += '\n';
            }
            bot.deleteMessage(chat_id, m_id);
            bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
        
        } else {
            String text = bot.messages[i].text;
            if (debag) Serial.println(m_id);
            String from_name = bot.messages[i].from_name;
            if (from_name == "") from_name = "Guest";
            uint8_t i2=0;
            do{
                if (!protection || String(chatID_acces[i2]) == chat_id) {
                    if (text == "/control") {
                        String statusMessage;
                        for (uint8_t i=0; i<quantity; i++) {
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

#endif