#pragma once
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include <renderd7/external/stb_truetype.h>

#define MAXUNICODE 0x10FFFF

namespace RenderD7 {
inline int utf8_decode(const char *o) {
  static const unsigned int limits[] = {0xFF, 0x7F, 0x7FF, 0xFFFF};
  const unsigned char *s = (const unsigned char *)o;
  unsigned int c = s[0];
  unsigned int res = 0; /* final result */
  if (c < 0x80)         /* ascii? */
    res = c;
  else {
    int count = 0;             /* to count number of continuation bytes */
    while (c & 0x40) {         /* still have continuation bytes? */
      int cc = s[++count];     /* read next byte */
      if ((cc & 0xC0) != 0x80) /* not a continuation byte? */
        return -1;             /* invalid byte sequence */
      res = (res << 6) | (cc & 0x3F); /* add lower 6 bits from cont. byte */
      c <<= 1;                        /* to test next bit */
    }
    res |= ((c & 0x7F) << (count * 5)); /* add first byte */
    if (count > 3 || res > MAXUNICODE || res <= limits[count])
      return -1; /* invalid byte sequence */
    s += count;  /* skip continuation bytes read */
  }
  return res;
}

inline std::string IntToUtf8(int convertval) {

  // We only care about plane 1 right now,
  // but know that we have other options (0x10FFFF)
  // Technically UTF-8 is "limited" to 4 bytes, so it's not
  // Like it matters much anyways these days

  if (convertval == 0)
    return " ";
  if ((convertval <= 0x7F) && (convertval > 0x00)) {

    std::string out(".");

    std::bitset<8> x(convertval);

    unsigned long l = x.to_ulong();
    unsigned char c = static_cast<unsigned char>(l);
    out[0] = c;

    return out;

  } else if ((convertval >= 0x80) && (convertval <= 0x07FF)) {

    std::string out("..");

    int firstShift = (convertval >> 0x06) ^ 0xC0;
    int secondShift = ((convertval ^ 0xFFC0) | 0x80) & ~0x40;

    std::bitset<8> first(firstShift);
    std::bitset<8> last(secondShift);

    unsigned long l = first.to_ulong();
    unsigned char c = static_cast<unsigned char>(l);
    out[0] = c;

    unsigned long ltwo = last.to_ulong();
    unsigned char ctwo = static_cast<unsigned char>(ltwo);
    out[1] = ctwo;

    return out;

  } else if ((convertval >= 0x0800) && (convertval <= 0xFFFF)) {

    std::string out("...");

    int firstShift = ((convertval ^ 0xFC0FFF) >> 0x0C) | 0xE0;
    int secondShift = (((convertval ^ 0xFFF03F) >> 0x06) | 0x80) & ~0x40;
    int thirdShift = ((convertval ^ 0xFFFC0) | 0x80) & ~0x40;

    std::bitset<8> first(firstShift);
    std::bitset<8> second(secondShift);
    std::bitset<8> third(thirdShift);

    unsigned long lone = first.to_ulong();
    unsigned char cone = static_cast<unsigned char>(lone);
    out[0] = cone;

    unsigned long ltwo = second.to_ulong();
    unsigned char ctwo = static_cast<unsigned char>(ltwo);
    out[1] = ctwo;

    unsigned long lthree = third.to_ulong();
    unsigned char cthree = static_cast<unsigned char>(lthree);
    out[2] = cthree;

    return out;

  } else {
    return " ";
  }
}
#define I2U82I(val) RenderD7::utf8_decode(RenderD7::IntToUtf8(val).c_str())

class NFontApi {
public:
  NFontApi();
  ~NFontApi();
  void LoadTTF(std::string path);
  unsigned char *GetGlyphBitmap(char glyph);
  std::string GetStatus() { return status; }
  float GetScale() { return scale; }
  int GetGlyphWidth(char glyph);
  int GetGlyphHeight(char glyph);
  int GetLineHeight() { return l_h; }
  int GetBaseHeight() { return height; }

private:
  std::string status;

  int height;

  float scale;
  int b_w;
  int b_h;
  int l_h;

  int w;
  int h;

  int x0, y0, x1, y1;
  int ascent, baseline, decent, linegap;

  int linespace;

  stbtt_fontinfo font;
};
} // namespace RenderD7