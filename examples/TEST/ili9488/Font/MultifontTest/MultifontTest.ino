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
uint16_t unicodeArray[0];
DFRobot_ILI9488_320x480_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setTextColor(COLOR_RGB565_RED);
  screen.setTextSize(1);
  screen.setCursor(0,0);
  screen.setTextWrap(true);
  bulidinTobulidin();
  delay(5000);
  bulidinTocustom();
  delay(5000);
  customTocustom();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void bulidinTobulidin(){
  /*内置默认字体-》默认字体,替换大小*/
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setTextColor(COLOR_RGB565_RED,COLOR_RGB565_WHITE);
  screen.setCursor(0,0);
  screen.setFont();
  screen.setTextSize(1);
  screen.print("GGGGGGggggggggGGGGGGggggggggGGGGGGggggg");
  screen.setFont();
  screen.print("JJJjjjjjjjjjj");
  /*内置默认字体-》除默认字体之外的其他字体,替换大小*/
  screen.setFont(&FreeMono24pt7b);
  screen.print("jabcda");
  screen.setFont(&FreeMono12pt7b);
  screen.print("jabcdadwfgkfffffffffffffffffffffffffff");
  screen.setFont(&FreeMono24pt7b);
  screen.print("jabcda");
  screen.setFont();
  screen.print("JJJjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj");
}
void bulidinTocustom(){
  /*内置默认字体-》自定义字体,替换大小*/
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setTextColor(COLOR_RGB565_RED,COLOR_RGB565_WHITE);
  screen.setCursor(0,0);
  screen.setFont();
  screen.setTextSize(1);
  screen.setFont(&SIMKAIFont48pt);
  screen.print("你好，世界！");
  /*自定义字体-》除默认字体之外的其他字体,替换大小*/
  screen.setFont(&FreeMono24pt7b);
  screen.print("jabcda");
  screen.setFont(&SIMKAIFont12pt);
  screen.print("你好，世界！");
  screen.setFont();
  screen.print("JJJjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj");
  screen.setFont(&SIMKAIFont12pt);
  screen.print("你好，世界！");
  screen.setFont(&FreeMono24pt7b);
  screen.print("jabcdajjjjjjjjjjjjj");
}
void customTocustom(){
  /*自定义字体-》自定义字体,替换大小*/
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setTextColor(COLOR_RGB565_RED,COLOR_RGB565_WHITE);
  screen.setCursor(0,0);
  Serial.println(screen.getCursorX());
  Serial.println(screen.getCursorY());
  screen.setFont(&SIMKAIFont48pt);
  screen.print("你好，世界！");
  screen.setFont(&SIMKAIFont12pt);
  screen.print("你好，世界！");
   screen.setFont(&SIMKAIFont48pt);
  screen.print("你好，世界！");
}
