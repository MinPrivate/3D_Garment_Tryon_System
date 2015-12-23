
// 3D_Garment_Tryon_SystemDlg.h : 头文件
//



#pragma once


#include "GarmentDlg.h"
#include "BodyDlg.h"

#include "Body.h"
//#include "NetGrid.h"
#include "Garment.h"

// CMy3D_Garment_Tryon_SystemDlg 对话框
class CMy3D_Garment_Tryon_SystemDlg : public CDialogEx
{
	DECLARE_EASYSIZE
// 构造
public:
	CMy3D_Garment_Tryon_SystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY3D_GARMENT_TRYON_SYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CBodyDlg bodydlg;
	CGarmentDlg garmentdlg;

	HICON m_hIcon;

	//两面版共有对象
	Body	*body;//人体
	NetGrid *netGrid;//网格


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabModel;
	afx_msg void OnTcnSelchangeModeltab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
