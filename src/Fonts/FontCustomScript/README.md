在使用setup.py脚本生成自定义字体之前，需要做如下准备：
一、环境搭建
登录网址https://www.python.org/downloads/，下载python3.6及以上版本；
安装完毕后，你需要用下列命令安装python第三方依赖包
pip3 install numpy
pip install freetype-py 

二、生成自定义字体
step1：将TTF字体文件存放在ttf文件夹里，例如：SIMKAI.TTF（简体字 楷体）
step2: 在text.txt文件中输入你想生成的字符，例如：你好，世界！
step3：打开config.txt文件，配置生成字体文件的名字前缀和字体大小：
FontFileNamePre：生成的字体文件名前缀
FontSizeList ：生成的字体的大小列表，如果为空[]，则默认生成12,18,24,36,48,72大小的文件, 如果是汉字，不要小于12
    其中FontFileNamePre代表文件名的前缀，如果为default，则代表无前缀
    例1：如果FontFileNamePre = default
             FontSizeList = [12]
    则会生成一个名字为SIMYOUFont12pt.h的文件
    例2：如果FontFileNamePre = English
             FontSizeList = [12]
    则会生成一个名字为EnglishSIMYOUFont12pt.h的文件
    例3：如果FontFileNamePre = English
             FontSizeList = [12,24]
    则会生成名字为EnglishSIMYOUFont12pt.h和EnglishSIMYOUFont24pt.h的文件
生成字体文件命名和后缀 = FontFileNamePre + TTF文件名 + Font + size + pt + .h
    其中FontFileNamePre只能是英文字符,size及字体的大小
step4: 运行setup.py脚本，会在font文件夹生成一系列后缀名为.h的字体文件，并弹出一个font.txt的文本，再进行以下步骤，即可在屏上显示：你好，世界！
    a.将font文件夹里的文件复制到DFRobot_GDL\src\Fonts\Fonts目录下；
    b.将弹出的font.txt的内容粘贴到DFRobot_GDL\src\Fonts\DFRobot_Font.h文件中;
    c.打开Arduino IDE，构造屏对象，如tft，调用tft.setFont(&SIMKAIFont48pt);
    d.调用tft.println("你好，世界！"),此时即可在屏上显示"你好，世界！"
注意：UNO等主控的ROM和RAM比较少，如果你一次生成的字体多，会因内存不足，而报错
