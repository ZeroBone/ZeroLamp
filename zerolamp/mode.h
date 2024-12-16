#ifndef ZB_MODE_H
#define ZB_MODE_H

#include <vector>
#include <string>

enum class CommandHandleResult {
  HANDLED,
  NOT_HANDLED
};

struct LampModeEventContainer {
  
  unsigned long time;

  void* event;

  LampModeEventContainer(unsigned long time, void* event) : time(time), event(event) {}

};

class LampMode {

private:
  unsigned long render_interval = 500; // number of milliseconds to wait between rendering individual frames
  bool immediate_rendering_requested = true; // the first frame should be rendered as soon as possible

  std::vector<LampModeEventContainer> future_events;
  bool future_events_sorted = true; // whether the future_events array is sorted in descending order by event time

public:
  LampMode() {}

  virtual void enter(int logical_width, int logical_height) = 0;

  virtual void leave() = 0;

  virtual void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) = 0;

  virtual CommandHandleResult handle_command(std::string command) = 0;

  virtual void handle_event(void* event) = 0;

  virtual ~LampMode() {}

  unsigned long get_render_interval();

  void event_tick();

protected:
  void set_render_interval(unsigned long new_render_interval);
  void request_immediate_rendering();
  void schedule_event(unsigned long timeout_ms, void* event);

};

#endif