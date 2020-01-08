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
  int8_t xOffset;
  int8_t yOffset;
  uint8_t xAdvance;
} gdl_Glyph_t;

/// Data stored for FONT AS A WHOLE
typedef struct{
  uint8_t  *bitmap;      /*< Glyph bitmaps, concatenated*/
  gdl_Glyph_t *glyph;       ///< Glyph array
  uint8_t yAdvance;    
  uint32_t length;
}gdl_Font_t;

#include "Fonts/SIMKAIFont12pt.h"
#include "Fonts/SIMKAIFont18pt.h"
#include "Fonts/SIMKAIFont24pt.h"
#include "Fonts/SIMKAIFont36pt.h"
#include "Fonts/SIMKAIFont48pt.h"
#include "Fonts/SIMKAIFont72pt.h"
#endif 