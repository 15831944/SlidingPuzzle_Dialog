
// SlidingPuzzleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SlidingPuzzle.h"
#include "SlidingPuzzleDlg.h"
#include "afxdialogex.h"

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


// CSlidingPuzzleDlg 대화 상자



CSlidingPuzzleDlg::CSlidingPuzzleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLIDINGPUZZLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlidingPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSlidingPuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_StartBtn, &CSlidingPuzzleDlg::OnBnClickedStartbtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_NUMBER, &CSlidingPuzzleDlg::OnBnClickedNumber)
	ON_BN_CLICKED(IDC_IMAGE, &CSlidingPuzzleDlg::OnBnClickedImage)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSlidingPuzzleDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CSlidingPuzzleDlg 메시지 처리기

BOOL CSlidingPuzzleDlg::OnInitDialog()
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
	mCurrentPage = pLOGO;
	RECT rc;
	::GetWindowRect(m_hWnd, &rc);	// 현재 창 사이즈 rc에 얻어오기
	::MoveWindow(m_hWnd, rc.left, rc.top, rc.right - rc.left + 100, rc.bottom - rc.top + 100, TRUE);	// 창 늘리기

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSlidingPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSlidingPuzzleDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())  // 최소화 되었을 때 사용하는 루틴?
	{
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
	{	// 최소화가 되지 않은 경우에 여기서 작업
		/*RECT total_rect;
		CRect rect;
		GetWindowRect(&total_rect);
		GetClientRect(&rect);
		CPoint pt;
		pt.x = total_rect.left + (total_rect.right - total_rect.left) / 2 - rect.Width() / 2;
		pt.y = total_rect.top + (total_rect.bottom - total_rect.top) / 2 - rect.Height() / 2;
		rect.left = total_rect.right;*/
		switch (mCurrentPage) {
		case Page::pLOGO: {
		/*	GetDlgItem(IDC_NUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IMAGE)->ShowWindow(SW_HIDE);*/
			CRect rect;
			GetClientRect(&rect);
			dc.Rectangle(100, 100, 500, 250); // 화면이 늘어나도 가운데 정렬이 될 수 있도록 계산 필요
			dc.DrawText(_T("로고"), CRect(130, 130, 200, 200), DT_SINGLELINE);
			break;
		}
		case Page::pMenu:{
			GetDlgItem(IDC_StartBtn)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_NUMBER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_IMAGE)->ShowWindow(SW_SHOW);
			CRect rect, show_rect;
			GetClientRect(&rect);
			show_rect.left = rect.Width() / 2 - 175;
			show_rect.top = rect.Height() / 2 - 150;
			show_rect.right = rect.Width() / 2 + 175;
			show_rect.bottom = rect.Height() / 2 + 75;
			dc.RoundRect(show_rect.left, show_rect.top, show_rect.right, show_rect.bottom, 30, 30); // 100, 150, 450, 300
			break; }
		case Page::pNumber: {
			GetDlgItem(IDC_NUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IMAGE)->ShowWindow(SW_HIDE);
			DoubleBuffering();
			dc.TextOutW(200, 200, _T("숫자 퍼즐"));
			break;
		}
		case Page::pImage: {
			GetDlgItem(IDC_NUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IMAGE)->ShowWindow(SW_HIDE);
			dc.TextOutW(200, 200, _T("이미지 퍼즐"));
			break;
		}
		}
		
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSlidingPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CSlidingPuzzleDlg::OnBnClickedStartbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mCurrentPage = pMenu;
	Invalidate();
}


void CSlidingPuzzleDlg::OnSize(UINT nType, int cx, int cy)
{	// 윈도우 창이 변할 때마다 내부 컨트롤 키도 자동으로 움직이게 하는 함수
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CWnd* pCtl = GetDlgItem(IDC_StartBtn);
	if (!pCtl) { return; }

	CRect rectCtl;
	pCtl->GetWindowRect(&rectCtl);
	ScreenToClient(&rectCtl);

	pCtl->MoveWindow(rectCtl.left, rectCtl.top, cx - 2 * rectCtl.left, cy - rectCtl.top - rectCtl.left, TRUE);

	// 컨트롤 키가 아니라 일반 그림도 화면이 움직일 때마다 바뀌게 할려면 다시 그려야 하는건가?
	return;
}


// 더블버퍼링으로 화면그리기 
void CSlidingPuzzleDlg::DoubleBuffering()
{
	// TODO: 여기에 구현 코드 추가.
	CWnd* pWnd = NULL;

	pWnd = GetDlgItem(IDC_StartBtn);

	CDC* pDCc = pWnd->GetDC();
	CRect rect;

	pWnd->GetClientRect(&rect);

	CDC memDC;

	CBitmap* pOldBitmap, bitmap;
	memDC.CreateCompatibleDC(pDCc);
	bitmap.CreateCompatibleBitmap(pDCc, rect.right, rect.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);
	CPen* pOldPen = NULL;

	CBrush* pOldBrush = NULL;
	CPen penWhite(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brushWhite(RGB(255, 255, 255));

	pOldPen = memDC.SelectObject(&penWhite);
	pOldBrush = memDC.SelectObject(&brushWhite);
	memDC.Rectangle(0, 0, rect.right, rect.bottom);
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	pDCc->BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	bitmap.DeleteObject();
	memDC.DeleteDC();

	pWnd->ReleaseDC(pDCc);

}


void CSlidingPuzzleDlg::OnBnClickedNumber()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mCurrentPage = pNumber;
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW); // 여기서 보여지게 하는게 맞는건가.?

	
	//Invalidate();
}


void CSlidingPuzzleDlg::OnBnClickedImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mCurrentPage = pImage;
	
	Invalidate();
}


void CSlidingPuzzleDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CComboBox test;
	CString str;
	test.GetLBText(test.GetCurSel(), str);
	CClientDC dc(this);
	dc.TextOutW(100, 100, str);*/
}
