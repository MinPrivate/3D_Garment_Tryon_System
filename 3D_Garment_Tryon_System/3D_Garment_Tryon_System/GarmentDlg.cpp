// GarmentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_Garment_Tryon_System.h"
#include "GarmentDlg.h"
#include "afxdialogex.h"


// CGarmentDlg 对话框

IMPLEMENT_DYNAMIC(CGarmentDlg, CDialogEx)

CGarmentDlg::CGarmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGarmentDlg::IDD, pParent)
{

}

CGarmentDlg::~CGarmentDlg()
{
}

void CGarmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_XSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_YSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_ZSlider);
	DDX_Control(pDX, IDC_COMBO1, m_ChangeBG);
}


BEGIN_MESSAGE_MAP(CGarmentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGarmentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CGarmentDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGarmentDlg::OnBnClickedButton6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CGarmentDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CGarmentDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CGarmentDlg::OnNMCustomdrawSlider3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CGarmentDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGarmentDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGarmentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGarmentDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


//初始化参数
BOOL CGarmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	displayGarment = new Display(GetDlgItem(IDC_STATIC_GARMENT));				//生成绘图对象

	GetDlgItem(IDC_STATIC_GARMENT)->GetWindowRect(m_rect);
 
	GetClientRect(&m_rect);								 //取客户区大小   

	glViewport(0, 0, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top);

	displayGarment->Init();

	m_garmentRecord = 0;		//初始衣服
	m_garmentBG = 2;			//初始背景
	m_isClear = false;			//初始化未清除


	//X旋转slider
	m_XSlider.SetRange(0,360);

	m_XSlider.SetPos(0);
	//Y旋转slider
	m_YSlider.SetRange(0,360);

	m_YSlider.SetPos(0);
	//Z旋转slider
	m_ZSlider.SetRange(0,360);

	m_ZSlider.SetPos(0);


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

	//衣服，图片和背景数据
	/////////////////////////////////////////////////////////////////////

	garment = new Garment();
	garment->garmentRead();

	//boxCloth = BoxCloth();/////////////////////////////////////s

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}

//从父对话框传递生成的body
void CGarmentDlg::setBody(Body *tmpBody){
	body = tmpBody;

}

//从父对话框传递生成的netgrid
void CGarmentDlg::setNetGrid(NetGrid *tmpNetGrid){
	netGrid = tmpNetGrid;

	//迭代/////////////////////////////////////////////////////////////////////////
	//garment->numIteration(28,netGrid);
}



// CGarmentDlg 消息处理程序

//防止箱子和布准备
void CGarmentDlg::OnBnClickedButton1()
{
	
	displayGarment->DrawTriangle(0,0,0,3,0,0,4,5,0,m_garmentBG);
	m_garmentRecord = 0;
	m_isClear = false;
	////////////////////////////////////////////////////////
}

//实现箱子碰撞
void CGarmentDlg::OnBnClickedButton2()
{
	
	displayGarment->DrawTriangle(0,0,0,-4,0,0,-5,6,0,m_garmentBG);
	m_garmentRecord = 1;
	m_isClear = false;
	////////////////////////////////////////////////////////
}

//衣片放置
void CGarmentDlg::OnBnClickedButton3()
{
	
	//displayGarment->DrawTriangle(0,0,0,-4,0,0,5,6,0);
	displayGarment->DefaultGarmentDisplay(&body->PartCollection,&garment->allCloth,m_garmentBG);//////////////
	m_garmentRecord = 2;
	m_isClear = false;
	///////////////////////////////////////////////////////
}

//衣片缝合过程
void CGarmentDlg::OnBnClickedButton4()
{
	
	//displayGarment->DrawTriangle(0,0,0,4,0,0,-5,6,0);

	displayGarment->GarmentCollideDisplay(&body->PartCollection,&garment->allCloth,m_garmentBG);//////////////
	m_garmentRecord = 3;
	m_isClear = false;
	/////////////////////////////////////////////////////////
}


void CGarmentDlg::Redraw()
{
	switch(m_garmentRecord)
	{
	case 0:
		OnBnClickedButton1();			//防止箱子和布准备
		break;
	case 1:
		OnBnClickedButton2();			//实现箱子碰撞
		break;
	case 2:
		OnBnClickedButton3();			//衣片放置
		break;
	case 3:
		OnBnClickedButton4();			//衣片缝合过程
		break;
	}
}




//清除
void CGarmentDlg::OnBnClickedButton5()
{
	/////////////////////////////////////////////////////////////
	displayGarment->Render();
	m_isClear = true;
}



//复原
void CGarmentDlg::OnBnClickedButton6()
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

	/////////////////////////////////////////////////////////////////
	displayGarment->xRot = 0.0;
	displayGarment->yRot = 0.0;
	displayGarment->zRot = 0.0;
	if(!m_isClear)
	{
		Redraw();
	}
}

//Xslider
void CGarmentDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
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
	displayGarment->xRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}

}

//Yslider
void CGarmentDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
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
	displayGarment->yRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}

}

//Zslider
void CGarmentDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
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
	displayGarment->zRot = pos;
	if(!m_isClear)
	{
		Redraw();
	}


}

//选择背景
void CGarmentDlg::OnCbnSelchangeCombo1()
{
	UINT nowBG = m_ChangeBG.GetCurSel();


	/////////////////////////////////////////////////////////切换背景
	switch(nowBG){
	case 0:
		m_garmentBG = 2;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 1:
		m_garmentBG = 0;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 2:
		m_garmentBG = 1;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	case 3:
		m_garmentBG = 3;
		if(!m_isClear)
		{
			Redraw();
		}
		break;
	default:
		break;
	}
}

