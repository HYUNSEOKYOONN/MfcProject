﻿
// GlimProjectDlg.h: 헤더 파일
//

#pragma once
#include "CDlgImage.h"

// CGlimProjectDlg 대화 상자
class CGlimProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CDlgImage* m_pDlgImage;
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void InitImage();
	void centerCircle();
	void drawCross(double dCenterX, double dCenterY);
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int radius;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
};
