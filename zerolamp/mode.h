#ifndef MODE_H
#define MODE_H

class LampMode {

public:
  LampMode() {}

  virtual void enter(size_t logical_width, size_t logical_height) = 0;

  virtual void leave() = 0;

  virtual void render_frame(size_t offset_x, size_t offset_y, size_t viewport_width, size_t viewport_height) = 0;

  virtual ~LampMode() {}

};

#endif