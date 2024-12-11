#ifndef MODE_H
#define MODE_H

class LampMode {

public:
  LampMode() {}

  virtual void enter(int logical_width, int logical_height) = 0;

  virtual void leave() = 0;

  virtual void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) = 0;

  virtual ~LampMode() {}

};

#endif