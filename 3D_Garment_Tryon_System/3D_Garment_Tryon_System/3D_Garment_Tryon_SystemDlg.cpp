
// 3D_Garment_Tryon_SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_Garment_Tryon_System.h"
#include "3D_Garment_Tryon_SystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy3D_Garment_Tryon_SystemDlg 对话框




CMy3D_Garment_Tryon_SystemDlg::CMy3D_Garment_Tryon_SystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy3D_Garment_Tryon_SystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3D_Garment_Tryon_SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODELTAB, m_TabModel);
}

BEGIN_MESSAGE_MAP(CMy3D_Garment_Tryon_SystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MODELTAB, &CMy3D_Garment_Tryon_SystemDlg::OnTcnSelchangeModeltab)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CMy3D_Garment_Tryon_SystemDlg)
   EASYSIZE(IDC_MODELTAB,ES_BORDER,ES_BORDER,
        ES_BORDER,ES_BORDER,0)
    /* EASYSIZE(IDC_RADIO2,ES_BORDER,ES_BORDER,
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


// CMy3D_Garment_Tryon_SystemDlg 消息处理程序

BOOL CMy3D_Garment_Tryon_SystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	INIT_EASYSIZE;
	///////////////////////////////////////初始化tab 标签

	CRect tabRect;
	m_TabModel.InsertItem(0,_T("人体建模"));
	m_TabModel.InsertItem(1,_T("人体试衣"));

	bodydlg.Create(IDD_BODYTAB,&m_TabModel);
	garmentdlg.Create(IDD_GARMENTTAB,&m_TabModel);
	m_TabModel.GetClientRect(&tabRect);
	tabRect.left+=1;tabRect.right-=1;tabRect.top+=30;tabRect.bottom-=1;

	bodydlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
		tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);
	
	//获得绘图描述表
	bodydlg.displayBody->GetDrawPen();

	garmentdlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
		tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW); 

	//设置 字体
	CFont *pSignNameFont;
	pSignNameFont =new CFont;
	pSignNameFont->CreateFont(18,0,0,0,150,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_SWISS,_T("宋体(TrueType)")
		);

	//改变tab 字体
	m_TabModel.SetFont(pSignNameFont);
	//设置高度m_TabCtrl.SetItemSize(CSize(50,40));
	CSize tmpsize = CSize(50,30);
	m_TabModel.SetItemSize(tmpsize);



	//////////////////////////////////////////////////////////////////绘图相关参数初始化
	body = new Body();

	body->sex = 1;
	body->height = 180.0;

	body->readOBJFile();
	body->triangulate();
	body->creatSurface();

	//将body传递给body对话框
	bodydlg.setBody(body);

	netGrid = new NetGrid(180, 80, 180, 1);
	netGrid->justifyInOrOut(body);

	//将body生成的netGrid传递给garment对话框
	garmentdlg.setNetGrid(netGrid);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy3D_Garment_Tryon_SystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy3D_Garment_Tryon_SystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy3D_Garment_Tryon_SystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3D_Garment_Tryon_SystemDlg::OnTcnSelchangeModeltab(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;


	CRect tabRect;
	
	m_TabModel.GetClientRect(&tabRect);
	tabRect.left+=1;tabRect.right-=1;tabRect.top+=30;tabRect.bottom-=1;

	switch(m_TabModel.GetCurSel()){
	case 0:
		bodydlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
			tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);

		//获得绘图描述表
		bodydlg.displayBody->GetDrawPen();

		garmentdlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
			tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
		break;
	case 1:
		bodydlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
			tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);

		garmentdlg.SetWindowPos(NULL,tabRect.left,tabRect.top,
			tabRect.Width(),tabRect.Height(), SWP_SHOWWINDOW);

		//获得绘图描述表
		garmentdlg.displayGarment->GetDrawPen();
		break;
	default:
		break;
	}

}


void CMy3D_Garment_Tryon_SystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}


void CMy3D_Garment_Tryon_SystemDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	EASYSIZE_MINSIZE(700,600,fwSide,pRect);
}
