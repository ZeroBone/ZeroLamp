#include "utils.h"

bool parseColorSpec(String colorSpec, CRGB &result) {
  colorSpec.trim();

  if (colorSpec.startsWith("#")) {
    // Hex color code
    
    if (colorSpec.length() == 7) {
      // #RRGGBB
      uint8_t r = strtol(colorSpec.substring(1, 3).c_str(), nullptr, 16);
      uint8_t g = strtol(colorSpec.substring(3, 5).c_str(), nullptr, 16);
      uint8_t b = strtol(colorSpec.substring(5, 7).c_str(), nullptr, 16);
      result = CRGB(r, g, b);
      return true;
    }
    
    if (colorSpec.length() == 4) {
      // #RGB (shorthand)
      uint8_t r = strtol(colorSpec.substring(1, 2).c_str(), nullptr, 16) * 17; // Scale to 0-255
      uint8_t g = strtol(colorSpec.substring(2, 3).c_str(), nullptr, 16) * 17;
      uint8_t b = strtol(colorSpec.substring(3, 4).c_str(), nullptr, 16) * 17;
      result = CRGB(r, g, b);
      return true;
    }

    return false; // invalid syntax
  }
  
  if (colorSpec.equalsIgnoreCase("red")) {
    result = CRGB::Red;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("green")) {
    result = CRGB::Green;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("blue")) {
    result = CRGB::Blue;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("black")) {
    result = CRGB::Black;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("white")) {
    result = CRGB::White;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("yellow")) {
    result = CRGB::Yellow;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("cyan")) {
    result = CRGB::Cyan;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("magenta")) {
    result = CRGB::Magenta;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("orange")) {
    result = CRGB(255, 165, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("purple")) {
    result = CRGB(128, 0, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("pink")) {
    result = CRGB(255, 192, 203);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("brown")) {
    result = CRGB(165, 42, 42);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("lime")) {
    result = CRGB(0, 255, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("indigo")) {
    result = CRGB(75, 0, 130);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("violet")) {
    result = CRGB(238, 130, 238);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("gold")) {
    result = CRGB(255, 215, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("silver")) {
    result = CRGB(192, 192, 192);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("gray") || colorSpec.equalsIgnoreCase("grey")) {
    result = CRGB(128, 128, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("navy")) {
    result = CRGB(0, 0, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("teal")) {
    result = CRGB(0, 128, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("olive")) {
    result = CRGB(128, 128, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("maroon")) {
    result = CRGB(128, 0, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("aqua")) {
    result = CRGB(0, 255, 255);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("beige")) {
    result = CRGB(245, 245, 220);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("coral")) {
    result = CRGB(255, 127, 80);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("chocolate")) {
    result = CRGB(210, 105, 30);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("khaki")) {
    result = CRGB(240, 230, 140);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("salmon")) {
    result = CRGB(250, 128, 114);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("orchid")) {
    result = CRGB(218, 112, 214);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("turquoise")) {
    result = CRGB(64, 224, 208);
    return true;
  }

  // parsing failed
  return false;
}