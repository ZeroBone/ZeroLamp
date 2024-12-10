#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

template <typename T, size_t capacity>
class VectorQueue {

private:
  T payload[capacity];
  size_t beginning; // index of the first element of the queue
  size_t end; // index of the element after the last element of the queue

public:
  VectorQueue() : end(0), beginning(0) {}

  bool is_empty() {
    return beginning == end;
  }

  bool push(T el) {
    size_t new_end = (end + 1) % capacity;

    if (new_end == beginning) {
      // queue full
      return false;
    }

    payload[end] = el;

    end = new_end;

    return true; // success
  }

  T poll() {
    assert(!is_empty());
    T el = payload[beginning];
    beginning = (beginning + 1) % capacity;
    return el;
  }

  size_t length() {
    if (beginning <= end) {
      // example:
      // x x x A B x x
      //       b   e
      return end - beginning;
    }
    // example
    // 0 1 2 3 4 5 6 (capacity=7)
    // 5 x x A B C 4
    //   e   b
    return end + capacity - beginning;
  }
  
};

#endif