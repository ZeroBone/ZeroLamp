#ifndef ZB_TOKEN_H
#define ZB_TOKEN_H

#include <Arduino.h>

class Token {

public:
  int id;
  size_t line;
  size_t start_position;

  Token(int id, size_t line, size_t start_position) : id(id), line(line), start_position(start_position) {}

};

#endif