# DFRobot_GDL
DFRobot_GDL is a cross-platform display interactive framework that integrates display, touch and UI.<br>
It supports a wide range of display ICs and touch ICs. So that users can use this library to drive a wide variety of displays, such as color screen, black and white screen, ink screen and so on.
<br>

## Table of Contents
* [Summary](#summary)
* [Text](#text)
* [Installation](#installation)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits) 

## summary

 * Supports multiple touch and display ICs as well as multiple resolutions.<br>
 * Multiple display function;Supports for drawing points, lines, circles, etc.;Supports bitmap display and a 
 * variety of font libraries and user-defined font and so on.<br>
 * Supports a variety of display functions: supports drawing points, drawing lines, drawing circles, etc. 
 * Supports various touch functions: gesture operation, click, double-click, long-press. <br>
 * Supports various UI functions: slider, progress bar, text box, button, switch, tableView, etc<br>

## text

### Dispaly Function <br>
The GDL display framework inherits from Adafruit's GFX framework, address: https://github.com/adafruit/Adafruit-GFX-Library<br>
It has many funcions, shown as below: <br>

GDL          |     Uno      |   Leonardo    |     ESP32     |    ESP8266    |     m0         |     BK7251      
-----------  | :----------: |  :----------: |  :----------: |  :----------: | :------------: |   ------------
Geometric figure     |      √       |       √       |      √        |       √       |       √        |  
BMP image decoding  |      √       |       √       |      √        |       √       |       √        |  
Various font libraries     |      √       |       √       |      √        |       √       |       √        |
ttf font library      |      √       |       √       |      √        |       √       |       √        |
Single-touch    |      √       |       √       |      √        |       √       |       √        |
Multi-touch     |              |               |               |               |                |
Gesture operation      |      √       |       √       |      √        |       √       |       √        |
Slider         |      √       |       √       |      √        |       √       |       √        |
Progress bar       |      √       |       √       |      √        |       √       |       √        | 
text box       |      √       |       √       |      √        |       √       |       √        | 
button, switch   |      √       |       √       |      √        |       √       |       √        | 
tableView    |      √       |       √       |      √        |       √       |       √        |     

### Display IC<br>

GDL currently supports several display driver ICs and resolutions. As shown in the figure below:<br>

GDL：display IC        | ST7789       | ILI9341   
------------------ | :----------: | ------------
resolution：240x240    |      √       |               | 
resolution：240x320    |      √       |      √        | 



### Touch<br>
GDL supports a variety of touch ICs. As shown in the figure below:<br>


GDL：touch IC      |  XPT2046     |    GT911     |   GT5688
---------------- | :----------: | :----------: |------------
Work Well        |      √       |     √        |     √

## installation
To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## ompatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -------
Arduino Uno        |      √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
ESP8266            |      √       |              |             | 
M0                 |      √       |              |             |
BK7252             |      √       |              |             |

## 产品链接（链接到英文商城）

## History

- Data 2020-1-8
- Version V1.0

## Credits

Written by(Ajax.zhong@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))


  
