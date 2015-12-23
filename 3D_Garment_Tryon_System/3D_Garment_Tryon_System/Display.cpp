#include "StdAfx.h"
#include "Display.h"
#include "TGA.h"
extern int isIn[180][80][180];

Display::Display(CWnd *w)
{
	wnd = w;

	xRot = 0.0;
	yRot = 0.0;
	zRot = 0.0;

	textureFileName[0] = "spring.tga";
	textureFileName[1] = "summer.tga";
	textureFileName[2] = "autumn.tga";
	textureFileName[3] = "winter.tga";
}


Display::~Display(void)
{
	
}

bool Display::GetDrawPen()
{
	// 获得绘图描述表
	m_hDC = ::GetDC(*wnd);  
	if(m_hDC == NULL) 
		return false;
	if(SetPixel() == false) 
		return false;
	// 创建渲染描述表
	m_hRC = wglCreateContext(m_hDC);
	// 使绘图描述表为当前调用现程的当前绘图描述表 
	wglMakeCurrent(m_hDC,m_hRC);

	return true;
}

//初始化OpenGL 
bool Display::Init()
{
	bool succeed = true;

	succeed = GetDrawPen();

	glClearColor(0.0f,0.0f,0.0f,0.0f);   //指定清除颜色缓存区时使用黑色

	gluPerspective						// 设置透视图
		( 45.0f,						// 透视角设置为 45 度
		  1,							// 窗口的宽与高比
		  0.1f,							// 视野透视深度:近点1.0f
		  3000.0f						// 视野透视深度:始点0.1f远点1000.0f
		);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);		// Hidden surface removal
	glFrontFace(GL_CW);				// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate insides
	glEnable(GL_NORMALIZE);			//使OpenGL自动进行法向量单位化	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	return succeed;
}

//void Display::LoadTexture()
//{
//	if(texture[0].LoadTextureTGA("spring.tga"))
//	{
//		//texture[0].SetTexturePara(texture[0].loadTexture);
//	}
//	if(texture[1].LoadTextureTGA("summer.tga"))
//	{
//		//texture[1].SetTexturePara(texture[1].loadTexture);
//	}
//	if(texture[2].LoadTextureTGA("autumn.tga"))
//	{
//		//texture[2].SetTexturePara(texture[2].loadTexture);
//	}
//	if(texture[3].LoadTextureTGA("winter.tga"))
//	{
//		//texture[3].SetTexturePara(texture[3].loadTexture);
//	}
//	glEnable(GL_TEXTURE_2D);
//}

// Called to draw background
void Display::DrawBackground(int backGround)
{
	

	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	//glTranslatef(0.0f,0.0f,-5.0f);
	glEnable(GL_TEXTURE_2D);
	texture[backGround].LoadTextureTGA(textureFileName[backGround]);
	texture[backGround].SetTexturePara(texture[backGround].loadTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

}


//主要OpenGL绘制      
void Display::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存
	
	//glLoadIdentity();
	////旋转
	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	//glPushMatrix();
	//	//glTranslatef(0.0f,0.5f,0.0f);
	//	glScalef(0.1f,0.1f,0.1f);
	//	glColor3f(0.0,1.0,0.0);

	//	glBegin(GL_TRIANGLES);
	//		glVertex3f(0.0, 0.0, 0.0);
	//		glVertex3f(1.0, 0.0, 0.0);
	//		glVertex3f(1.5, 1.0, 0.0);
	//	glEnd();
	//	
	//glPopMatrix();
	
	SwapBuffers(m_hDC);
}





void Display::DrawTriangle(float x1,float y1, float z1, 
						float x2, float y2, float z2,
						float x3, float y3, float z3, int backGround)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存

	glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();    

	
		glScalef(0.1f,0.1f,0.1f);
		
		DrawBackground(backGround);
		
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();    
		//旋转
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);

		
			//glTranslatef(0.0f,0.5f,0.0f);
			glScalef(0.1f,0.1f,0.1f);
			glColor3ub(255,0,0);

			glBegin(GL_TRIANGLES);
				
				glVertex3f(x1, y1, z1);
				glVertex3f(x2, y2, z2);
				glVertex3f(x3, y3, z3);
			glEnd();

		glPopMatrix();
	
	
	SwapBuffers(m_hDC);
}



//绘制初始人体模型
void Display::DefaultBodyDisplay(vector<BodyPart *> *data,int backGround)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存
	/*glTranslatef(0.0f, 3.0f, 0.0f);*/
	//背景
	glLoadIdentity();
	glScalef(0.1f,0.1f,0.1f);
	DrawBackground(backGround);

	//人体
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glColor3ub(198,120,110);
	glPushMatrix();
		glTranslatef(0.0f, -0.9f, 0.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		//glPointSize(2);
		glBegin(GL_POINTS);
			for(int i=0;i<data->size() ;i++)
			{
				for(int j=0;j<data->at(i)->dotCollection.size() ;j++)
				{
					glVertex3f(data->at(i)->dotCollection.at(j).x,
								data->at(i)->dotCollection.at(j).y,
								data->at(i)->dotCollection.at(j).z);
				}
			}
		glEnd();
		
	glPopMatrix();
	
	SwapBuffers(m_hDC);
}

//绘制三角剖分后的人体模型
void Display::TriangulateBodyDisplay(vector<BodyPart *> *data,int backGround)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存

	//背景
	glLoadIdentity();
	glScalef(0.1f,0.1f,0.1f);
	DrawBackground(backGround);

	//人体
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glColor3ub(198,120,110);
	glPushMatrix();
		glTranslatef(0.0f, -0.9f, 0.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		//glPointSize(2);
		glBegin(GL_POINTS);
			for(int i = 0; i < data->size(); i++)
			{
				for(int j = 0; j < data->at(i)->circleCollection.size(); j++)
				{
					for(int k = 0; k < data->at(i)->circleCollection.at(j).size(); k++)
					{
						glVertex3f(data->at(i)->circleCollection.at(j).at(k).x,
									data->at(i)->circleCollection.at(j).at(k).y,
									data->at(i)->circleCollection.at(j).at(k).z);
					}
				}
			}
		glEnd();
		
	glPopMatrix();
	
	SwapBuffers(m_hDC);
}

//绘制三角表面人体模型——调整人体模型
void Display::SurfaceBodyDisplay(vector<BodyPart *> *data,int backGround)
//void Display::SurfaceBodyDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存

	//背景
	glLoadIdentity();
	glScalef(0.1f,0.1f,0.1f);
	DrawBackground(backGround);

	//人体
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	
	glPushMatrix();
		glTranslatef(0.0f, -0.9f, 0.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		//glPointSize(2);
		glColor3ub(198,120,110);
		for(int i = 0; i < data->size(); i++)
		{
			for(int j = 0; j < data->at(i)->surfaceCollection.size(); j++)
			{
				glBegin(GL_TRIANGLES);
					glVertex3f(data->at(i)->surfaceCollection.at(j).p1.x,
									data->at(i)->surfaceCollection.at(j).p1.y,
									data->at(i)->surfaceCollection.at(j).p1.z);
					glVertex3f(data->at(i)->surfaceCollection.at(j).p2.x,
									data->at(i)->surfaceCollection.at(j).p2.y,
									data->at(i)->surfaceCollection.at(j).p2.z);
					glVertex3f(data->at(i)->surfaceCollection.at(j).p3.x,
									data->at(i)->surfaceCollection.at(j).p3.y,
									data->at(i)->surfaceCollection.at(j).p3.z);
				glEnd();
			}
		}
		
		//glColor3ub(0,0,255);
		//glBegin(GL_TRIANGLE_STRIP);
		////////////////////////////////////////////////////////////////			衣服
		//	for(int i=0;i<clothcol->size() ;i++)
		//	{
		//		//if(i>3)
		//		for(int j=0;j<clothcol->at(i).getVectorMass()->size() ;j++)
		//		{
		//			for(int k = 0 ; k < clothcol->at(i).getVectorMass()->at(i)->massSpring.size();k ++){
		//				if(k%3 == 0){
		//					glVertex3f( 
		//						clothcol->at(i).getVectorMass()->at(j)->x,
		//						156 - clothcol->at(i).getVectorMass()->at(j)->y,
		//						clothcol->at(i).getVectorMass()->at(j)->z
		//					);
		//				}

		//				glVertex3f( 
		//					clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->x,
		//					156 - clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->y,
		//					clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->z
		//				);
		//			}
		//		}
		//	}
		//glEnd();
		
	glPopMatrix();
	
	SwapBuffers(m_hDC);
}


//void Display::DefaultBoxDisplay(BoxCloth *tmpBoxCloth){}
//void Display::BoxCollideDisplay(BoxCloth *tmpBoxCloth){}







/////////////////////////////////////////////////////////////////////////////////////////////
void Display::DefaultGarmentDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol, int backGround)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存

	//背景
	glLoadIdentity();
	glScalef(0.1f,0.1f,0.1f);
	DrawBackground(backGround);

	//衣服
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	
	glPushMatrix();
		glTranslatef(0.0f, -0.9f, 0.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		
		
		glColor3ub(0,0,255);
		glBegin(GL_TRIANGLE_STRIP);
		//////////////////////////////////////////////////////////////			衣服
			for(int i=0;i<clothcol->size() ;i++)
			{
				//if(i>3)
				for(int j=0;j<clothcol->at(i).getVectorMass()->size() ;j++)
				{
					for(int k = 0 ; k < clothcol->at(i).getVectorMass()->at(i)->massSpring.size();k ++){
						if(k%3 == 0){
							glVertex3f( 
								clothcol->at(i).getVectorMass()->at(j)->x,
								156 - clothcol->at(i).getVectorMass()->at(j)->y,
								clothcol->at(i).getVectorMass()->at(j)->z
							);
						}

						glVertex3f( 
							clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->x,
							156 - clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->y,
							clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->z
						);
					}
				}
			}
		glEnd();
		
	glPopMatrix();
	
	SwapBuffers(m_hDC);
}



/////////////////////////////////////////////////////////////////////////////////////////////
void Display::GarmentCollideDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol,int backGround)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存

	//背景
	glLoadIdentity();
	glScalef(0.1f,0.1f,0.1f);
	DrawBackground(backGround);

	//衣服
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	
	glPushMatrix();
		glTranslatef(0.0f, -0.9f, 0.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		
		
		glColor3ub(0,0,255);
		glBegin(GL_TRIANGLE_STRIP);
		//////////////////////////////////////////////////////////////			衣服
			for(int i=0;i<clothcol->size() ;i++)
			{
				//if(i>3)
				for(int j=0;j<clothcol->at(i).getVectorMass()->size() ;j++)
				{
					for(int k = 0 ; k < clothcol->at(i).getVectorMass()->at(i)->massSpring.size();k ++){
						if(k%3 == 0){
							glVertex3f( 
								clothcol->at(i).getVectorMass()->at(j)->x,
								156 - clothcol->at(i).getVectorMass()->at(j)->y,
								clothcol->at(i).getVectorMass()->at(j)->z
							);
						}

						glVertex3f( 
							clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->x,
							156 - clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->y,
							clothcol->at(i).getVectorMass()->at(i)->massSpring.at(k)->getConnectedMass()->z
						);
					}
				}
			}
		glEnd();
		
	glPopMatrix();
	
	SwapBuffers(m_hDC);
}



//void Display::NetDisplay(NetGrid *net, int l, int w, int h)
//{
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存
//
//	glLoadIdentity();
//
//	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
//
//	glColor3ub(255,0,0);
//	glPushMatrix();
//		glTranslatef(0.0f, -0.9f, 0.0f);
//		glScalef(0.01f, 0.01f, 0.01f);
//		//glPointSize(2);
//		
//		for(int i = 0; i < l; i++)
//		{
//			for(int j = 0; j < w; j++)
//			{
//				for(int k = 0; k < h; k++)
//				{
//					if(isIn[i][j][k] == 1)
//					{
//						glBegin(GL_POINTS);
//						glVertex3f(net->centerDots[i][j][k].x,
//											net->centerDots[i][j][k].y,
//											net->centerDots[i][j][k].z);
//						
//						glEnd();
//					}
//				}
//			}
//		}
//		
//		
//	glPopMatrix();
//	
//	SwapBuffers(m_hDC);
//}

// 设置像素格式函数
bool Display::SetPixel()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{ 
		sizeof(PIXELFORMATDESCRIPTOR),  	// size of this pfd 
		1,									// version number 
		PFD_DRAW_TO_WINDOW |				// support window 
		PFD_SUPPORT_OPENGL |				// support OpenGL 
		PFD_DOUBLEBUFFER,					// double buffered 
		PFD_TYPE_RGBA,						// RGBA type 
		24,									// 24-bit color depth 
		0, 0, 0, 0, 0, 0,					// color bits ignored 
		0,									// no alpha buffer 
		0,									// shift bit ignored 
		0,									// no accumulation buffer 
		0, 0, 0, 0,							// accum bits ignored 
		32,									// 32-bit z-buffer 
		0,									// no stencil buffer 
		0,									// no auxiliary buffer 
		PFD_MAIN_PLANE,						// main layer 
		0,									// reserved 
		0, 0, 0								// layer masks ignored 
	}; 
	int pixelformat; 
	if ( (pixelformat = ChoosePixelFormat(m_hDC, &pfd)) == 0 ) 
	{ 
		MessageBox(NULL,_T("ChoosePixelFormat failed"),_T("Warning"),MB_OK); 
		return FALSE; 
	} 
	if (SetPixelFormat(m_hDC, pixelformat, &pfd) == FALSE) 
	{ 
		MessageBox(NULL,_T("SetPixelFormat failed"),_T("Warning"),MB_OK); 
		return FALSE; 
	} 
	return TRUE;	
}
