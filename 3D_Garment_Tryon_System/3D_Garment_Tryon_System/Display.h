
#pragma once

#include "Body.h"
#include "NetGrid.h"
#include "TextureMap.h"


#include "Garment.h"   


#define TEXTURE_COUNT	4

class Display
{
public:
	Display(CWnd *w);
	~Display(void);

	bool Init();
	bool GetDrawPen();
	void Render();
	void DrawTriangle(float x1,float y1, float z1, 
						float x2, float y2, float z2,
						float x3, float y3, float z3, int backGround);
	//void LoadTexture();
	void DrawBackground(int backGround);
	//绘制初始人体模型
	void DefaultBodyDisplay(vector<BodyPart *> *data,int backGround);
	//绘制三角剖分后的人体模型
	void TriangulateBodyDisplay(vector<BodyPart *> *data,int backGround);


	void SurfaceBodyDisplay(vector<BodyPart *> *data,int backGround);




	//void DefaultBoxDisplay(BoxCloth *tmpBoxCloth);
	//void BoxCollideDisplay(BoxCloth *tmpBoxCloth);

	void DefaultGarmentDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol,int backGround);
	void GarmentCollideDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol,int backGround);


	
public:
	//绘图和渲染描述表
	CWnd *wnd;
	HDC m_hDC;
	HGLRC m_hRC;

	// Rotation amounts
	float xRot;
	float yRot;
	float zRot;

	//背景
	TextureMap texture[TEXTURE_COUNT];
	char *textureFileName[TEXTURE_COUNT];

protected:
	bool SetPixel();
};

