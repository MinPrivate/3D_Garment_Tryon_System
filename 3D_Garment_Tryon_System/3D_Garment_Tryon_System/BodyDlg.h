#pragma once

#include "Display.h"
#include "Body.h"

// CBodyDlg 对话框

class CBodyDlg : public CDialogEx
{

	DECLARE_EASYSIZE

	DECLARE_DYNAMIC(CBodyDlg)

public:
	CBodyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBodyDlg();

// 对话框数据
	enum { IDD = IDD_BODYTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()



// 实现
public:

	//增加的成员变量
	Display *displayBody;		//绘图对象
	CRect	m_rect;				//绘图窗口
	int		m_bodyRecord;			//绘图记录
	int		m_bodyBG;				//背景记录
	bool	m_isClear;				//判断是否清除

	//int		m_nHitTest;


	//body对象
	Body *body;
	//从父对话框传递生成的body
	void setBody(Body *tmpBody);

	void Redraw();



public:
	afx_msg void OnBnClickedBodystartbut();
	afx_msg void OnBnClickedBodysimplybut();
	afx_msg void OnBnClickedBodycompletebut();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider6(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_XSlider;
	CSliderCtrl m_ZSlider;
	CSliderCtrl m_YSlider;
	CComboBox m_ChangeBG;
	virtual BOOL OnInitDialog();
	CSliderCtrl m_HeightSlider;
	CSliderCtrl m_ChestSlider;
	CSliderCtrl m_WaistSlider;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
