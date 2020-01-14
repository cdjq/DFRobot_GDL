#ifndef __DFROBOT_ST7735S_H
#define __DFROBOT_ST7735S_H

#define ST7735S_IC_WIDTH  132
#define ST7735S_IC_HEIGHT  162
#define ST7735S_COLSET  0x2A
#define ST7735S_RAWSET  0x2B
#define ST7735S_RAMWR   0x2C
#define ST7735S_MADCTL  0x36
#define ST7735S_MADCTL_RGB 0x00
#define ST7735S_INVOFF  0x20
#define ST7735S_INVON   0x21

static const uint8_t PROGMEM DFRobot_ST7735S_initCmd[] = {
  //cmd delayFlag/argsNum argsValue 延时（超过255）延时/255
//flag
0x01, 0x11, 0x80, 0x00, 120,/*0x11：退出睡眠模式命令，0x80：最高位代表是否延时，
1代表延时，0代表不延时，后1位代表命令后面参数的个数，0代表没有参数
0x00:表示延时的时255的倍数，比如延时120ms，可写成0x00， 120
实际延时时间= 0x00*255 + 120ms*/
0x01, 0x21, 0,//0x21打开反转显示，无参数，不延时
0x01, 0xB1, 3, 0x05, 0x3A, 0x3A,//帧速率控制(正常模式)(GM[1:0]00)
0x01, 0xB2, 3, 0x05, 0x3A, 0x3A,//帧速率控制（空闲模式）
0x01, 0xB3, 6, 0x05, 0x3A, 0x3A, 0x05, 0x3A, 0x3A,//帧速率控制（局部模式）
0x01, 0xB4, 1, 0x03,//反转控制
0x01, 0xC0, 3, 0x62, 0x02, 0x04,//功耗控制
0x01, 0xC1, 1, 0xC0,//功耗控制
0x01, 0xC2, 2, 0x0D, 0x00,//功耗控制
0x01, 0xC3, 2, 0x8D, 0x6A,//功耗控制
0x01, 0xC4, 2, 0x8D, 0xEE,//功耗控制
0x01, 0xC5, 1, 0x0E,//VCOM
0x01, 0xE0, 16,0x10, 0x0E, 0X02, 0X03, 0X0E, 0X07, 0x02, 0x07, 0X0A, 0X12, 0X27, 0X37, 0X00, 0X0D, 0X0E, 0x10,
0x01, 0xE1, 16,0x10, 0x0E, 0X03, 0X03, 0X0F, 0X06, 0x02, 0x08, 0X0A, 0X13, 0X26, 0X36, 0X00, 0X0D, 0X0E, 0x10,
0x01, 0x3A, 1, 0x05,//颜色模式设置
0x01, 0x36, 1, 0xC8,//(0x36)MADCTL内存数据访问控制命令
0x01, 0x29, 0,
0x00
//第一列 0x01和0x00用来区分数组是否结束
//格式:flag-cmd-argNs-args-(time)
};

#endif