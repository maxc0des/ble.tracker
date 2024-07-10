#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEAddress.h>
 
String Adresse = "03:28:2f:5c:00:32";                            // Bluetooth Adresse die zu Anwesenheitserkennung überwacht wird
#define lautsprecher 19
#define button 23
int timeThreashold = 20000; //in ms
int signalThreashold = - 100; // in rssi
long lastTimefound; // in ms

static BLEAddress *pServerAddress;
BLEScan* pBLEScan ;

 
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice){
      Serial.print(advertisedDevice.getAddress().toString().c_str()),//gefundene Adresse anzeigen
      Serial.print("  |  ");
      Serial.print(advertisedDevice.getRSSI());//Signalstärke anzeigen
      if (advertisedDevice.getAddress().equals(*pServerAddress)){//prüfen, ob die Adresse der gesuchten entspricht
        if (advertisedDevice.getRSSI()>signalThreashold) {//prüfen, ob Signalstärke inerhalb des Threasholds liegt
          //wenn beides zutrifft, auf Ergebniss anzeigen, zuletzt gefunden auf aktuelle Zeit setzen und Scan stoppen
          Serial.println("  |  gesuchtes gerät in der nähe gefunden");
          lastTimefound = millis();
          advertisedDevice.getScan()->stop();
        }
      }
      Serial.println("");
    }
};
 
void setup(){
  pinMode (lautsprecher, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starte BLE Scanner");
  pServerAddress = new BLEAddress(Adresse.c_str());
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
}
 
void loop(){
  pBLEScan->start(10);
  if(millis() - lastTimefound > timeThreashold){
    Serial.println("Gesuchtes Signal zu lang nicht gefunden");
    while (digitalRead(button)==HIGH){
      tone(lautsprecher, 404);
      delay(200);
      noTone(lautsprecher);
      delay(200);
    }
  }
  delay(2000);
  Serial.println("neuer scan:");
}