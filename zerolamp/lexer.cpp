#include "lexer.h"

/*
ZBResult<Token, LexerError> Lexer::lex() {

}
*/

ZBResult<char32_t, Lexer::ReadCharError> Lexer::read_char() {

  size_t total_input_bytes = input.size();

  if (current_position >= total_input_bytes) {
    // we have reached the end of the input string
    return ZBResult<char32_t, Lexer::ReadCharError>(ReadCharError::REACHED_END);
  }

  uint8_t c = input[current_position];
  uint32_t code_point = 0;

  if ((c & 0x80) == 0) {
    code_point = c;
    current_position += 1;
  }
  else if ((c & 0xE0) == 0xC0 && current_position + 1 < total_input_bytes) {
    code_point = ((c & 0x1F) << 6) | (input[current_position + 1] & 0x3F);
    current_position += 2;
  }
  else if ((c & 0xF0) == 0xE0 && current_position + 2 < total_input_bytes) {
    code_point = ((c & 0x0F) << 12) | ((input[current_position + 1] & 0x3F) << 6) | (input[current_position + 2] & 0x3F);
    current_position += 3;
  }
  else if ((c & 0xF8) == 0xF0 && current_position + 3 < total_input_bytes) {
    code_point = ((c & 0x07) << 18) | ((input[current_position + 1] & 0x3F) << 12) |
                  ((input[current_position + 2] & 0x3F) << 6) | (input[current_position + 3] & 0x3F);
    current_position += 4;
  } 
  else {
    current_position += 1;
    return ZBResult<char32_t, Lexer::ReadCharError>(ReadCharError::INVALID_ENCODING);
  }

  return ZBResult<char32_t, Lexer::ReadCharError>(code_point);

}