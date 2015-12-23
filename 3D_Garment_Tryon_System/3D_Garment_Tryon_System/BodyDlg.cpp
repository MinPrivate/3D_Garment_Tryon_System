// BodyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_Garment_Tryon_System.h"
#include "BodyDlg.h"
#include "afxdialogex.h"


// CBodyDlg 对话框

IMPLEMENT_DYNAMIC(CBodyDlg, CDialogEx)

CBodyDlg::CBodyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBodyDlg::IDD, pParent)
{

}

CBodyDlg::~CBodyDlg()
{
}

void CBodyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER4, m_XSlider);
	DDX_Control(pDX, IDC_SLIDER6, m_ZSlider);
	DDX_Control(pDX, IDC_SLIDER5, m_YSlider);
	DDX_Control(pDX, IDC_COMBO1, m_ChangeBG);
	DDX_Control(pDX, IDC_SLIDER1, m_HeightSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_ChestSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_WaistSlider);
}


BEGIN_MESSAGE_MAP(CBodyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BODYSTARTBUT, &CBodyDlg::OnBnClickedBodystartbut)
	ON_BN_CLICKED(IDC_BODYSIMPLYBUT, &CBodyDlg::OnBnClickedBodysimplybut)
	ON_BN_CLICKED(IDC_BODYCOMPLETEBUT, &CBodyDlg::OnBnClickedBodycompletebut)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBodyDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CBodyDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CBodyDlg::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDC_BUTTON2, &CBodyDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CBodyDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CBodyDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &CBodyDlg::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &CBodyDlg::OnNMCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, &CBodyDlg::OnNMCustomdrawSlider6)
	ON_WM_SIZE()
	ON_WM_SIZING()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CBodyDlg)
    EASYSIZE(IDC_STATIC_DRAW,ES_BORDER,ES_BORDER,
        ES_BORDER,ES_BORDER,0)
   /* EASYSIZE(IDC_RADIO1,ES_BORDER,ES_BORDER,
        ES_KEEPSIZE,ES_KEEPSIZE,0)
    EASYSIZE(IDC_RADIO2,ES_BORDER,ES_BORDER,
        ES_KEEPSIZE,ES_KEEPSIZE,0)
    EASYSIZE(IDC_CONTENT,ES_BORDER,ES_BORDER,
        ES_BORDER,ES_BORDER,0)
    EASYSIZE(IDC_STATUSFRAME,ES_BORDER,ES_KEEPSIZE,
        ES_BORDER,ES_BORDER,0)
    EASYSIZE(IDC_STATUS,ES_BORDER,ES_KEEPSIZE,
        ES_BORDER,ES_BORDER,0)
    EASYSIZE(IDOK,ES_KEEPSIZE,ES_KEEPSIZE,
        ES_BORDER,ES_BORDER,0)
    EASYSIZE(IDCANCEL,ES_KEEPSIZE,ES_KEEPSIZE,
        ES_BORDER,ES_BORDER,0)
    EASYSIZE(IDC_MYICON1,ES_BORDER,IDC_RADIO2,IDC_CONTENT,
        IDC_STATUSFRAME,ES_HCENTER|ES_VCENTER)
    EASYSIZE(IDC_MYICON2,ES_BORDER,ES_BORDER,IDC_TITLE,
        ES_KEEPSIZE,ES_HCENTER)*/
END_EASYSIZE_MAP

//初始化参数
BOOL CBodyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	displayBody = new Display(GetDlgItem(IDC_STATIC_BODY));				//生成绘图对象

	
	GetDlgItem(IDC_STATIC_BODY)->GetWindowRect(m_rect);
 
	GetClientRect(&m_rect);								 //取客户区大小   

	glViewport(0, 0, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top);

	displayBody->Init();

	m_bodyRecord = 0;		//初始人体绘制
	m_bodyBG = 2;			//初始背景
	m_isClear = false;		//初始化未清除



	//X旋转slider
	m_XSlider.SetRange(0,360);

	m_XSlider.SetPos(0);
	//Y旋转slider
	m_YSlider.SetRange(0,360);

	m_YSlider.SetPos(0);
	//Z旋转slider
	m_ZSlider.SetRange(0,360);

	m_ZSlider.SetPos(0);

	

	//身高slider
	m_HeightSlider.SetRange(90,220);

	m_HeightSlider.SetPos(180);
	//胸围slider
	m_ChestSlider.SetRange(40,180);

	m_ChestSlider.SetPos(65);
	//腰围slider
	m_WaistSlider.SetRange(20,100);

	m_WaistSlider.SetPos(45);



	//设置初始的背景图片

	m_ChangeBG.SetCurSel(0);


	//设置 字体
	CFont *pSignNameFont;
	pSignNameFont =new CFont;
	pSignNameFont->CreateFont(24,0,0,0,150,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_SWISS,_T("宋体(TrueType)")
		);

	//改变combo 字体
	m_ChangeBG.SetFont(pSignNameFont);


	//图片和背景数据
	/////////////////////////////////////////////////////////////////////
	INIT_EASYSIZE;

	return TRUE;  // return TRUE unless you set the focus to a control
}


//从父对话框传递生成的body
void CBodyDlg::setBody(Body *tmpBody){
	body = tmpBody;

}




// CBodyDlg 消息处理程序





// 人体初始化
void CBodyDlg::OnBnClickedBodystartbut()
{
	
	//displayBody->DrawTriangle(0,0,0,1,0,0,2,2,0);
	displayBody->DefaultBodyDisplay(&body->PartCollection,m_bodyBG);
	m_bodyRecord = 0;
	m_isClear = false;
	 //////////////////////////////////////////////////////////////////
}

//三角剖分简化
void CBodyDlg::OnBnClickedBodysimplybut()
{
	
	 //displayBody->DrawTriangle(0,0,0,3,0,0,4,5,0);
	 displayBody->TriangulateBodyDisplay(&body->PartCollection,m_bodyBG);
	 m_bodyRecord = 1;
	 m_isClear = false;
	 //////////////////////////////////////////////////////////////////
}

//人体生成
void CBodyDlg::OnBnClickedBodycompletebut()
{
	
	//displayBody->DrawTriangle(0,0,0,-4,0,0,-5,6,0);
	displayBody->SurfaceBodyDisplay(&body->PartCollection,m_bodyBG);//绘制人体模型
	m_bodyRecord = 2;
	m_isClear = false;
	 //////////////////////////////////////////////////////////////////
}


void CBodyDlg::Redraw()
{
	switch(m_bodyRecord)
	{
	case 0:
		OnBnClickedBodystartbut();		//人体初始化

		break;
	case 1:
		OnBnClickedBodysimplybut();		//三角剖分简化

		break;
	case 2:
		OnBnClickedBodycompletebut();	//人体生成

		break;
	}
}




//身高
void CBodyDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;

	UpdateData(TRUE);  
	int pos = m_HeightSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	


	CString str; 
	str.Format(_T("%dcm"), pos);
	GetDlgItem(IDC_STATICHEIGHT)->SetWindowText(str);//MessageBox(str);
	UpdateData(FALSE);                   //显示到对话框上 

	/////////////////////////////////////////////////////////////

	//for(int i=0;i<body->PartCollection.size() ;i++)
	//{
	//	for(int j=0;j<body->PartCollection.at(i)->dotCollection.size() ;j++)
	//	{
	//		
	//		body->PartCollection.at(i)->dotCollection.at(j).y *=pos/180;
	//		//alert(pos/180);
	//		 //MessageBox(_T("%f",pos/180));
	//					
	//	}
	//}
	//displayBody->DefaultBodyDisplay(&body->PartCollection);


	//for(int i=0;i<body->PartCollection.size() ;i++)
	//{
	//	for(int j=0;j<body->PartCollection.at(i)->dotCollection.size() ;j++)
	//	{
	//		
	//		body->PartCollection.at(i)->dotCollection.at(j).y *= 180/pos;
	//					
	//	}
	//}

}

//胸围silder
void CBodyDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;

	
	UpdateData(TRUE);  
	int pos = m_ChestSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	CString str; 
	str.Format(_T("%dcm"), pos);
	GetDlgItem(IDC_STATICCHEST)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 

	/////////////////////////////////////////////////////////////

}

//腰围slider
void CBodyDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;

	
	UpdateData(TRUE);  
	int pos = m_WaistSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	CString str; 
	str.Format(_T("%dcm"), pos);
	GetDlgItem(IDC_STATICWAIST)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 

	/////////////////////////////////////////////////////////////
}

//清除显示的所有内容
void CBodyDlg::OnBnClickedButton2()
{
	///////////////////////////////////////////////////////////////////
	displayBody->Render();
	m_isClear = true;
}

//combo 选择背景
void CBodyDlg::OnCbnSelchangeCombo1()
{
	UINT nowBG = m_ChangeBG.GetCurSel();


	/////////////////////////////////////////////////////////切换背景
	switch(nowBG){
	case 0:
		m_bodyBG = 2;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 1:
		m_bodyBG = 0;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 2:
		m_bodyBG = 1;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 3:
		m_bodyBG = 3;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	default:
		break;
	}

	//移除焦点
	//m_ChangeBG.
}

//将旋转的人体模型复原
void CBodyDlg::OnBnClickedButton1()
{
	 
	UpdateData(TRUE);  
	int pos = m_XSlider.GetPos();//得到滑块位置   
	
	CString str; 
	str.Format(_T("%d"), 0);
	m_XSlider.SetPos(0);      //给变量m_str1赋值   m_slider.SetPos(50);

	m_YSlider.SetPos(0);      //给变量m_str1赋值
	m_ZSlider.SetPos(0);      //给变量m_str1赋值

	GetDlgItem(IDC_STATICX)->SetWindowText(str);
	GetDlgItem(IDC_STATICY)->SetWindowText(str);
	GetDlgItem(IDC_STATICZ)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 

	/////////////////////////////////////////////////////////////////////////////////////////
	displayBody->xRot = 0.0;
	displayBody->yRot = 0.0;
	displayBody->zRot = 0.0;
	if(!m_isClear)
	{
		Redraw();
	}

}

//X旋转
void CBodyDlg::OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;


	UpdateData(TRUE);  
	int pos = m_XSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	CString str; 
	str.Format(_T("%d"), pos);
	GetDlgItem(IDC_STATICX)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 

	
	//////////////////////////////////////////////////////////////////////////////////////
	displayBody->xRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}

}


//Y旋转
void CBodyDlg::OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;

		UpdateData(TRUE);  
	int pos = m_YSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	CString str; 
	str.Format(_T("%d"), pos);
	GetDlgItem(IDC_STATICY)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 


	//////////////////////////////////////////////////////////////////////////////////////
	displayBody->yRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}

}


//Z旋转
void CBodyDlg::OnNMCustomdrawSlider6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	*pResult = 0;

	UpdateData(TRUE);  
	int pos = m_ZSlider.GetPos();           //得到滑块位置   
	//m_XSlider.Format(_T("%d"),pos);      //给变量m_str1赋值   

	CString str; 
	str.Format(_T("%d"), pos);
	GetDlgItem(IDC_STATICZ)->SetWindowText(str);
	UpdateData(FALSE);                   //显示到对话框上 


	//////////////////////////////////////////////////////////////////////////////////////
	displayBody->zRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}
}






void CBodyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}


void CBodyDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	EASYSIZE_MINSIZE(700,600,fwSide,pRect);
}


//void CBodyDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnMouseMove(nFlags, point);
//
//	CRect rect; 
//	GetClientRect(&rect); 
//	if(point.x <= rect.left+3) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE))); 
//	m_nHitTest = HTLEFT; 
//	} 
//	else if(point.x >= rect.right-3) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE))); 
//	m_nHitTest = HTRIGHT; 
//	} 
//	else if(point.y <= rect.top+3) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS))); 
//	m_nHitTest = HTTOP; 
//	} 
//	else if(point.y >= rect.bottom-3) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS))); 
//	m_nHitTest = HTBOTTOM; 
//	} 
//	else if(point.x <= rect.left+10 && point.y <= rect.top+10) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE))); 
//	m_nHitTest = HTTOPLEFT; 
//	} 
//	else if(point.x >= rect.right-10 && point.y <= rect.top+10) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW))); 
//	m_nHitTest = HTTOPRIGHT; 
//	} 
//	else if(point.x <= rect.left+10 && point.y >= rect.bottom-10) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW))); 
//	m_nHitTest = HTBOTTOMLEFT; 
//	} 
//	else if(point.x >= rect.right-10 && point.y >= rect.bottom-10) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE))); 
//	m_nHitTest = HTBOTTOMRIGHT; 
//	} 
//	else 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW))); 
//	m_nHitTest = 0; 
//	}
//}
//
//
//void CBodyDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//
//	if(m_nHitTest == HTTOP) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTBOTTOM) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTLEFT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTRIGHT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTTOPLEFT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTTOPRIGHT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTBOTTOMLEFT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW))); 
//	SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else if(m_nHitTest == HTBOTTOMRIGHT) 
//	{ 
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE))); 
//	SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y)); 
//	} 
//	else 
//	{
//
//	//实现对话框跟随鼠标移动
//
//	::SendMessage (GetSafeHwnd(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0); 
//	}
//}
