#ifndef ZB_LEXER_H
#define ZB_LEXER_H

#include <sstream>
#include "token.h"
#include "result.h"

enum class ReadCharError {
  REACHED_END,
  INVALID_ENCODING
};

class LexerError {
public:
  const size_t line;
  const size_t position;
  std::string message;

  LexerError(const size_t line, const size_t position, std::string message) : line(line), position(position), message(message) {}

  LexerError(const size_t line, const size_t position, ReadCharError e) : line(line), position(position) {

    switch (e) {

      case ReadCharError::REACHED_END:
        message = "";
        break;

      case ReadCharError::INVALID_ENCODING:
        message = "Invalid encoding.";
        break;

      default:
        assert(false);
        break;
    }

  }

  bool is_eof_error() const {
    return message.empty();
  }

};

class Lexer {

private:
  std::string input;
  size_t current_position = 0;
  size_t current_line_number = 0;
  bool peeking;

public:
  Lexer(const std::string& input) : input(input) {}

  ZBResult<Token, LexerError> lex();

private:
  ZBResult<char32_t, ReadCharError> read_char();

};

#endif