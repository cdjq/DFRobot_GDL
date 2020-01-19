# DFRobot_GDL
DFRobot_GDL 是一个跨平台，集显示、触摸、UI于一体的综合显示交互框架。<br>
支持多种显示IC和触摸IC。用户可以用GDL驱动各种各样的显示屏，如彩屏、黑白屏、墨水屏等等。<br>

## Table of Contents
* [Summary](#summary)
* [Text](#text)
* [Installation](#installation)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits) 

## summary

 * 支持多种触摸IC和显示IC以及多种分辨率。<br>
 * 支持多种显示功能；支持画点、画线、画圆等等;支持位图的显示;支持多种字库;支持用户自定义字体功能等。<br>
 * 支持多种触摸功能：手势操作、单击、双击、长按等。<br>
 * 支持多种UI功能：滑条,进度条,文本框,按钮,开关，tableView等。<br>

## text

### 示功能<br>
GDL显示框架继承自Adafruit的GFX框架，链接:https://github.com/adafruit/Adafruit-GFX-Library<br>
支持非常多的功能，下图可以详细查看<br>

GDL          |     Uno      |   Leonardo    |     ESP32     |    ESP8266    |     m0         |     BK7251      
-----------  | :----------: |  :----------: |  :----------: |  :----------: | :------------: |   ------------
几何图形     |      √       |       √       |      √        |       √       |       √        |  
BMP图形解码  |      √       |       √       |      √        |       √       |       √        |  
多种字库     |      √       |       √       |      √        |       √       |       √        |
ttf字库      |      √       |       √       |      √        |       √       |       √        |
单点触摸     |      √       |       √       |      √        |       √       |       √        |
多点触摸     |              |               |               |               |                |
手势操作     |      √       |       √       |      √        |       √       |       √        |
滑条         |      √       |       √       |      √        |       √       |       √        |
进度条       |      √       |       √       |      √        |       √       |       √        | 
文本框       |      √       |       √       |      √        |       √       |       √        | 
按钮、开关   |      √       |       √       |      √        |       √       |       √        | 
tableView    |      √       |       √       |      √        |       √       |       √        |     

### 显示IC<br>

GDL目前支持多种的显示驱动IC和分辨率，下图查看目前可用的驱动。<br>

GDL：显示IC        | ST7789       | ILI9341   
------------------ | :----------: | ------------
分辨率：240x240    |      √       |               | 
分辨率：240x320    |      √       |      √        | 



### 触摸<br>
GDL支持多种触摸IC，下图查看目前支持的触摸驱动：<br>


GDL：触摸IC      |  XPT2046     |    GT911     |   GT5688
---------------- | :----------: | :----------: |------------
Work Well        |      √       |     √        |     √

## installation
要使用此库，请首先下载该库文件，将其粘贴到\ Arduino \ libraries目录，然后打开examples文件夹并在该文件夹中运行demo。<br>

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


  
