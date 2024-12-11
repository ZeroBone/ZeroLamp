#ifndef MODE_H
#define MODE_H

class LampMode {

private:
  unsigned long render_interval = 500; // number of milliseconds to wait between rendering individual frames

public:
  LampMode() {}

  virtual void enter(int logical_width, int logical_height) = 0;

  virtual void leave() = 0;

  virtual void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) = 0;

  virtual ~LampMode() {}

  unsigned long get_render_interval();

protected:
  void set_render_interval(unsigned long new_render_interval);

};

#endif