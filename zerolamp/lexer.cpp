#include "lexer.h"

std::variant<Token, LexerError> Lexer::lex() {



}

char32_t Lexer::read_char() {

  char32_t codepoint = 0;
  unsigned char c;

  stream.get(&c);

}