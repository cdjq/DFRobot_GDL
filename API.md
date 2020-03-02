# GDL的API函数列表
* C++/Aduino示例教程
* 参考
    * [drawCircle](###drawCircle)<br>
    * [drawCircleHelper](###drawCircleHelper)<br>
    * [fillCircle](###fillCircle)<br>
    * [fillCircleHelper](###fillCircleHelper)<br>
    * [drawTriangle](###drawTriangle)<br>
    * [fillTriangle](###fillTriangle)<br>
    * [drawRoundRect](###drawRoundRect)<br>
    * [fillRoundRect](###fillRoundRect)<br>
    * [drawBitmap](###drawBitmap)<br>
    * [drawXBitmap](###drawXBitmap)<br>
    * [drawGrayscaleBitmap](###drawGrayscaleBitmap)<br>
    * [drawRGBBitmap](###drawRGBBitmap)<br>
    * [drawChar](###drawChar)<br>
    * [getTextBounds](###getTextBounds)<br>
    * [setTextSize](###setTextSize)<br>
    * [setFont](###setFont)<br>
    * [setCursor](###setCursor)<br>
    * [setTextColor](###setTextColor)<br>
    * [setTextWrap](###setTextWrap)<br>
    * [cp437](###cp437)<br>
	
	
## C++/Aduino示例教程
(```)
	代码
(```)
	
### drawCircle	
* C++/Arduino原型:

  `void DFRobot_GDL::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) `

* 说明:`r` 在位置绘制一个半径为r的圆`(x0, y0)`。圆的直径为`2*r+1`。`color`可以使用指定的颜色进行绘制
* 参数: 
	* `x0`,`y0`:圆心的位置。
	* `r`:定义圆的大小:Radus = `r`。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:
	

   


### drawCircleHelper
* C++/Arduino原型:

  `void GDFRobot_GDL::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color)`

* 说明:`r` 在位置绘制一个半径为r的圆`(x0, y0)`。圆的直径为`2*r+1`。`cornername`
`color`可以使用指定的颜色进行绘制
* 参数:
	*  `x0`,`y0`:圆心的位置。
	* `r`:定义圆的大小:Radus = `r`。
	* `cornername`:
	* `color`:定义绘制颜色。
* 返回值:无
* 例:

### fillCircle	
* C++/Arduino原型: 

  `void DFRobot_GDL::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)`

* 说明:
`r` 在位置绘制一个半径为r的实心圆`(x0, y0)`。圆的直径为`2*r+1`。`color`可以使用指定的颜色进行绘制
* 参数:
	* `x0`,`y0`:圆心的位置。
	* `r`:定义圆的大小:Radus = `r`。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:


### fillCircleHelper	
* C++/Arduino原型:

  `void DFRobot_GDL::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color)`	

* 说明:`r` 在位置绘制一个半径为r的实心圆`(x0, y0)`。圆的直径为`2*r+1`。`cornername`
`color`可以使用指定的颜色进行绘制
* 参数:
    * `x0`,`y0`:圆心的位置。
	* `r`:定义圆的大小:Radus = `r`。
	* `cornername`:
	* `color`:定义绘制颜色。
* 返回值:无
* 例:   

 
### drawTriangle	
* C++/Arduino原型:

  `void DFRobot_GDL::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color)`

* 说明:绘制一个空心三角形。参数为16位，并且多边形被裁剪​​为显示的大小。绘制了多个多边形，
以便它们完全匹配而没有重叠：绘制多边形的左侧，不绘制右侧。上侧只有在平的情况下才可以绘制。
* 参数:
    * `x0`:X位置点0。
    * `y0`:X位置点0。	
	* `x1`:X位置点1。
	* `y1`:X位置点1。
	* `x2`:X位置点2。
	* `y2`:X位置点2。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:

  
### fillTriangle	
* C++/Arduino原型:

  `void DFRobot_GDL::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color)`  

* 说明:绘制一个实心三角形。参数为16位，并且多边形被裁剪​​为显示的大小。绘制了多个多边形，
以便它们完全匹配而没有重叠：绘制多边形的左侧，不绘制右侧。上侧只有在平的情况下才可以绘制。
* 参数:
    * `x0`:X位置点0。
    * `y0`:X位置点0。	
	* `x1`:X位置点1。
	* `y1`:X位置点1。
	* `x2`:X位置点2。
	* `y2`:X位置点2。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:

### drawRoundRect	
* C++/Arduino原型:

  `void DFRobot_GDL::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color)`

* 说明:  从x / y位置（左上边缘）开始绘制一个具有圆形边缘的空心框/框架。盒子/框架有width w和height h。框的某些部分可以在显示边界之外。边缘具有半径r。要求w >= 2*(r+1)和h >= 2*(r+1)。不检查此条件。如果w或h小于，则行为未定义2*(r+1)。此过程使用当前的颜色索引绘制框。
对于单色显示器，颜色索引0将清除一个像素，颜色索引1将设置一个像素。
* 参数:
    * `x`:左上边缘的X位置。
    * `y`:左上边缘的Y位置。	
	* `w`:矩形的宽度。
	* `h`:矩形的高度。
	* `r`:四个边缘的半径。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:

  
### fillRoundRect	
* C++/Arduino原型:

  `void DFRobot_GDL::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color)`  

* 说明:  
从x / y位置（左上边缘）开始绘制一个具有圆形边缘的实心框/框架。盒子/框架有width w和height h。框的某些部分可以在显示边界之外。边缘具有半径r。要求w >= 2*(r+1)和h >= 2*(r+1)。不检查此条件。如果w或h小于，则行为未定义2*(r+1)。此过程使用当前的颜色索引绘制框。对于单色显示器，颜色索引0将清除一个像素，颜色索引1将设置一个像素。
* 参数:
    * `x`:左上边缘的X位置。
    * `y`:左上边缘的Y位置。	
	* `w`:矩形的宽度。
	* `h`:矩形的高度。
	* `r`:四个边缘的半径。
	* `color`:定义绘制颜色。
* 返回值:无
* 例:

### drawBitmap
* C++/Arduino原型:

  `void DFRobot_GDL::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h, uint16_t color)`

  `void DFRobot_GDL::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h, uint16_t color, uint16_t bg)`

  `void DFRobot_GDL::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color)`

  `void DFRobot_GDL::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color, uint16_t bg)`

* 说明：`drawBitmap`重载了多个函数。在指定的`x`,`y`位置（位图的左上角）绘制一个单色位图。位图的某些部分可能不在显示边界之内。位图由数组指定`bitmap`或者是指向位图开始的指针。`w`,`h`为位图的高度和宽度；`color`画16位5-6-5的单色图片颜色，`bg`画16位5-6-5的背景颜色。
* 参数：
    * `x`:X位置。
    * `y`:Y位置。
    * `bitmap`:位图数组或者是指向位图开始的指针。
    * `w`:位图的宽度。
    * `h`:位图的高度。
    * `color`:画16位5-6-5的单色图片颜色。
    * `bg`:画16位5-6-5的背景颜色。
* 返回值： 无




### drawXBitmap 
* C++/Arduino原型:
 
    `void DFRobot_GDL::drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h, uint16_t color)`
* 说明：`drawXBitmap`绘制`progmemm`驻留的XBitMap文件`(*.xbm)`，从`GIMP`导出。从GIMP导出到*.xbm、重命名*.xbm到*.c并在编辑器中打开。C数组可以直接与此函数一起使用。该函数没有ram驻留版本;如果生成位图在RAM中，使用drawBitmap()定义的格式并调用它。在指定的`x`,`y`位置（位图的左上角）绘制一个单色位图。位图的某些部分可能不在显示边界之内。位图由数组指定`bitmap`或。`w`,`h`为位图的高度和宽度；`color`画16位5-6-5的单色图片颜色。
* 参数：
    * `x`:X位置。
    * `y`:Y位置。
    * `bitmap`:位图数组。
    * `w`:位图的宽度。
    * `h`:位图的高度。
    * `color`:绘制16位5-6-5的单色图片颜色。
* 返回值： 无



### drawGrayscaleBitmap
* C++/Arduino原型:
    
    `void DFRobot_GDL::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h)`

    `void DFRobot_GDL::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h)`

    `void DFRobot_GDL::drawGrayscaleBitmap(int16_t x, int16_t y,const uint8_t bitmap[], const uint8_t mask[],int16_t w, int16_t h)`

    `void DFRobot_GDL::drawGrayscaleBitmap(int16_t x, int16_t y,uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h)`
* 说明：`drawGrayscaleBitmap`重载了多个函数,它旨在指定的位置(x,y)绘制一个progmemeresident 8位图像(灰度)。
特别适用于8位显示设备，如IS31FL3731;不进行减色/展开。在指定的`x`,`y`位置（位图的左上角）绘制一个8位位图。位图的某些部分可能不在显示边界之内。位图由数组指定`bitmap`或者是指向位图开始的指针；`mask`是带掩码位图的字节数组。`w`,`h`为位图的高度和宽度。
* 参数：
    * `x`:X位置。
    * `y`:Y位置。
    * `bitmap`:灰阶位图数组或者是指向灰阶位图开始的指针。
    * `mask`:带掩码位图的字节数组。
    * `w`:位图的宽度。
    * `h`:位图的高度。
* 返回值： 无

### drawRGBBitmap
* C++/Arduino原型:

    `void DFRobot_GDL::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],int16_t w, int16_t h)`

    `void DFRobot_GDL::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,int16_t w, int16_t h)`

    `void DFRobot_GDL::drawRGBBitmap(int16_t x, int16_t y,const uint16_t bitmap[], const uint8_t mask[],int16_t w, int16_t h)`

    `void drawRGBBitmap(int16_t x, int16_t y,uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h)`
* 说明：`drawRGBBitmap`重载了多个函数。在指定的`x`,`y`位置（位图的左上角）绘制ram驻留的16位图像(RGB 5/6/5)；用于16位显示设备；未进行颜色还原。位图的某些部分可能不在显示边界之内。位图由数组指定`bitmap`或者是指向位图开始的指针；`mask`是带掩码位图的字节数组。`w`,`h`为位图的高度和宽度。
* 参数：
    * `x`:X位置。
    * `y`:Y位置。
    * `bitmap`:位图数组或者是指向位图开始的指针。
    * `mask`:是带掩码位图的字节数组。
    * `w`:位图的宽度。
    * `h`:位图的高度。
* 返回值： 无


### drawChar
* C++/Arduino原型:

    `void DFRobot_GDL::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,uint16_t bg, uint8_t size)`

    `void DFRobot_GDL::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,uint16_t bg, uint8_t size_x,uint8_t size_y)`
* 说明：`drawChar`旨在画一个字符，它也进行了重载。在指定的`x`,`y`位置（字符的左上角）绘制字符。`size`为设置字体放大等级。`size_z`和`size_y`旨在自定义设置字体的长和宽的放大等级。
* 参数：
    * `x`:X位置。
    * `y`:Y位置。
    * `c`:8位字符索引字符(类似于ascii)。
    * `color`:绘制16位5-6-5的字符颜色
    * `bg`:绘制16位5-6-5的背景颜色。
    * `size`:字体放大等级(1-6级)，1是“原始”大小。
    * `size_z`:字体放大等级在x轴(1-6级)，1是“原始”大小。
    * `size_y`:字体放大等级在y轴(1-6级)，1是“原始”大小。
* 返回值： 无

### getTextBounds
* C++/Arduino原型:

    `void DFRobot_GDL::getTextBounds(const char *string, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)`

    `void DFRobot_GDL::getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)`

    `void DFRobot_GDL::getTextBounds(const String &str, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)`

* 说明：`getTextBounds`帮助程序，用于确定具有当前字体/大小的字符串的大小。传递字符串和光标位置，返回UL角和W,H。它也进行了重载。
* 参数：
    * `string`:要测量的ascii字符串。
    * `s`:要测量的闪存ascii字符串。
    * `str`:测量ascii字符串(作为arduino字符串()类)。
    * `x`:当前光标X。
    * `y`:当前光标y。
    * `x1`:边界X坐标，由函数设置。
    * `y1`:边界y坐标，由函数设置。
    * `w`:边界宽度，由函数设置。
    * `h`:边界高度，由函数设置
* 返回值： 无

### setTextSize
* C++/Arduino原型:

    `void DFRobot_GDL::setTextSize(uint8_t s)`

    `void DFRobot_GDL::setTextSize(uint8_t sx, uint8_t sy)`

* 说明：`setTextSize`旨设置文本“放大”大小。`size`为设置字体放大等级；长和宽由函数设置。`sx`和`sy`旨在自定义设置字体的长和宽的放大等级。
* 参数：
    * `s`:想要的文本大小。1是默认的6x8, 2是12x16, 3是18x24，等等。
    * `sx`:sx所需的文本宽度放大水平在x轴。1是默认的。
    * `sy`:sx所需的文本宽度放大水平在y轴。1是默认的。。
* 返回值： 无
   
### setFont
* C++/Arduino原型:

    `void DFRobot_GDL::setFont(const GFXfont *f = NULL) `

* 说明：`setFont`旨当打印()时设置字体显示时，可以自定义或默认。`size`为设置字体放大等级；长和宽由函数设置。`sx`和`sy`旨在自定义设置字体的长和宽的放大等级。
* 参数：
    * `f`:GFXfont对象，如果为空，使用内置的6x8字体。

* 返回值： 无

### setCursor
* C原型:

    `void setCursor(int16_t x, int16_t y)`

* 说明：`setCursor`设置光标位置。
* 参数：
    * `x`:X坐标(像素)。
    * `y`:Y坐标(像素)。

* 返回值： 无

### setTextColor
* C原型:

    `void setTextColor(uint16_t c)`
    `void setTextColor(uint16_t c, uint16_t bg)`

* 说明：`setTextColor`设置文本字体颜色与透明背景或者设置文本字体颜色自定义背景颜色。用于“透明”背景，背景和前景设置为相同的颜色，而不是使用单独的标志。
* 参数：
    * `c`:设置16位5-6-5颜色绘制文本。
    * `bg`:设置16位5-6-5颜色绘制背景/填充。

* 返回值： 无

### setTextWrap
* C原型:

    `void setTextWrap(uint16_t c)`

* 说明：`setTextColor`设置文本对于屏幕宽度是否太长自动换行(否则剪切）。
* 参数：
    * `c`:真用于自动换行，假用于剪裁。

* 返回值： 无

### cp437
* C原型:

    `void cp437(boolean x=true)`

* 说明：`setTextColor`启用(或禁用)代码页437兼容的字符集。在glcdfont.c中有一个最长时间的错误—1字符(#176，'light shade'块)丢失——这个去掉它后面每个字符的索引。但是很多代码都是用错误代码编写的字符索引。默认情况下，库使用原始文件“错误的”行为和旧的草图仍然有效。通过'true'来使用正确的CP437字符值在您的代码中。
* 参数：
    * `c`:true = 启用(新行为)，false = 禁用(旧行为)。

* 返回值： 无


