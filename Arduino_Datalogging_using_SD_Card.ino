/*
 * Arduino Datalogging using SD Card
 *
 * 
 * by Niyas Thalappil
 * 
 * www.youtube.com/c/NiyasThalappil
 * NiyazThalappil@gmail.com
 *
 */

#include "DHT.h"                        //Library for DHT sensor
#include <SPI.h>                        //Serial library for SD card shield
#include <SD.h>                         //SD card library
#define DHTPIN 8                        //DHT sensor on pin Digital 8
#define DHTTYPE DHT22                   //DHT type (11,21,22)
DHT dht(DHTPIN, DHTTYPE);               //create instance of DHT called dht

const int chipSelect = 4;               //chip select on digital 4 for SD card shield

void setup() {

  Serial.begin(9600);                 
  while (!Serial) {
    ;                                  
  }
  Serial.print("Initializing SD card...");

                                       
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");

    dht.begin();                        
}

void loop() {
    delay(2000);                        
    float h = dht.readHumidity();      
    float f = dht.readTemperature(true);
    
                                        /
  String dataString = "";

  dataString += String(h);
  dataString += ",";
  dataString += String(f);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

                                       
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}


