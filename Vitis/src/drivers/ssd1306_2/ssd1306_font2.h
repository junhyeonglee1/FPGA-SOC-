#ifndef __SSD1306_FONTS_H__
#define __SSD1306_FONTS_H__

#include "ssd1306_command2.h"
#include "ssd1306_conf_template2.h"

#ifdef SSD1306_INCLUDE_FONT_6x8
extern const SSD1306_Font_t2 Font_6x82;
#endif
#ifdef SSD1306_INCLUDE_FONT_7x10
extern const SSD1306_Font_t2 Font_7x102;
#endif
#ifdef SSD1306_INCLUDE_FONT_11x18
extern const SSD1306_Font_t2 Font_11x182;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x26
extern const SSD1306_Font_t2 Font_16x262;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x24
extern const SSD1306_Font_t2 Font_16x242;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x15
/** Generated Roboto Thin 15
 * @copyright Google https://github.com/googlefonts/roboto
 * @license This font is licensed under the Apache License, Version 2.0.
*/
extern const SSD1306_Font_t2 Font_16x152;
#endif

#endif // __SSD1306_FONTS_H__
