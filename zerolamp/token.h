#ifndef ZB_TOKEN_H
#define ZB_TOKEN_H

#include <Arduino.h>

#define T_C_LEFT_BRACE '{'
#define T_C_RIGHT_BRACE '}'

class Token {

public:
  int id = -1;
  size_t line;
  size_t start_position;
  size_t length = 0;

  Token(size_t line, size_t start_position) : line(line), start_position(start_position) {}

  inline void init(int id, size_t length) {
    this->id = id;
    this->length = length;
  }

  inline void assert_init() {
    assert(id >= 0);
    assert(length != 0);
  }

};

#endif