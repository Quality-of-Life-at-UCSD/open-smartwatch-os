
#include "./apps/test/test_display.h"


#include <anim_matrix.h>
#include <gfx_util.h>
#include <osw_app.h>
#include <osw_config.h>
#include <osw_config_keys.h>
#include <osw_hal.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


#define SERVICE_UUID           "50D02E01-CAD0-47A8-8BD5-DB5DCCB71336"
#define CHARACTERISTIC_UUID_RX "50D02E02-CAD0-47A8-8BD5-DB5DCCB71336"


bool deviceConnected;
//BLECharacteristic* writeCharacteristic;
BLECharacteristic* readCharacteristic;
BLEServer *pServer;

void OswAppTestDisplay::setup() {
  BLEDevice::init("Open Smartwatch");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  //writeCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);

  readCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  readCharacteristic->setCallbacks(new MyCallbacks());

  Serial.printf("*** Begin Advertising ***\n");
  pService->start();
  pServer->getAdvertising()->start();
}

int color(float t) {
    float t2 = t*6;
    while (t2 > 2)
        t2 -= 2;
    float x = 1 - abs(t2-1);
    if (t*6 < 1) return (int)(0xff0000+x*0xff00);
    if (t*6 < 2) return (int)(x*0xff0000+0xff00);
    if (t*6 < 3) return (int)(0xff00+x*0xff);
    if (t*6 < 4) return (int)(x*0xff00+0xff);
    if (t*6 < 5) return (int)(x*0xff0000+0xff);
    return (int)(0xff0000+x*0xff);
}

void OswAppTestDisplay::drawDisplay() {
  OswHal* hal = OswHal::getInstance();

  float r = (millis()%7000)/150 + 20;
  float t = (millis()%15000)/15000.0;
  hal->gfx()->fillCircle(120,120,r,rgb888to565(color(t)));
}


void OswAppTestDisplay::loop() {
  if (deviceConnected) { 
    OswHal* hal = OswHal::getInstance();
    hal->gfx()->fill(ui->getBackgroundColor());
    drawDisplay();
    hal->requestFlush();
  }
  else
    pServer->getAdvertising()->start();
}

void OswAppTestDisplay::stop() {

}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
  deviceConnected = true;
};

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
  deviceConnected = false;
}

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string rxValue = pCharacteristic->getValue();
  Serial.printf("Received Value: %s \n", rxValue.c_str());
}