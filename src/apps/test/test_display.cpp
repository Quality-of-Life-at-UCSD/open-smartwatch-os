
#include "./apps/test/test_display.h"

#include <anim_matrix.h>
#include <gfx_util.h>
#include <osw_app.h>
#include <osw_config.h>
#include <osw_config_keys.h>
#include <osw_hal.h>



void OswAppTestDisplay::setup() {
  tracker = new BLETracker();
}

void OswAppTestDisplay::stop() {
  delete tracker;
}

/*
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
void drawDisplay() {
  OswHal* hal = OswHal::getInstance();

  float r = (millis()%7000)/150 + 20;
  float t = (millis()%15000)/15000.0;
  hal->gfx()->fillCircle(120,120,r,rgb888to565(color(t)));
}
*/

BLEAddress addr;
void OswAppTestDisplay::loop() {
  /*
  OswHal* hal = OswHal::getInstance();
  hal->gfx()->fill(ui->getBackgroundColor());
  drawDisplay();
  hal->requestFlush();
  */
  tracker->tick();
  OswHal* hal = OswHal::getInstance();
  hal->gfx()->println(tracker->getAvgRssi(addr));
}