#ifndef _GDLFONTDEF_H_
#define _GDLFONTDEF_H_
#include "Arduino.h"
#include <DFRobot_Type.h>

/// Font data stored PER GLYPH
typedef struct{
  uint16_t unicode;
  uint16_t length;
  uint8_t  width;            ///< Bitmap dimensions in pixels
  uint8_t  height;           ///< Bitmap dimensions in pixels
  //uint8_t  xStep;            ///< width+xpitch
  int8_t xOffset;
  int8_t yOffset;
  uint8_t xAdvance;
  //uint8_t xpitch;           ///<字与字之间的间隔
}gdl_Glyph_t;

/// Data stored for FONT AS A WHOLE
typedef struct{
  uint8_t  *bitmap;      ///< Glyph bitmaps, concatenated
  gdl_Glyph_t *glyph;       ///< Glyph array
  //uint8_t   yStep;       ///< 永远为偶数，字体起始点（x,y）
  uint8_t yAdvance;
  uint32_t length;
}gdl_Font_t;
#include "Fonts/SIMKAIFont12pt.h"
#include "Fonts/SIMKAIFont72pt.h"
#endif 