#include "DFRobot_GDL.h"
#include "DFRobot_Font.h"
#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

void DFRobot_GDL::setFonts(const gdl_Font_t *font){
  if(font){
      _gdlFont = (gdl_Font_t *)font;
  }
}

size_t DFRobot_GDL::write(const uint8_t *buffer, size_t size){//默认为uft8，这里不处理gbk
  size_t n = 0;
  uint8_t c = 0;
  uint8_t num = 0;
  bool flag = true;//false:代表gbk编码，true，代表utf8编码
  uint32_t unicode = 0;
  uint32_t length = 0;
  //Serial.println("write(const uint8_t *buffer, size_t size)");
  // for(uint8_t i =0; i<size; i++){
      // Serial.println(buffer[i],HEX);
  // }
  //Serial.print("size = ");Serial.println(size);
  if(!_gdlFont){
      while(size--) {
          n += Adafruit_GFX::write(*buffer++);
      }
  }else{
      while(size){
          c = *buffer++;
          gdl_Font_t gdlFont;
          gdlFont.bitmap = (uint8_t *)pgm_read_dword(&_gdlFont->bitmap);
          //Serial.println(pgm_read_byte(&gdlFont.bitmap[0]),HEX);
          gdlFont.glyph = (gdl_Glyph_t *)pgm_read_dword(&_gdlFont->glyph);//取出glyph的地址
          gdlFont.yAdvance = pgm_read_byte(&_gdlFont->yAdvance);
          gdlFont.length = (uint32_t)pgm_read_dword(&_gdlFont->length);
          if(c == '\n'){
              cursor_x  = 0;
              cursor_y += gdlFont.yAdvance;
          }
          if(c < 128){//说明是字符{
              n++;
              size -= 1;
          }else{
              length = 0;
              num = getUtf_8Bytes(c);
              unicode = utf8ToUnicode(num, (uint8_t *)(buffer-1));
              //Serial.print("unicode1 = ");Serial.println(unicode,HEX);
              for(uint32_t i = 0; i < gdlFont.length; i++){
                  //Serial.print("unicode = "); Serial.println(pgm_read_word(&(gdlFont.glyph->unicode)),HEX);
                  if(unicode == (uint32_t)pgm_read_word(&(gdlFont.glyph->unicode))){
                      gdlFont.bitmap += length;
                      //Serial.println(pgm_read_byte(&gdlFont.bitmap[0]),HEX);
					  if((cursor_y + gdlFont.yAdvance) > _height){
                    	  cursor_x = 0;
                    	  cursor_y = 0;
                      }
                      if((cursor_x + pgm_read_byte(&(gdlFont.glyph->xAdvance))) > _width){
                    	  cursor_x = 0;
                    	  cursor_y += gdlFont.yAdvance;
                      }
                      drawCharBitmaps(cursor_x, cursor_y, &gdlFont, textcolor, textbgcolor);
                      //Serial.print("cursor_x = ");Serial.println(cursor_x);
                      cursor_x += pgm_read_byte(&(gdlFont.glyph->xAdvance));
                      //Serial.println(pgm_read_byte(&(gdlFont.glyph->xAdvance)));
                      break;
                  }
                  length += (uint32_t)pgm_read_word(&(gdlFont.glyph->length));
                  gdlFont.glyph++;
              }
              buffer += num - 1;
              if(size > num)
                 size -= num;
              else
                  size = 0;
              //Serial.print("num = ");Serial.println(num);
              //Serial.print("size1 = ");Serial.println(size);
              n += num;
          }
      }
  }
  return n;
}
 //&(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
void DFRobot_GDL::drawCharBitmaps(uint16_t x, uint16_t y, gdl_Font_t *gdlFont, uint16_t fg, uint16_t bg){
  uint16_t length = pgm_read_word(&(gdlFont->glyph->length));
  uint8_t width = pgm_read_byte(&(gdlFont->glyph->width));
  uint8_t xStep = pgm_read_byte(&(gdlFont->glyph->xAdvance));
  uint8_t yStep = gdlFont->yAdvance;
  
  uint16_t x_pos = x + pgm_read_byte(&gdlFont->glyph->xOffset);
  uint16_t y_pos = y + pgm_read_byte(&gdlFont->glyph->yOffset);
  x = x_pos;
  y = y_pos;
  
  if((xStep + x) >  _width || (yStep + y) > _height){
      if((xStep + x) >  _width && (yStep + y) < _height)
          cursor_x = 0;
      if((yStep + y) > _height)
          cursor_y += yStep;
  }
  uint8_t w = 0;
  uint8_t total = 0;//记录每行的总宽度
  for(uint16_t i = 0; i < length; i++){
      for(uint8_t j = 0; j < 2; j++){
          uint8_t val = (pgm_read_byte(&gdlFont->bitmap[i]))>>(4*(1-j));
          w = val&0x07;
          total += w;
          while(total > width){//代表一行结束,y的值增加
              uint8_t c = width - (total - w);
              if(c != 0){
                  if(val & 0x08){
                      drawFastHLine(x, y,c,fg);
                  }else{
                      drawFastHLine(x, y,c,bg);
                  }
              }
              x = x_pos;
              y += 1;
              w = w - c;
              total = w;
          }
          if(val & 0x08){
              drawFastHLine(x, y,w,0x001F);
          }else{
             drawFastHLine(x, y,w,bg);
          }
          x += w;
      }
  }
}

uint32_t DFRobot_GDL::utf8ToUnicode(uint8_t num, uint8_t *buf){
  uint32_t unicode = 0;
  uint8_t Byte[num];
  memset(Byte, 0, sizeof(Byte));
  // Serial.println((char*)buf);
  // for(int i = 0; i<num; i++){
      // Serial.println(buf[i],HEX);
  // }
  //Serial.print("num = ");Serial.println(num);
  if(num > 1 && num < 7){//大概率为uft-8编码
      for(uint8_t i = 0; i < num; i++){
          Byte[0] |= 1 <<(7-i);
          if (i > 0){
              Byte[i] = 0xC0;
          }
      }
      Byte[0] |= 1<<(7 - num);
      for(uint8_t i = 0; i < num; i++){
          Byte[i] = ~Byte[i] & *buf++;
          //Serial.println(Byte[i],HEX);
      }
      uint8_t index = 0;
      uint8_t n = num;
      while((n--)){
          unicode |= uint32_t(Byte[n]) <<index;
          index += 6;
      }
  }
  //Serial.println("utf8ToUnicode(uint8_t num, uint8_t *buf)");
  //Serial.println(unicode,HEX);
  return unicode;
}

uint8_t DFRobot_GDL::getUtf_8Bytes(uint8_t b){
   uint8_t num = 0, i = 0;
   for(i = 0; i < 7; i++){
       if(b&(0x80>>i)){
          num +=1;
        }else{
            if (num == 0)
               num = 1; 
            break;
          }
    }
    if(i==1)
      num = 255;
    return num;
}