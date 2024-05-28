//code based on this tutorial https://www.youtube.com/watch?v=YN42n9dQSv8 

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEAddress.h>
#include <Ticker.h>
#include <SSD1306Wire.h>
SSD1306Wire bildschirm(0x3c, 4, 15);
bool lost;
 
String Adresse = ""; // Bluetooth Adresse die zu Anwesenheitserkennung überwacht wird
const int buzzer = 21;
const int Verzoegerung = 15; 
int VerzoegerungZaeler = 0;
int scanTime = 30;

Ticker Tic;
static BLEAddress *pServerAddress;
BLEScan* pBLEScan ;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks{
    void onResult(BLEAdvertisedDevice advertisedDevice){
      Serial.print(advertisedDevice.getAddress().toString().c_str());
      
      if (advertisedDevice.getAddress().equals(*pServerAddress)){
        Serial.println("      <- gesuchte adresse");
        lost = false;
        advertisedDevice.getScan()->stop();
      }
      else{
        Serial.println("");
      }
    }
};
 
void SekundenTic(){
VerzoegerungZaeler++;
if (VerzoegerungZaeler >= Verzoegerung){
  lost = true;
}}

void setup(){
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  pServerAddress = new BLEAddress(Adresse.c_str());
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  Tic.attach( 1,SekundenTic);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  bildschirm.init();
  bildschirm.drawString(0, 0, "find my v1.3");
  bildschirm.display();
}
 
void loop(){
  pBLEScan->start(scanTime);
  delay(2000);
  if (!lost){
    bildschirm.clear();
    bildschirm.drawString(0, 0, String(advertisedDevice.getAddress().toString().c_str()));
    bildschirm.drawString(0, 20, "gesuchtes device gefunden");
    bildschirm.display();
    VerzoegerungZaeler = 0; 
  }
  else{
    bildschirm.clear();
    bildschirm.drawString(0, 0, "dieser tracker wurde");
    bildschirm.drawString(0, 10, "gerade verloren!");
    bildschirm.display();
  }
  while (lost){
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}