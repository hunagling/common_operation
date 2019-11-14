#define _CRT_SECURE_NO_WARNINGS  //使用fopen等函数，避免vs的检测
#include <iostream>
#include <stdio.h>

if ((cipher = fopen(cipherFile, "rb")) == NULL) {
	//新建二进制文件，已存在的文件将内容清空，只允许写
		return CIPHER_FILE_OPEN_ERROR;              
	    //#define 定义返还值
	}                                              
	//fopen的第一个参数均为路径
if ((plain = fopen(plainFile, "wb")) == NULL) {
	//打开一个二进制文件，文件必须存在，只允许读
		return PLAIN_FILE_OPEN_ERROR;
	}


while (!feof(plain)) {
           //feof函数，在stdio.h中，检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
		   if ((count = fread(plainBlock, sizeof(char), 8, plain)) == 8) {
		   //  fread函数返还值为读取到的元素个数，元素尺寸为sizeof(char),保存到plainBlock数组中	
		   //这里填更改操作操作
		   fwrite(cipherBlock3, sizeof(char), 8, cipher);//写入文件
		   /*用cipherBlock3数组，写8个 char大小的元素进cipher文件流中 */
		   }
}
if (count) {//如果文件数据不足，需要补充的情况，我们需要一个标记
		memset(plainBlock + count, '\0', 7 - count);
		//补充"\x00"，补满七个
		//最后一个字符保存包括最后一个字符在内的所填充的字符数量
		plainBlock[7] = 8 - count;   
		//第八个，保存补充的个数
		fwrite(cipherBlock3, sizeof(char), 8, cipher);
	}
	fclose(plain);
	fclose(cipher);
	return OK;		
-----------------------------------------------------加密生成新文件，及文件数据不足补充数据

if ((cipher = fopen(cipherFile, "rb")) == NULL) {
		return CIPHER_FILE_OPEN_ERROR;
	}
	if ((plain = fopen(plainFile, "wb")) == NULL) {
		return PLAIN_FILE_OPEN_ERROR;
	}

	//获取文件长度的操作，目的是取出被还原的最后一组数据
	fseek(cipher, 0, SEEK_END);   //将文件指针置尾
	fileLen = ftell(cipher);    //取文件指针当前位置
	rewind(cipher);             //将文件指针重指向文件头
	while (1) {
		//密文的字节数一定是8的整数倍
		fread(cipherBlock, sizeof(char), 8, cipher);
		times += 8;
		if (times < fileLen) {
			fwrite(plainBlock3, sizeof(char), 8, plain);
		}
		else {
		//最后一组数据需要进行处理，再拷贝回去。先跳出
			break;
		}
	}
	//判断末尾是否被填充
	if (plainBlock3[7] < 8) {
		//先判断最后一位是否小于8，不是直接去执行无填充
		for (count = 8 - plainBlock3[7]; count < 7; count++) {
			if (plainBlock3[count] != '\0') {
				//即使最后一个数小于8，也有可能没有填充，所以去检测填充的每一个具体位置否是'\0'
				//存在不是'\0'的情况直接跳出
				break;
			}
		}
	}
	if (count == 7) {//有填充
		fwrite(plainBlock3, sizeof(char), 8 - plainBlock3[7], plain);
	}
	else {//无填充
		fwrite(plainBlock3, sizeof(char), 8, plain);
	}

	fclose(plain);
	fclose(cipher);
	return OK;
----------------------------------------------------------------还原文件，特殊处理最后一组数据
