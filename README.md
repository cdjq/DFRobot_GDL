# DFRobot_GDL
DFRobot_GDL 是一个综合显示库，集显示、触摸、UI于一体。
显示

触摸

UI
DFRobot_UI
  DFRobot_UI 是一个用户界面显示库，该库包含了一些简单的控件，可以使用户通过控件实现人机交互，控件包括有：滑条,进度条,文本框,按钮,开关，tableView<br>
  用户可以自己定义控件的一些参数，如按钮，用户可以定义按钮的样式，大小，颜色，按钮的名字，位置等<br>
  并且该库还提供了识别手势的方法，可以识别的手势包括：上滑,下滑,左滑,右滑,单击,双击,长按<br>
  因为该库只实现了简单的控件,该库对微控制器内存的要求很小，即使在arduino uno上面也可以使用
  如果需要太过复杂的用户界面，或者对界面有较高的要求，可以使用littlelvgl库，但相对littlelvgl而言，DFRobot_UI里面的控件使用起来比较简单，更容易上手
## 产品链接（链接到英文商城）
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

   1.在屏幕上创建一个进度条控件，用户可以自定义进度条的参数，也可以使用默认的参数，用户可以通过进度条的回调函数控制进度条的值.<br>
   2.在屏幕上创建一个按钮控件，用户可以自定义按钮的参数，示例里面创建了三个按钮A,B,C,按下A,B按钮会在文本框内显示，按下C按钮会删除文本框的一个字符.<br>
   3.在屏幕上创建一个开关，文本框和滑条控件，用户可以这些控件的参数，也可以使用默认的参数,当用户对控件操作时，会在文本框显示你当前的操作<br>
   4.在屏幕指定区域可以识别到用户所使用的手势，手势的名称会显示到文本框内<br>
   5.在屏幕上创建一个table控件，用户可以自定义进度条的参数，用户可以选择不同的页来显示不同的内容<br>
## Installation

# DFRobot_Touch
  DFRobot_Touch是一个能支持多种触摸屏IC的触摸框架，现在能够支持的触摸IC有：XPT2046,GT911,GT5688
  可以支持电容屏和电阻屏，单点，多点等不同类型的触控芯片
  支持的通信协议有IIC/SPI
  用户可以通过不同的构造函数选择不同的IC来控制不同的触摸屏
  能够支持不同的mcu