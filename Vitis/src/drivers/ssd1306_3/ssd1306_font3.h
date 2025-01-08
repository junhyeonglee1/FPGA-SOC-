#ifndef __SSD1306_FONTS_H__
#define __SSD1306_FONTS_H__

#include "ssd1306_command3.h"
#include "ssd1306_conf_template3.h"

#ifdef SSD1306_INCLUDE_FONT_6x8
extern const SSD1306_Font_t3 Font_6x83;
#endif
#ifdef SSD1306_INCLUDE_FONT_7x10
extern const SSD1306_Font_t3 Font_7x103;
#endif
#ifdef SSD1306_INCLUDE_FONT_11x18
extern const SSD1306_Font_t3 Font_11x183;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x26
extern const SSD1306_Font_t3 Font_16x263;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x24
extern const SSD1306_Font_t3 Font_16x243;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x15
/** Generated Roboto Thin 15
 * @copyright Google https://github.com/googlefonts/roboto
 * @license This font is licensed under the Apache License, Version 2.0.
*/
extern const SSD1306_Font_t3 Font_16x153;
#endif

#endif // __SSD1306_FONTS_H__
