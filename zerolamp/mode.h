#ifndef MODE_H
#define MODE_H

class LampMode {

public:
  LampMode() {}

  virtual void enter() = 0;

  virtual void leave() = 0;

  virtual void render_frame() = 0;

  virtual ~LampMode() {}

};

#endif