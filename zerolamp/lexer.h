#ifndef ZB_LEXER_H
#define ZB_LEXER_H

#include <sstream>
#include <variant>
#include "token.h"

class LexerError {
public:
  const size_t line;
  const size_t position;
  std::string message;
  LexerError(const size_t line, const size_t position, std::string message) : line(line), position(position), message(message) {}
};

class Lexer {

private:
  std::istringstream stream;

public:
  Lexer(std::istringstream stream) : stream(std::move(stream)) {}
  Lexer(const std::string& input) : stream(input) {}

  std::variant<Token, LexerError> lex();

private:
  char32_t read_char();

};

#endif