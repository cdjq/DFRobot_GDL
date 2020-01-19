#include "DFRobot_GDL.h"
#if defined(ESP8266)||defined(ESP32)
#define DC  D3
#define CS  D4
#define RST D5
#define BL  D6
#else
#define DC  2 
#define CS  3
#define RST 5
#define BL  6
#endif

DFRobot_ST7735S_80x160_HW_SPI tft(DC,CS,RST,BL);
void setup(void) {
  Serial.begin(9600);
  tft.begin();
  #ifdef ARDUINO_SAM_ZERO
  SerialUSB.println("打开串口，选择“回车”，点击发送即可开始旋转测试：");
  #else
  Serial.println("打开串口，选择“回车”，点击发送即可开始旋转测试：");
  #endif
}

void loop(void) {
  rotateLine();
  rotateText();
  rotatePixel();
  rotateFastline();
  rotateDrawrect();
  rotateFillrect();
  rotateDrawcircle();
  rotateFillcircle();
  rotateTriangle();
  rotateFillTriangle();
  rotateRoundRect();
  rotateFillRoundRect();
  rotateChar();
  rotateString();
}

void rotateText() {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.setCursor(0, 0);
    tft.setTextColor(COLOR_RGB565_RED);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(COLOR_RGB565_YELLOW);
    tft.setTextColor(COLOR_RGB565_BLUE);
    tft.setTextSize(2);
    tft.print(1234.567);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif
    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateFillcircle(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.fillCircle(10, 30, 10, COLOR_RGB565_YELLOW);

    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateDrawcircle(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawCircle(10, 30, 10, COLOR_RGB565_YELLOW);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif
  
    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateFillrect(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.fillRect(10, 20, 10, 20, COLOR_RGB565_GREEN);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateDrawrect(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawRect(10, 20, 10, 20, COLOR_RGB565_GREEN);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateFastline(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawFastHLine(0, 20, tft.width(), COLOR_RGB565_RED);
    tft.drawFastVLine(20, 0, tft.height(), COLOR_RGB565_BLUE);

    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateLine(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawLine(tft.width()/2, tft.height()/2, 0, 0, COLOR_RGB565_RED);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotatePixel(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawPixel(10,20, COLOR_RGB565_WHITE);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateTriangle(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawTriangle(20, 10, 10, 30, 30, 30, COLOR_RGB565_GREEN);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateFillTriangle(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.fillTriangle(20, 10, 10, 30, 30, 30, COLOR_RGB565_RED);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateRoundRect(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawRoundRect(20, 10, 25, 15, 5, COLOR_RGB565_BLUE);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateFillRoundRect(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.fillRoundRect(20, 10, 25, 15, 5, COLOR_RGB565_CYAN);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateChar(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.drawChar(25, 15, 'A', COLOR_RGB565_WHITE, COLOR_RGB565_WHITE, 1);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}

void rotateString(void) {
  for (uint8_t i=0; i<4; i++) {
    tft.fillScreen(COLOR_RGB565_BLACK);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(tft.getRotation(), DEC);
    #else
    Serial.println(tft.getRotation(), DEC);
    #endif

    tft.setCursor(8, 25);
    tft.setTextSize(1);
    tft.setTextColor(COLOR_RGB565_WHITE);
    tft.print("Hi, DFRobot!");
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    tft.setRotation(tft.getRotation()+1);
  }
}
