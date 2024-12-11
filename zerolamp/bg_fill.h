#ifndef ZB_BG_FILL_H
#define ZB_BG_FILL_H

#include <FastLED.h>
#include "mode.h"

class FillBG : public LampMode {

private:
  CRGB fill_color = CRGB::Yellow;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);

};

#endif