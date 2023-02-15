#ifndef OSW_APP_TEST_DISPLAY_H
#define OSW_APP_TEST_DISPLAY_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

#include "BleConnectionStatus.h"
#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"

class OswAppTestDisplay : public OswApp {
 public:
  OswAppTestDisplay(void) { ui = OswUI::getInstance(); };
  virtual void setup() override;
  virtual void loop() override;
  virtual void stop() override;
  ~OswAppTestDisplay(){};

 private:
  OswUI* ui;
  void drawDisplay();
};

class MyServerCallbacks: public BLEServerCallbacks {
    virtual void onConnect(BLEServer* pServer);

    virtual void onDisconnect(BLEServer* pServer);
};

class MyCallbacks: public BLECharacteristicCallbacks {
    virtual void onWrite(BLECharacteristic *pCharacteristic);
};

#endif
