
// GlimProjectDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "GlimProject.h"
#include "GlimProjectDlg.h"
#include "afxdialogex.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimProjectDlg 대화 상자



CGlimProjectDlg::CGlimProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMPROJECT_DIALOG, pParent)
	, m_x1(0) //EDIT 좌표를 받기 위한 변수 초기화
	, m_y1(0)
	, m_x2(0)
	, m_y2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//EDIT과 좌표 연결
	DDX_Text(pDX, IDC_EDIT1, m_x1);
	DDX_Text(pDX, IDC_EDIT2, m_y1);
	DDX_Text(pDX, IDC_EDIT3, m_x2);
	DDX_Text(pDX, IDC_EDIT4, m_y2);
}

BEGIN_MESSAGE_MAP(CGlimProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimProjectDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimProjectDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimProjectDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGlimProjectDlg 메시지 처리기

BOOL CGlimProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 960, 640);


	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 50, 960, 640);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGlimProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pDlgImage;
}


void CGlimProjectDlg::OnBnClickedBtnDraw()
{	
	//시작 좌표 가져오기
	m_x1 = GetDlgItemInt(IDC_EDIT1);
	m_y1 = GetDlgItemInt(IDC_EDIT2);

	//이미지 데이터 가져오기
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	int nGray = 128;

	//원 그리기
	memset(fm, 0, nWidth*nHeight);
	radius = rand() % 50 + 10;
	drawCircle(fm, m_x1, m_y1, radius, nGray);

	//이미지 갱신
	m_pDlgImage->Invalidate();
}

void CGlimProjectDlg::OnBnClickedBtnAction()
{
	//종료 좌표 가져오기
	m_x2 = GetDlgItemInt(IDC_EDIT3);
	m_y2 = GetDlgItemInt(IDC_EDIT4);

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();

	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	int nGray = 128;

	memset(fm, 0, nWidth * nHeight);

	//시작 좌표에서 종료 좌표까지 n번 옮기기
	int n = 10;
	int dx = (m_x2 - m_x1) / (n - 1);
	int dy = (m_y2 - m_y1) / (n - 1);

	for (int i = 0; i < n; i++)
	{
		memset(fm, 0xff, nWidth * nHeight);

		int CenterX = m_x1 + i * dx;
		int CenterY = m_y1 + i * dy;

		drawCircle(fm, CenterX, CenterY, radius, nGray);

		m_pDlgImage->Invalidate();
		m_pDlgImage->UpdateWindow();

		CString strFileName;
		strFileName.Format(_T("C:\\image\\save_%d.bmp"), i);
		m_pDlgImage->m_image.Save(strFileName);

		Sleep(500);
	}

}


void CGlimProjectDlg::OnBnClickedBtnOpen()
{

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image Files (*.bmp; *.jpg)|*.bmp;*.jpg|All Files (*.*)|*.*||"));

	if (IDOK == dlg.DoModal())
	{
		CString img_path = dlg.GetPathName();
		m_pDlgImage->m_image.Load(img_path);

		centerCircle();
	}
}

void CGlimProjectDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_pDlgImage->m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

bool CGlimProjectDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	int dX = i - nCenterX;
	int dY = j - nCenterY;
	int dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}
	return bRet;
}

void CGlimProjectDlg::InitImage()
{
	int nWidth = 960;
	int nHeight = 640;
	int nBpp = 8;

	m_pDlgImage->m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_pDlgImage->m_image.SetColorTable(0, 255, rgb);
	}

	int nPitch = m_pDlgImage->m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

#include <iostream>
using namespace std;

void CGlimProjectDlg::centerCircle()
{
	//특정 패턴의 중앙 좌표 찾기 와 Elipse활용을 하기 위해 추가한 기능
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	int nGray = 128;

	CRect rect(0, 0, nWidth, nHeight); //검사할 영역 생성
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] == nGray) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;
	
	m_pDlgImage->Invalidate();
	m_pDlgImage->UpdateWindow();

	drawCross(dCenterX, dCenterY);

	cout << "중심좌표:" << dCenterX << "," << dCenterY << endl;

	InitImage();
}

void CGlimProjectDlg::drawCross(double dCenterX, double dCenterY)
{
	CDC* pDc = m_pDlgImage->GetDC();

	int nCenterX = static_cast<int>(dCenterX);
	int nCenterY = static_cast<int>(dCenterY);

	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = pDc->SelectObject(&pen);

	pDc->MoveTo(nCenterX - 5, nCenterY - 5);
	pDc->LineTo(nCenterX + 5, nCenterY + 5);
	pDc->MoveTo(nCenterX - 5, nCenterY + 5);
	pDc->LineTo(nCenterX + 5, nCenterY - 5);

	pDc->SelectObject(pOldPen);
	m_pDlgImage->ReleaseDC(pDc);
}
