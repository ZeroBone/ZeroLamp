#include "font.h"
#include "matrix.h"
#include <cassert>

const uint8_t font3x5[][3] = {
  {0b00000, 0b00000, 0b00000}, // Space (ASCII 32)
  {0b00000, 0b10111, 0b00000}, // Exclamation Mark (!, ASCII 33)
  {0b00011, 0b00000, 0b00011}, // Double Quote (", ASCII 34)
  {0b11111, 0b01010, 0b11111}, // Hash (#, ASCII 35)
  {0b10010, 0b11111, 0b01001}, // Dollar ($, ASCII 36)
  {0b01001, 0b00100, 0b10010}, // Percent (% ASCII 37)
  {0b01010, 0b10101, 0b01010}, // Ampersand (&, ASCII 38)
  {0b00000, 0b00011, 0b00000}, // Single Quote (', ASCII 39)
  {0b00000, 0b01110, 0b10001}, // Open Parenthesis ((, ASCII 40)
  {0b10001, 0b01110, 0b00000}, // Close Parenthesis (), ASCII 41)
  {0b01010, 0b00100, 0b01010}, // Asterisk (*, ASCII 42)
  {0b00100, 0b01110, 0b00100}, // Plus (+, ASCII 43)
  {0b10000, 0b01000, 0b00000}, // Comma (, ASCII 44)
  {0b00100, 0b00100, 0b00100}, // Dash (-, ASCII 45)
  {0b00000, 0b10000, 0b00000}, // Period (., ASCII 46)
  {0b01000, 0b00100, 0b00010}, // Slash (/, ASCII 47)
  // Numbers (0-9, ASCII 48-57)
  {0b11111, 0b10001, 0b11111}, // 0
  {0b10010, 0b11111, 0b10000}, // 1
  {0b11101, 0b10101, 0b10111}, // 2
  {0b10101, 0b10101, 0b11111}, // 3
  {0b00111, 0b00100, 0b11111}, // 4
  {0b10111, 0b10101, 0b11101}, // 5
  {0b11111, 0b10101, 0b11101}, // 6
  {0b10001, 0b01001, 0b00111}, // 7
  {0b11111, 0b10101, 0b11111}, // 8
  {0b10111, 0b10101, 0b11111}, // 9
  // ASCII 58-64
  {0b00000, 0b01010, 0b00000}, // : 0x3a 58
  {0b00000, 0b11010, 0b00000}, // ; 0x3b 59
  {0b00100, 0b01010, 0b10001}, // < 0x3c 60
  {0b01010, 0b01010, 0b01010}, // = 0x3d 61
  {0b10001, 0b01010, 0b00100}, // > 0x3e 62
  {0b00011, 0b10101, 0b00111}, // ? 0x3f 63
  {0b01101, 0b01101, 0b01111}, // @ 0x40 64
  // Letters (A-Z, ASCII 65-90)
  {0b11111, 0b00101, 0b11111}, // A
  {0b11111, 0b10101, 0b01010}, // B
  {0b11111, 0b10001, 0b10001}, // C
  {0b11111, 0b10001, 0b01110}, // D
  {0b11111, 0b10101, 0b10101}, // E
  {0b11111, 0b00101, 0b00101}, // F
  {0b01110, 0b10101, 0b11101}, // G
  {0b11111, 0b00100, 0b11111}, // H
  {0b10001, 0b11111, 0b10001}, // I
  {0b01001, 0b10001, 0b01111}, // J
  {0b11111, 0b01010, 0b10001}, // K
  {0b11111, 0b10000, 0b10000}, // L
  {0b11111, 0b00010, 0b11111}, // M
  {0b11111, 0b01110, 0b11111}, // N (looks very weird but idk how to improve)
  {0b01110, 0b10001, 0b01110}, // O
  {0b11111, 0b00101, 0b00010}, // P
  {0b00110, 0b01001, 0b10110}, // Q
  {0b11111, 0b00101, 0b11010}, // R
  {0b10010, 0b10101, 0b01001}, // S
  {0b00001, 0b11111, 0b00001}, // T
  {0b01111, 0b10000, 0b01111}, // U
  {0b00111, 0b11000, 0b00111}, // V
  {0b11111, 0b01000, 0b11111}, // W
  {0b11011, 0b00100, 0b11011}, // X
  {0b00011, 0b11100, 0b00011}, // Y
  {0b11001, 0b10101, 0b10011}, // Z
  {0b00000, 0b11111, 0b10001}, // [ 0x5b 91
  {0b00010, 0b00100, 0b01000}, // \ 0x5c 92
  {0b10001, 0b11111, 0b00000}, // ] 0x5d 93
  {0b00100, 0b00010, 0b00100}, // ^ 0x5e 94
  {0b10000, 0b10000, 0b10000}, // _ 0x5f 95
  {0b00001, 0b00010, 0b00000}, // ` 0x60 96
  {0b11111, 0b00101, 0b11111}, // a 0x61 97
  {0b11111, 0b10101, 0b01010}, // b 0x62 98
  {0b11111, 0b10001, 0b10001}, // c 0x63 99
  {0b11111, 0b10001, 0b01110}, // d 0x64 100
  {0b11111, 0b10101, 0b10101}, // e 0x65 101
  {0b11111, 0b00101, 0b00101}, // f 0x66 102
  {0b01110, 0b10101, 0b11101}, // g 0x67 103
  {0b11111, 0b00100, 0b11111}, // h 0x68 104
  {0b10001, 0b11111, 0b10001}, // i 0x69 105
  {0b01001, 0b10001, 0b01111}, // j 0x6a 106
  {0b11111, 0b01010, 0b10001}, // k 0x6b 107
  {0b11111, 0b10000, 0b10000}, // l 0x6c 108
  {0b11111, 0b00010, 0b11111}, // m 0x6d 109
  {0b11111, 0b01110, 0b11111}, // n 0x6e 110
  {0b01110, 0b10001, 0b01110}, // o 0x6f 111
  {0b11111, 0b00101, 0b00010}, // p 0x70 112
  {0b00110, 0b01001, 0b10110}, // q 0x71 113
  {0b11111, 0b00101, 0b11010}, // r 0x72 114
  {0b10010, 0b10101, 0b01001}, // s 0x73 115
  {0b00001, 0b11111, 0b00001}, // t 0x74 116
  {0b01111, 0b10000, 0b01111}, // u 0x75 117
  {0b00111, 0b11000, 0b00111}, // v 0x76 118
  {0b11111, 0b01000, 0b11111}, // w 0x77 119
  {0b11011, 0b00100, 0b11011}, // x 0x78 120
  {0b00011, 0b11100, 0b00011}, // y 0x79 121
  {0b11001, 0b10101, 0b10011}, // z 0x7a 122
  {0b00100, 0b01110, 0b10001}, // { 0x7b 123
  {0b00000, 0b11111, 0b00000}, // | 0x7c 124
  {0b10001, 0b01110, 0b00100}, // } 0x7d 125
  {0b00100, 0b01010, 0b00100}, // ~ 0x7e 126
};

int draw_character(int start_x, int start_y, char c, int x_min, int x_max, CRGB color) {
  // start_x - x coordinate where to start rendering text (can be negative)
  // start_y - y coordinate where to start rendering text
  // c - character to draw
  // x_min - the minimum x coordinate to actually draw to (must be non-negative)
  // x_max - the maximum x coordinate to actually draw to (must be non-negative)
  // color - color of the character
  // Returns the width of the character that was drawn

  assert(start_y >= 0);
  assert(x_min >= 0);
  assert(x_max >= 0);

  if (c < 32 || c > 126) {
    // unsupported character
    c = '?';
  }

  const uint8_t* charBitmap = font3x5[c - 32];

  int empty_column_count = 0;

  for (int col = 0; col < 3; col++) {

    int final_x = start_x + col - empty_column_count;

    if (final_x > x_max) {
      // we are not allowed to draw this far
      // since the final_x variable grows as col grows, we can break
      break;
    }

    // first we need to check whether there is at least one pixel to be drawn in the current column
    // for example, if c is '!', then the first columns will be empty and should be ignored
    if (charBitmap[col] & 0x1f == 0) {
      // no pixels in this column
      empty_column_count++;
      continue;
    }

    if (final_x < x_min) {
      // we are to the left of the area we are allowed to draw in
      continue;
    }

    for (int row = 0; row < 5; row++) {

      if (!(charBitmap[col] & (1 << row))) {
        continue;
      }
      
      size_t final_y = row + start_y;
      assert(final_y < MATRIX_HEIGHT);
      assert(final_x >= x_min);
      assert(final_x <= x_max);
      matrix_setLedColor(final_y, final_x, color);
    }

  }

  return 3 - empty_column_count;

}

int draw_string_horizontally(int start_x, int start_y, char* str, int x_min, int x_max, CRGB color, int space_between_letters) {
  // start_x - x coordinate where to start rendering text (can be negative)
  // start_y - y coordinate where to start rendering text
  // str - string to draw
  // x_min - the minimum x coordinate to actually draw to (must be non-negative)
  // x_max - the maximum x coordinate to actually draw to (must be non-negative)
  // color - color of the character
  // space_between_letters - how many pixels to add between letters (horizontal spacing, must be non-negative)
  // returns the width of the entire text

  assert(x_min >= 0);
  assert(x_max >= 0);
  assert(space_between_letters >= 0);

  if (str[0] == '\0') {
    // empty string
    return 0;
  }

  int current_x = start_x;
  int total_width = 0;

  for (size_t i = 0; str[i] != '\0'; i++) {
    int width = draw_character(current_x, start_y, str[i], x_min, x_max, color);
    current_x += width + space_between_letters;
    total_width += width + space_between_letters;
  }

  assert(space_between_letters == 0 || total_width >= 1);

  return total_width - space_between_letters;

}