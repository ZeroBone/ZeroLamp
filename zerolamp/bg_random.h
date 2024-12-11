#ifndef ZB_BG_RANDOM_H
#define ZB_BG_RANDOM_H

#include "mode.h"

class RandomBG : public LampMode {

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);

};

#endif