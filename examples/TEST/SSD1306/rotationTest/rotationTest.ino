#include "DFRobot_GDL.h"

DFRobot_SSD1306_128x32_HW_IIC oled;
void setup(void) {
  Serial.begin(9600);
  oled.begin();
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
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(0);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.setCursor(0, 0);
    oled.setTextColor(SET_COLOR);
    oled.setTextSize(1);
    oled.println("Hello World!");
    oled.setTextSize(2);
    oled.print(1234.567);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif
    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateFillcircle(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(0);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.fillCircle(10, 30, 10, SET_COLOR);

    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateDrawcircle(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(0);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawCircle(10, 30, 10, SET_COLOR);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif
  
    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateFillrect(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.fillRect(10, 20, 10, 20, SET_COLOR);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateDrawrect(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawRect(10, 20, 10, 20, SET_COLOR);
 
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateFastline(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawFastHLine(0, 20, oled.width(), SET_COLOR);
    oled.drawFastVLine(20, 0, oled.height(), SET_COLOR);

    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateLine(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawLine(oled.width()/2, oled.height()/2, 0, 0, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotatePixel(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawPixel(10,20, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateTriangle(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawTriangle(20, 10, 10, 30, 30, 30, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateFillTriangle(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.fillTriangle(20, 10, 10, 30, 30, 30, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateRoundRect(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawRoundRect(20, 10, 25, 15, 5, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateFillRoundRect(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.fillRoundRect(20, 10, 25, 15, 5, SET_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateChar(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.drawChar(25, 15, 'A', SET_COLOR, SET_COLOR, 1);
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}

void rotateString(void) {
  for (uint8_t i=0; i<2; i++) {
    oled.fillScreen(CLR_COLOR);
    #ifdef ARDUINO_SAM_ZERO
    SerialUSB.println(oled.getRotation(), DEC);
    #else
    Serial.println(oled.getRotation(), DEC);
    #endif

    oled.setCursor(8, 25);
    oled.setTextSize(1);
    oled.setTextColor(SET_COLOR);
    oled.print("Hi, DFRobot!");
    #ifdef ARDUINO_SAM_ZERO
    while (!SerialUSB.available());
    SerialUSB.read();  SerialUSB.read();  SerialUSB.read();
    #else
    while (!Serial.available());
    Serial.read();  Serial.read();  Serial.read();
    #endif

    oled.setRotation(oled.getRotation()+1);
    oled.update();
  }
}
