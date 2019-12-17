#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- coding: cp936 -*- 

import numpy as np
from freetype import * 
import math
import os
import codecs
import copy

BYTEBITS_MAX = 8
PIXEL_MAX = 65535 #同一种颜色的计数
FG_BG_ORDER = 2 #位图表现形式 先前景色后背景色
BG_FG_ORDER = 1  #位图表现形式 先背景色后前景色
CHINESE_FLAG = 1
ENGLISH_FLAG = 2
def configFile():#写config.txt的内容
    manul = '1'
    pwd = os.getcwd()
    src = pwd + '\\ttf'
    i = pwd.find('Fonts')
    dst = pwd[:i+len('Fonts')]
    configDict = {'AutoConfiguration':manul,'ttfSourceFloder':src,'FontTargeFloder':dst}
    Dict2 = {}
    if os.path.exists('config.txt') == False:
        fp = open('config.txt', 'w+')
        fp.close()
    fp = open('config.txt', 'r')
    List = fp.readlines()
    fp.close()
    for s in List:
        s1 = s.replace(' ','').replace('\n','')
        index = s1.find('#')#查找‘#’字符的初始位置，可以用str.index和str.find查找，区别find查找没有的字符，会返回-1，index会报错
        if index == 0:
            continue
        else:
            index = s1.find('=')
            if index != -1:
                key = s1[:index]
                val = s1[index+1:]
                index = val.find('#')
                if index != -1:
                    val = val[:index]
                if key in configDict:
                        Dict2[key] = val
    if len(Dict2) == 3 and Dict2['AutoConfiguration'] == '0':#判断目录是否存在
        src = Dict2['ttfSourceFloder']
        dst = Dict2['FontTargeFloder']
        if os.path.exists(src) and os.path.exists(dst):
            return
    a = configDict.keys()
    L = list(configDict.keys())
    fp = open('config.txt', 'w+')
    s = '#Manual configuration: 0\n' + '#Auto configuration : 1\n\n' + '#AutoConfiguration = 0\n'
    fp.write(s)
    for key in L:
        s = key + ' = '
        if isinstance(configDict[key],str):
            s +=  configDict[key] + '\n'
        else:
            s += str(configDict[key]) + '\n'
        fp.write(s)
    fp.close()


def readConfigFile():
    if os.path.exists('config.txt') == False:
        configFile()
    configDict = {'AutoConfiguration':'0','ttfSourceFloder':'0','FontTargeFloder':'0'}
    Dict2 = {}
    fp = open('config.txt', 'r')
    List = fp.readlines()
    fp.close()
    for s in List:
        s1 = s.replace(' ','').replace('\n','')
        index = s1.find('#')#查找‘#’字符的初始位置，可以用str.index和str.find查找，区别find查找没有的字符，会返回-1，index会报错
        if index == 0:
            continue
        else:
            index = s1.find('=')
            if index != -1:
                key = s1[:index]
                val = s1[index+1:]
                index = val.find('#')
                if index != -1:
                    val = val[:index]
                if key in configDict:
                        Dict2[key] = val
    L = [Dict2['ttfSourceFloder'], Dict2['FontTargeFloder']]
    return L

def getConfigSrc():
    L = readConfigFile()
    return L[0]

def getConfigDst():
    L = readConfigFile()
    return L[1]

def srcFileNameTXTConfig():
    fp = open('FileNameSet.txt', 'w+')
    fileList = os.listdir(getConfigSrc())
    for s in fileList:
        s += '\n'
        fp.write(s)
    fp.close()

def readTFTfileNmae():
    if os.path.exists('FileNameSet.txt') == False:
        srcFileNameTXTConfig()
    fp = open('FileNameSet.txt', 'r')
    fileList = fp.readlines()
    for i in range(len(fileList)):
        fileList[i] = fileList[i].replace(' ','').replace('\n', '')
    fp.close()
    return fileList

def readChinese():
    if os.path.exists('chinese.txt') == False:
        fp = codecs.open('chinese.txt', 'w+', encoding='utf-8')
        fp.close()
    fp = codecs.open('chinese.txt', 'r', encoding='utf-8')
    ChList = fp.readlines()
    fp.close()
    return ChList


def parseFont(dstfilename, filename, lis, size = 12, angle = 0):
    face = freetype.Face(filename)
    face.set_char_size(size*64)
    Font_height = face.size.height//72
    Font_totallen = 0
    
    angle = (angle/180.0)*math.pi
    matrix = FT_Matrix((int)( math.cos( angle ) * 0x10000),
                       (int)(-math.sin( angle ) * 0x10000),
                       (int)( math.sin( angle ) * 0x10000),
                       (int)( math.cos( angle ) * 0x10000))
    flag = FT_LOAD_RENDER
    pen = FT_Vector(0,0)
    FT_Set_Transform( face._FT_Face, byref(matrix), byref(pen))
    previous = 0
    xmin, xmax = 0, 0
    ymin, ymax = 0, 0
    L = []
    start = '{'
    unicode = 0
    length = 0
    width = 0
    rows = 0
    xadvance = 0
    xoffset = 0
    yoffset = 0
    end = '},\n'
    TotalList = []
    dict1 = {"unicode":0, "length":0, "width":0, "rows":0, "xadvance":0, "xoffset":0, "top":0}
    baseline = 0
    for s in lis:
        s = s.replace('\n','')
        for c in s:
            dict1["unicode"] = getUnicode(c)[0]#hex会将整数变为字符串
            face.load_char(c, flag)
            kerning = face.get_kerning(previous, c)
            previous = c
            dict1["xadvance"] = face.glyph.metrics.horiAdvance//64
            yadvance = face.glyph.metrics.vertAdvance//64
            if yadvance > Font_height:
                Font_height = yadvance
            bitmap1 = face.glyph.bitmap
            dict1["width"]  = face.glyph.bitmap.width
            dict1["rows"]   = face.glyph.bitmap.rows
            dict1["top"] = face.glyph.bitmap_top
            dict1["xoffset"] = face.glyph.bitmap_left
            if dict1["top"] > baseline:
                baseline = dict1["top"]
            
            bitmap = getBitmap(bitmap1.buffer)
            dict1["length"] = len(bitmap)#像素的数据个数
            if dict1["length"]:
                writeFileArray(dstfilename, bitmap)#将像素的数据写进去
            TotalList.append(copy.deepcopy(dict1))
            Font_totallen +=1
    print(baseline)
    #print(TotalList)
    for d in TotalList:
        yoffset = baseline - d['top']
        ll = []
        ll.append(d['unicode'])
        ll.append(hex(d['length']))
        ll.append(hex(d['width']))
        ll.append(hex(d['rows']))
        ll.append(hex(d['xoffset']))
        ll.append(hex(yoffset))
        ll.append(hex(d['xadvance']))
        ls = start + listToString(ll) + end
        L.append(ls)
    L.append(Font_height)
    L.append(Font_totallen)
    return L

def listToString(List,c = ''):#将列表转化为字符串,c表示是否加逗号
    s = str(List).replace('[',']').strip(']').replace("'",'') + c
    #print(s)
    return s

def getUnicode(text):#return a List
    L = []
    cl = []
    for i in text:
        cl.append(ord(i))#ord
    #cl = text.encode("unicode_escape").decode("utf-8").replace("\\u",",0x").lstrip(',').split(',')
    #print(type(cl))
    #print(cl)
    for i in cl:
        L.append(hex(i))
    return L
def getBitmap(bitmap):
    L = []
    n = 0
    highByte = 0
    flag = True  #if flag = 0 indicate that highByte_start  flag = 1 indicate that highByte_end  
    #flag = 2 indicate that lowByte_start  flag = 3 indicate that lowByte_end
    lowByte  = 0
    oneByte = 1
    halfByte = 0
    for i in range(len(bitmap)):
        n = n + 1
        if i + 1 == len(bitmap):#最后一个有效数据
            if bool(bitmap[i]):
                halfByte = 8
            else:
                halfByte = 0
            if flag:
                highByte = halfByte | n
                lowByte = 0
            else:
                lowByte = halfByte | n
            oneByte = (highByte << 4) | lowByte
            L.append(hex(oneByte))
            L.append(hex(0))
            return L
        if (bool(bitmap[i]) != bool(bitmap[i+1]) or n + 1 > 7):
            if bool(bitmap[i]):
                halfByte = 8
            else:
                halfByte = 0
            if flag:
                flag = False
                highByte = halfByte | n
                n = 0
            else:
                flag = True
                lowByte = halfByte | n
                oneByte = (highByte << 4) | lowByte
                L.append(hex(oneByte))
                n = 0
    return L

def loadList(List, num,remains, fix = 0):#将数据加载到list中，并返回列表最后一个字节数据的无效长度
    s = str(bin(num)).lstrip('0').strip('b')
    if fix != 0:
        lis = [0]*(fix-(s))
        s = listToString(lis).replace(',','').replace(' ','') + s
    tail = 0
    index = len(List) - 1
    while len(s):
        if len(s) > remains:
            tail = remains
        else:
            tail = len(s)
        value = int(s[:tail],2)
        if remains < BYTEBITS_MAX:
            List[index] = List[index] | (value << (remains -  tail))
        else:
            List.append((value << (remains - tail)))
        if remains - tail:
            remains -= tail
        else:
            remains = BYTEBITS_MAX
            index += 1
        s = s[tail:]
    
    return remains

def ModifySuffixName(filename, suffix):#修改文件后缀名
    portion = os.path.splitext(filename)
    if portion[1] != suffix:
        newname = portion[0]+suffix
        if os.path.exists(newname):
            return
        os.rename(filename, newname)

def writeFile(filename, text):
    fp = open(filename, 'a+')
    fp.write(text)
    fp.close()


def writeFileArray(filename, List):#每排10个数据
    #writeFile(filename, listToString(List[0:5], ',\n'))
    num = (len(List))//10;
    m = (len(List))%10
    for i in range(num):
        writeFile(filename, listToString(List[(i*10):(i*10)+10], ',\n'))
    if m:
        writeFile(filename, listToString(List[(num*10):], ',\n'))
#step1: 先将font.c修改为font.txt
#step2: 判断font.txt是否为空，如果为空，则写入头文件"#include<Arduino.h>\n",否则跳过此步

def TTFFileNameGenerate(floderPath):#该函数的作用是读取floderPath里面所有的tft文件，并将其路径存放TTFfilename.txt
    #判断floderPath是否存在，如果不存在，则直接返回
    if os.path.exists(floderPath) == False:
        return
    
def setup():
    configFile()
    srcFileNameTXTConfig()

def getGb2312ToUnicodeMap(chr_lis):
    fp = open("Gb2312LocalMap.txt",'w+')
    text = "const uint16_t GBKToUnicodeMap[][2] PROGMEM = {\n"
    fp.write(text)
    for s in chr_lis:
        for c in s:
            gbk2312 = int(c.encode('gbk').hex(),16)
            if gbk2312 >0xA1A0 and gbk2312 < 0xFEFF:
                gbk = hex(gbk2312)
                unicode = getUnicode(c)[0]
                #print(unicode)
                text = gbk + ', '+unicode+',\n'
                fp.write(text)
    fp.write("};\n")
    fp.close()
    ModifySuffixName("Gb2312LocalMap.txt", '.h')

if __name__ == '__main__':
    setup()
    srcpath = getConfigSrc()
    dstpath = getConfigDst()
    ch_chr_list = readChinese()
    tft_file_list = readTFTfileNmae()
    font_size = [12,18,24,36,48,72]
    font_size_wh = [0,0]
    lis_1 = ["const uint8_t ", "Bitmaps[] PROGMEM = {\n"]
    lis_2 = ["const gdl_Glyph_t ","Glyphs[] PROGMEM = {\n"]
    lis_3 = ["const gdl_Font_t "," PROGMEM = {\n"]
    getGb2312ToUnicodeMap(ch_chr_list)
    Glyph_list = []
    for file in tft_file_list:
        (filename,suffix) = os.path.splitext(file)#分离文件名和后缀
        for size in font_size:
            newfilename = filename + "Font"+ str(size) +'pt'
            filename_path = dstpath + '\\' +newfilename
            filename_h = filename_path +'.h'
            if os.path.exists(filename_h):
                continue
            filename_txt = filename_path +'.txt'
            fp = open(filename_txt, 'w+')
            text = lis_1[0] + newfilename + lis_1[1]
            fp.write(text)
            fp.close()
            src = srcpath + '\\' + file
            Glyph_list = parseFont(filename_txt, src, ch_chr_list, size, angle = 90)
            text = '};\n\n' + lis_2[0] + newfilename + lis_2[1]
            writeFile(filename_txt, text)
            for i in Glyph_list[:len(Glyph_list) - 2]:
                writeFile(filename_txt, i)
            text = '};\n\n' + lis_3[0] + newfilename + lis_3[1]
            text += "(uint8_t *)"+ newfilename +"Bitmaps,\n"
            text += "(gdl_Glyph_t *)" + newfilename + "Glyphs,\n" + hex(Glyph_list[len(Glyph_list)-2])+', ' + hex(Glyph_list[len(Glyph_list)-1])+'\n};\n\n'
            writeFile(filename_txt, text)
            ModifySuffixName(filename_txt, '.h')
