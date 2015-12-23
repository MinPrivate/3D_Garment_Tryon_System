#pragma once
#include "LoadTexture.h"



class TextureMap
{
public:
	TextureMap(void);
	~TextureMap(void);

public:
	bool LoadTextureTGA(const char* fileName);		 // 载入TGA文件为纹理 
	void SetTexturePara(LoadTexture *texture);

	LoadTexture *loadTexture;
	
};

