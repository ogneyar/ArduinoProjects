
// Arduino Nano 168p

#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 14;

void setup() {
  Serial.begin(9600);
  while (!Serial); 

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("failed");
    while (1);
  }else {
  Serial.println("norm");
  }

//  Serial.println();
//  Serial.print("Card type:         ");
//  switch (card.type()) {
//    case SD_CARD_TYPE_SD1:
//      Serial.println("SD1");
//      break;
//    case SD_CARD_TYPE_SD2:
//      Serial.println("SD2");
//      break;
//    case SD_CARD_TYPE_SDHC:
//      Serial.println("SDHC");
//      break;
//    default:
//      Serial.println("Unknown");
//  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16");
    while (1);
  }

//  Serial.print("Clusters:          ");
//  Serial.println(volume.clusterCount());
//  Serial.print("Blocks x Cluster:  ");
//  Serial.println(volume.blocksPerCluster());
//
//  Serial.print("Total Blocks:      ");
//  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
//  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
//  Serial.print("Volume type is:    FAT");
//  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
//  Serial.print("Volume size (Kb):  ");
//  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void loop(void) {
}
