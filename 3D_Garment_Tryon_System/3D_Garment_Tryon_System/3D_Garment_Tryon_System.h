
// 3D_Garment_Tryon_System.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy3D_Garment_Tryon_SystemApp:
// 有关此类的实现，请参阅 3D_Garment_Tryon_System.cpp
//

class CMy3D_Garment_Tryon_SystemApp : public CWinApp
{
public:
	CMy3D_Garment_Tryon_SystemApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy3D_Garment_Tryon_SystemApp theApp;