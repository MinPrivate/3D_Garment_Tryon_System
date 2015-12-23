#include "StdAfx.h"
#include "LoadTexture.h"
#include<stdio.h>
#include<GL/glut.h>
#include<GL/glu.h>	
#include<GL/glaux.h>
#pragma comment(lib, "glaux.lib")

LoadTexture::LoadTexture(void)
{
	// 设置为默认值 
	  image = 0;
	  type = 0;
	  ID = -1;
	  imageWidth = 0;
	  imageHeight = 0;
}


LoadTexture::~LoadTexture(void)
{
	FreeImage();           // 释放内存 
}


/** 载入TGA文件 */
bool LoadTexture::LoadTGA(const char* file)
{
   FILE *pfile;
   unsigned char tempColor;													    //用于交换颜色分量 
   unsigned char bitCount;													    // 每象素的bit位数
   int colorMode;															    // 颜色模式 
   long tgaSize;															    //TGA文件大小
   unsigned char unCompressHeader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//未压缩TGA文件头 
   unsigned char tgaHeader[12];													// 文件头
   unsigned char header[6];													    //文件头前6个字节

   /** 检查文件名是否为空 */
   if(!file) 
	   return false;
   
   /** 打开文件 */
   pfile = fopen(file, "rb");
   if(!pfile) 
	   return false;

   /** 读取文件头前12个字节 */
   fread(tgaHeader, 1, sizeof(tgaHeader), pfile);

   /** 比较文件是否为未压缩文件 */
   if(memcmp(unCompressHeader, tgaHeader, sizeof(unCompressHeader)) != 0)
	   {
		   fclose(pfile);
		   return false;
	   }

   /** 读取6个字节 */
   fread(header, 1, sizeof(header), pfile);

   /** 计算图像的宽度和高度 */
   imageWidth = header[1] * 256 + header[0];
   imageHeight = header[3] * 256 + header[2];

   /** 获取每象素的bit位数 */
   bitCount = header[4];

   /**　计算颜色模式和图像大小 */
   colorMode = bitCount / 8;
   tgaSize = imageWidth * imageHeight * colorMode;

   /** 分配内存 */
   image = new unsigned char[sizeof(unsigned char) * tgaSize];

   /** 读取数据 */
   fread(image, sizeof(unsigned char), tgaSize, pfile);

   /** 将BGA格式转化为RGA格式 */
   for(long index = 0; index < tgaSize; index += colorMode)
	   {
		   tempColor = image[index];
		   image[index] = image[index + 2];
		   image[index + 2] = tempColor;
	   }

   /** 关闭文件 */
   fclose(pfile);

   /** 设置图象类型 */
   if(colorMode == 3) 
	   type = GL_RGB;
   else 
	   type = GL_RGBA;

   return true;
}

void LoadTexture::FreeImage()
{
   /** 释放内存 */
   if(image)
      {
         delete[] image;
         image = 0;
      }
}