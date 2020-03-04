# DFRobot_GDL
DFRobot_GDL 是一个支持多种MCU，集显示、触摸、UI于一体的综合显示交互框架。<br>
支持多种显示IC和触摸IC。用户可以用GDL驱动各种各样的显示屏，如彩屏、黑白屏、墨水屏等等。<br>

GDL旨在让用户能更简单快速上手和快速学习；从而实现多种显示效果，能让你的项目更加丰富多彩。

## GDL软件
GDL集成了大量的功能组件，wiki中包含这些组件的使用方法<br>
#### 查看wiki
* 点击[此处查看中文wiki](https://github.com/cdjq/DFRobot_GDL/wiki/%E4%B8%AD%E6%96%87WIKI)<br>
* 点击[此处查看英文wiki](https://github.com/cdjq/DFRobot_GDL/wiki/English-WIKI)

#### 基础显示
* 点、线、几何图形等的实现<br>
[效果图]
* 图形解码(BMP)<br>
[效果图]
* 内置字库<br>
[效果图]
* ttf字体（用户自定义）<br>
[效果图]

#### 触摸功能
* 单击/双击<br>
[效果图]
* 长按/滑动<br>
[效果图]
* 手势操作(单点手势和多点手势)<br>
[效果图]

#### UI功能
* 滑条<br>
[效果图]
* 进度条<br>
[效果图]
* 文本框<br>
[效果图]
* 按键<br>
[效果图]
* 表格视图<br>
[效果图]
* 坐标系控件<br>
[效果图]

## GDL兼容性

#### 支持MCU
GDL可以支持多种MCU，下表可以查看支持的MCU型号。

GDL          |     Uno      |   Leonardo    |     ESP32     |    ESP8266    |     m0         |     BK7251      
-----------  | :----------: |  :----------: |  :----------: |  :----------: | :------------: |   ------------
几何图形     |      √       |       √       |      √        |       √       |       √        |  
BMP图形解码  |      √       |       √       |      √        |       √       |       √        |  
内置字库     |      √       |       √       |      √        |       √       |       √        |
ttf字库      |      √       |       √       |      √        |       √       |       √        |
单点触摸     |      √       |       √       |      √        |       √       |       √        |
多点触摸     |              |               |               |               |                |
手势操作     |      √       |       √       |      √        |       √       |       √        |
滑条         |      √       |       √       |      √        |       √       |       √        |
进度条       |      √       |       √       |      √        |       √       |       √        | 
文本框       |      √       |       √       |      √        |       √       |       √        | 
Button       |      √       |       √       |      √        |       √       |       √        | 
tableView    |      √       |       √       |      √        |       √       |       √        |     

#### 显示IC
GDL目前支持多种的显示驱动IC和分辨率，我们支持DFRobot系列屏幕和Adafruit系列屏幕，下表查看目前可用的驱动。<br>
中文链接，请点击[此处](https://docs.qq.com/sheet/DWGRwa05PV3NSRGtI?c=B11A0A0)。<br>
英文连接，请点击[此处]()。

 

#### 触摸<br>
GDL支持多种触摸IC，下图查看目前支持的触摸驱动：<br>


GDL：触摸IC      |  XPT2046     |    GT911     |   GT5688
---------------- | :----------: | :----------: |------------



## 安装GDL固件
GDL能满足不同软件开发水平的人使用。对于初学者，您不需要很高的Arduino或软件开发经验。
就可以实现炫酷的显示效果。随时在公共实验室或github上的Wiki页面上发布您的软件问题。

1. 下载Arduino IDE
1. 从[github](网址)下载GDL代码
1. 使用`Arduino IDE`从下载的文件中打开“basicTest.ino”
1. 连接您的`Arduino Uno`开发板
1. 选择工具>板子：`Arduino Uno`和工具>端口：选择你的Arduino开发板
1. 单击“验证”，然后将软件“上传”到您的开发板上

## 教学
这是一个有120分钟的教学视频；旨在让初学者快速入门。

1. GDL简介----5分钟

1. GDL下载安装及基础使用 -5分钟

1. GDL图形显示--20分钟

1. GDL文字显示--10分钟

1. GDL图片显示--5分钟

1. GDL使用ttf字库--10分钟

1. GDL Touch简介--5分钟

1. GDL-Touch基本操作--5分钟

1. GDL-Touch手势操作--10分钟

1. GDL UI简介--5分钟

1. GDL-UI-Text控件--5分钟

1. GDL-UI-滑条/进度条控件--5分钟

1. GDL-UI-Button控件--5分钟

1. GDL-UI-Tableview控件--5分钟

1. GDL-UI-直角坐标系控件--5分钟
 

## 常见问题

1.问：为什么有的示例程序在Arduino UNO/Leonardo上运行不了<br>
&nbsp;&nbsp; 答：因为Arduino UNO/Leonardo内存大小，无法存储下整个程序；您可以换一个内存较大的主控，如Firebettle-ESP32等。我们再每一个ino的头文件都有对应的说明，大家可以详细阅读。

## 关于分支
**master**是当前的稳定版本

**其他分支**都是开发版本，用于存放未经完全测试的实验版本，使用者可以试用并通过issues提出改进意见或反馈bug

## 待办事项清单
- [ ]多点手势触摸功能
- [ ]坐标系控件


## 联系
GDL团队的电子邮件地址<br>
* 阿贾克斯Ajax.zhong@dfrobot.com

## 感谢
* 内部集成了Adafruit的GFX库，[GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library)库地址
* 字体部分参考了u8g2的编码格式，[u8g2](https://github.com/olikraus/u8g2)库地址
