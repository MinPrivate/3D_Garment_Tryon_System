#pragma once

#include "Display.h"
#include "Garment.h"




// CGarmentDlg 对话框

class CGarmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGarmentDlg)

public:
	CGarmentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGarmentDlg();

// 对话框数据
	enum { IDD = IDD_GARMENTTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


// 实现
public:

	//增加的成员变量
	Display *displayGarment;		//绘图对象
	CRect	m_rect;					//绘图窗口
	int		m_garmentRecord;			//绘图记录
	int		m_garmentBG;			//背景记录
	bool	m_isClear;				//是否清除
	
	//衣服对象
	Garment *garment;
	//body对象
	Body *body;
	//从父对话框传递生成的body
	void setBody(Body *tmpBody);

	//网格对象
	NetGrid *netGrid;
	//从父对话框传递生成的netgrid
	void setNetGrid(NetGrid *tmpNetGrid);

	//BoxCloth boxCloth;


	void Redraw();

public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CSliderCtrl m_XSlider;
	CSliderCtrl m_YSlider;
	CSliderCtrl m_ZSlider;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_ChangeBG;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
