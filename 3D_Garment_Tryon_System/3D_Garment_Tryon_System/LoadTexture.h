#pragma once
class LoadTexture
{
public:
	LoadTexture(void);
	~LoadTexture(void);

public:
	bool LoadTGA(const char *file);          //载入TGA文件
    void FreeImage();                        // 释放内存 
	
public:
    unsigned int ID;                        // 生成纹理的ID号 
    int imageWidth;                         // 图像宽度
    int imageHeight;                        // 图像高度
    unsigned char *image;                   // 指向图像数据的指针 
    unsigned int type;                      // 图象类型GL_RGB 或GL_RGBA 
};

