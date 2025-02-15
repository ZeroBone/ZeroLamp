#ifndef ZB_LEXER_H
#define ZB_LEXER_H

#include <sstream>
#include "token.h"
#include "result.h"

class LexerError {
public:
  const size_t line;
  const size_t position;
  std::string message;
  LexerError(const size_t line, const size_t position, std::string message) : line(line), position(position), message(message) {}
};

class Lexer {

private:
  std::string input;
  size_t current_position = 0;
  bool peeking;

public:
  Lexer(const std::string& input) : input(input) {}

  // ZBResult<Token, LexerError> lex();

private:
  enum class ReadCharError {
    REACHED_END,
    INVALID_ENCODING
  };

  ZBResult<char32_t, ReadCharError> read_char();

};

#endif