#include "mode.h"
#include <Arduino.h>

unsigned long LampMode::get_render_interval() {

  if (immediate_rendering_requested) {
    immediate_rendering_requested = false;
    return 0;
  }

  return render_interval;
}

void LampMode::set_render_interval(unsigned long new_render_interval) {
  render_interval = new_render_interval;
}

void LampMode::request_immediate_rendering() {
  immediate_rendering_requested = true;
}

void LampMode::schedule_event(unsigned long timeout_ms, void* event) {

  LampModeEventContainer event_container = LampModeEventContainer(
    millis() + timeout_ms,
    event
  );

  future_events.push_back(event_container);

  if (future_events.size() == 1) {
    // a single-element array is already sorted
    assert(future_events_sorted);
    return;
  }

  assert(future_events.size() >= 2);

  if (!future_events_sorted) {
    return;
  }

  // the future_events array used to be sorted before we added the current event above
  // there is a possibility that the current event we added did not make the array not sorted
  // check whether this is the case
  // i.e., whether the currently scheduled event should be run before the second last event

  if (event_container.time <= future_events[future_events.size() - 2].time) {
    // the array remains sorted
    assert(future_events_sorted);
  }
  else {
    // unfortunately, the array becomes not sorted at this point
    future_events_sorted = false;
  }

}

void LampMode::event_tick() {

  if (future_events.empty()) {
    // no pending events, nothing to do
    return;
  }

  // sort the future_events array
  if (!future_events_sorted) {
    // sort by event time in descending order
    std::sort(future_events.begin(), future_events.end(), [](const LampModeEventContainer& a, const LampModeEventContainer& b) {
      return a.time > b.time;
    });
    future_events_sorted = true;
  }

  unsigned long current_time = millis();

  do {

    LampModeEventContainer event = future_events.back();

    if (current_time < event.time) {
      // we have reached an event that lies too far in the future
      break;
    }

    // event is to be fired
    handle_event(event.event);

    // remove the event that we have already handled
    future_events.pop_back();

  } while (!future_events.empty());

}