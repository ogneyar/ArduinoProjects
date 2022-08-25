
#include <SPI.h>    // Подключаем библиотеку для работы с SPI устройствами
#include <SD.h>     // Подключаем библиотеку для работы с SD картой

// Определяем объекты, используемые функциями библиотеки SD:
Sd2Card card;           // Для информации о карте
SdVolume volume;        // Для информации о типе и размере файловой системы
SdFile root;            // Для информации о файлах и каталогах

// Указываем пин подключения chipSelect (CS), в соответствии со схемой сборки, модулем или шилдом;
const int chipSelect = 4;         // Пин к которому подсоединен вывод модуля CS

// Начало функции обработки кириллических символов при выводе на монитор серийного порта
String utf8rus(String source)     // Функция для конвертации русских символов из двубайтовой кодировки в однобайтовую
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
 
    if (n >= 0xBF){
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m); 
  }
  return target;
}
// Конец функции обработки кириллических симоволов

void setup() {
  Serial.begin(9600);         // Инициализируем вывод данных на монитор серийного порта
  SD.begin(chipSelect);       // Инициализируем библиотеку для работы с SD-картой, указав пин подключения вывода CS

  // Далее будем использовать код, содержащий функции, приведенные в библиотеке

  // Сначала просто проверим работает ли карта
  Serial.println(utf8rus("Инициализация SD карты..."));
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {   // Если не удалось инициализировать обмен данными с SD-картой
    Serial.println(utf8rus("Инициализация провалена."));
/*
  При появлении этой ошибки необходимо проверить:
    1. Вставлена ли карта
    2. Правильно ли собрана схема
    3. Указали ли вы в скетче chipSelect в соответсвии с вашим шилдом или модулем
*/
    return;                                       // Завершаем выполнение программы
  } else {
    delay(1000);                                  // Эта и остальные задержки в скетче для красоты. Их можно убирать. В начальном варианте здесь выводилось сообщение о том, что инициализация прошла успешно и карта установлена правильно.
  }

  // Выводим тип карты
  Serial.print(utf8rus("\nТип карты: "));
  switch (card.type()) { 
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println(utf8rus("Неизвестен"));
  }

  // Теперь попытаемся открыть раздел 'volume'/'partition' файловой системы - это должна быть система FAT16 или FAT32
  if (!volume.init(card)) {
    Serial.println(utf8rus("Невозможно найти FAT16/FAT32 раздел.")); // При появлении этой ошибки необходимо убедиться, что карта отформатирована
    return;                                                          // Завершаем выполнение программы
  }


  // Выводим тип FAT файловой системы и ее размер
  uint32_t volumesize;                                  // Объявляем переменную в которой будем хранить информацию о размерности карты
  
  Serial.print(utf8rus("Тип файловой системы: FAT"));
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();               // Узнаем сколько блоков содержит кластер (кластеры представляют собой наборы блоков)
  volumesize *= volume.clusterCount();                  // Узнаем общее кол-во кластеров
  volumesize *= 512;                                    // Узнаем размер карты в байтах (1 блок на SD-карте всегда занимает 512 байт)
  volumesize /= 1024;                                   // Переводим в килобайты (в одном килобайте 1024 байта)
  volumesize /= 1024;                                   // Переводим в мегабайты (в одном мегабайте 1024 килобайта)
  Serial.print(utf8rus("Размер карты: "));
  Serial.print(volumesize);
  Serial.println(" Mb");


  Serial.println(utf8rus("Файлы на карте: "));
  root.openRoot(volume);                                              // Активируем корневой каталог раздела
  root.ls(LS_R | LS_DATE | LS_SIZE);                                  // Выводим список всех файлов, находящихся на карте, а также дату их создания/изменения и размер

  Serial.println("");                                                 // Перевод строки

  String filename = "borodino.txt";                                   // Определяем имя файла с которым будем работать

  File dataFile = SD.open(filename);                                  // Открываем файл и связываем его с указателем dataFile

  delay (2000);
  if (dataFile) {                                                     // Если файл доступен
    Serial.println(utf8rus("Вывожу содержимое файла: ") + filename + "\n");
    delay (2000);
    while (dataFile.available()) {                                    //  Пока не достигли конца файла
      Serial.write(dataFile.read());                                  //    выводим по одному считанному из файла символу
      delay(20);                                                      //    делаем небольшую задержку, имитируя набор текста
    }
    dataFile.close();                                                 //  Закрываем файл
  }
  else {                                                              // иначе (если файл не доступен)
    Serial.println(utf8rus("Ошибка открытия файла ") + filename);     //  выводим текст ошибки
  }
}

void loop() {

}
