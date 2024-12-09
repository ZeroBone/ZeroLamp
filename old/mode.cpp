#include "mode.h"

class Mode {

public:
  virtual void enter() = 0;
  virtual void leave() = 0;
  virtual void tick() = 0;

}