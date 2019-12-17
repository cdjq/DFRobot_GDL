#include "DFRobot_GDL.h"

DFRobot_SSD1306_IIC_128x32 ssd;

void setup() {
  Serial.begin(115200);
  Serial.println("SSD1306 Test!");
  ssd.begin();
  
  Serial.println("Fillscreen Test!");
  testFillScreen1();
  
  Serial.println("Text Test!");
  textTest1();
  
  Serial.print(F("Lines                    "));
  testLines1(DF_GDL_CYAN);
  
  Serial.print(F("Horiz/Vert Lines         "));
  testFastLines1(DF_GDL_RED, DF_GDL_BLUE);
  delay(500);

  Serial.print(F("Rectangles (outline)     "));
  testRects(DF_GDL_GREEN);
  delay(500);
  Serial.print(F("Rectangles (filled)      "));
  testFilledRects(DF_GDL_YELLOW, DF_GDL_PURPLE);
  delay(500);

  Serial.print(F("Circles (filled)         "));
  testFilledCircles(10, DF_GDL_PURPLE);

  Serial.print(F("Circles (outline)        "));
  testCircles(10, DF_GDL_WHITE);
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  testTriangles();
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));
}

void loop() {
  //ssd.fillScreen(0x1fFF);
  //ssd.fillScreen(0xFF00);
}

void testFillScreen1(){
  ssd.fillScreen(DF_GDL_BLACK);
  ssd.fillScreen(DF_GDL_WHITE);
}

void textTest1(){
  ssd.fillScreen(DF_GDL_BLACK);
  ssd.setCursor(0, 0);
  ssd.setTextColor(DF_GDL_RED);
  ssd.setTextSize(1);
  ssd.println("hello, world!");
}

void testLines1(uint16_t color){
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = ssd.width(),
                h = ssd.height();

  ssd.fillScreen(DF_GDL_BLACK);
  
  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) ssd.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) ssd.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  ssd.fillScreen(DF_GDL_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  for(x2=0; x2<w; x2+=6) ssd.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) ssd.drawLine(x1, y1, x2, y2, color);

  ssd.fillScreen(DF_GDL_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  for(x2=0; x2<w; x2+=6) ssd.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) ssd.drawLine(x1, y1, x2, y2, color);

  ssd.fillScreen(DF_GDL_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) ssd.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) ssd.drawLine(x1, y1, x2, y2, color);

}


unsigned long testFastLines1(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = ssd.width(), h = ssd.height();

  ssd.fillScreen(DF_GDL_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) ssd.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) ssd.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = ssd.width()  / 2,
                cy = ssd.height() / 2;

  ssd.fillScreen(DF_GDL_BLACK);
  n     = min(ssd.width(), ssd.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    ssd.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = ssd.width()  / 2 - 1,
                cy = ssd.height() / 2 - 1;

  ssd.fillScreen(DF_GDL_BLACK);
  n = min(ssd.width(), ssd.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    ssd.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    ssd.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = ssd.width(), h = ssd.height(), r2 = radius * 2;

  ssd.fillScreen(DF_GDL_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      ssd.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = ssd.width()  + radius,
                h = ssd.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      ssd.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = ssd.width()  / 2 - 1,
                      cy = ssd.height() / 2 - 1;

  ssd.fillScreen(DF_GDL_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    ssd.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      DF_GDL_CYAN);
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = ssd.width()  / 2 - 1,
                   cy = ssd.height() / 2 - 1;

  ssd.fillScreen(DF_GDL_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    ssd.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      DF_GDL_CYAN);
    t += micros() - start;
    ssd.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      DF_GDL_CYAN);
    yield();
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = ssd.width()  / 2 - 1,
                cy = ssd.height() / 2 - 1;

  ssd.fillScreen(DF_GDL_BLACK);
  w     = min(ssd.width(), ssd.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    ssd.drawRoundRect(cx-i2, cy-i2, i, i, i/8, DF_GDL_BLUE);
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = ssd.width()  / 2 - 1,
                cy = ssd.height() / 2 - 1;

  ssd.fillScreen(DF_GDL_BLACK);
  start = micros();
  for(i=min(ssd.width(), ssd.height()); i>20; i-=6) {
    i2 = i / 2;
    ssd.fillRoundRect(cx-i2, cy-i2, i, i, i/8, DF_GDL_BLUE);
    yield();
  }

  return micros() - start;
}


