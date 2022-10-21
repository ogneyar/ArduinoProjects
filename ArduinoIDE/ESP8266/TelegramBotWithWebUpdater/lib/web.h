
#ifndef _WEB_H_
#define _WEB_H_

// --------------- список функций -------------------
// String webPage(String route);
// --------------------------------------------------


// ---------------- функция формирования локальной страницы --------------------------------------
String webPage(String route) {
    
    // minify html files - https://www.willpeavy.com/tools/minifier/
    String web = "<!DOCTYPE html><html lang='ru'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>ESP WiFi Server</title> <style>*{margin: 0; padding: 0; box-sizing: border-box;}html{font-family: Open sans; background-color: #696969;}body, .handle, .box{text-align: center; width: 100%; display: flex; flex-direction: column;}.handle{background-color: #8dec12; padding: 20px;}.handle_title{font-weight: 700; font-size: 24px; color:rgb(238, 238, 238); background-color: #ecc412; padding: 20px 30px;}.box_on_off{align-items: center;}.box_led1, .box_update{padding: 20px 30px; align-items: center;}.box_led1{background-color: #1278ec;}.box_update{background-color: grey;}.button{border-radius: 5px; color: white;}.button_led1{width: 150px; padding: 10px 30px; border: 1px solid grey; background-color: lightgrey;}.button_update{width: 120px; padding: 5px 20px; background-color: lightgrey;}a{cursor: pointer; text-decoration: none;}a:hover{opacity:0,7;}.on{background-color: #d12525; padding: 20px; border-radius: 5px;}.off{background-color: lightgrey; padding: 20px; border-radius: 5px;}</style></head><body> <div class='handle'> <h1 class='handle_title'>Управление светом онлайн</h1> </div><hr/><br/> <div class='box box_led1'> <div class='box_on_off ${led1}'> <a href='led1'> <div class='button button_led1'>Включатель №1</div></a> </div></div><br/> <hr/><br/> <div class='box box_update'> <a href='update'> <div class='button button_update'>Обновить прошивку</div></a> </div><script></script></body></html>";
  
  
    if (digitalRead(led1) == 1) {
        web.replace("${led1}", "on"); 
    }else {
        web.replace("${led1}", "off"); 
    }

    return web;

}
//------------------------------------------------------------------------------------------

#endif