#include "lexer.h"
#include "parser.h"


ZBResult<Token, LexerError> Lexer::lex() {

  ZBResult<char32_t, ReadCharError> ch_result;
  char32_t ch;

  do {

    ch_result = read_char();

    if (ch_result.is_error()) {
      return ZBResult<Token, LexerError>(LexerError(current_line_number, current_position, ch_result.unwrap_error()));
    }

    ch = ch_result.unwrap();

  } while (ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ');

  Token token = Token(current_line_number, current_position - 1);

  switch (ch) {

    case T_C_LEFT_BRACE: // {
      token.init(T_LEFT_BRACE, 1);
      break;

    case T_C_RIGHT_BRACE: // }
      token.init(T_RIGHT_BRACE, 1);
      break;

  }

  token.assert_init();

  return ZBResult<Token, LexerError>(token);

}

ZBResult<char32_t, ReadCharError> Lexer::read_char() {

  size_t total_input_bytes = input.size();

  if (current_position >= total_input_bytes) {
    // we have reached the end of the input string
    return ZBResult<char32_t, ReadCharError>(ReadCharError::REACHED_END);
  }

  uint8_t c = input[current_position];
  uint32_t code_point = 0;

  if (c == '\n') {
    current_line_number++;
  }

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
    return ZBResult<char32_t, ReadCharError>(ReadCharError::INVALID_ENCODING);
  }

  return ZBResult<char32_t, ReadCharError>(code_point);

}