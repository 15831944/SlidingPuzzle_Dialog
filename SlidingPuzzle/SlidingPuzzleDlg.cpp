
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
	ON_BN_CLICKED(IDC_NUMBERbtn, &CSlidingPuzzleDlg::OnBnClickedNumberbtn)
	ON_BN_CLICKED(103, &CSlidingPuzzleDlg::OnButton3Clicked)
	ON_BN_CLICKED(104, &CSlidingPuzzleDlg::OnButton4Clicked)
	ON_BN_CLICKED(105, &CSlidingPuzzleDlg::OnButton5Clicked)
	ON_BN_CLICKED(IDC_IMAGEbtn, &CSlidingPuzzleDlg::OnBnClickedImagebtn)
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
	RECT rc;
	::GetWindowRect(m_hWnd, &rc);	// 현재 창 사이즈 rc에 얻어오기
	::MoveWindow(m_hWnd, rc.left, rc.top, rc.right - rc.left + 400, rc.bottom - rc.top + 400, TRUE);	// 창 늘리기

	mCurrentPage = pNull;
	SetPage(pLOGO);
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
		CRect rect;
		CBrush brush, * pBrush;
		switch (mCurrentPage) {
		case Page::pLOGO: 
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(204, 204, 255));
			pBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);
			brush.DeleteObject();

			brush.CreateSolidBrush(RGB(255, 255, 255));
			pBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect_Logo); // 화면이 늘어나도 가운데 정렬이 될 수 있도록 계산 필요
			
			dc.SelectObject(pBrush);
			brush.DeleteObject();
			break;
		
		case Page::pMenu:{
			
			/*CBrush brush, * pBrush;
			brush.CreateSolidBrush(RGB());*/
			CRect rect;
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(204, 204, 255));
			pBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);
			dc.SelectObject(pBrush);
			brush.DeleteObject();
			m_menu_rect.left = (rect.Width() - MENU_RECT_WIDTH) / 2;
			m_menu_rect.top = (rect.Height() - MENU_RECT_HEIGHT) / 2;
			m_menu_rect.right = m_menu_rect.left + MENU_RECT_WIDTH;
			m_menu_rect.bottom = m_menu_rect.top + MENU_RECT_HEIGHT;
			dc.RoundRect(m_menu_rect.left, m_menu_rect.top, m_menu_rect.right, m_menu_rect.bottom, 30, 30); // 100, 150, 450, 300
			break; 
		}
		case Page::pNumber: {
		
			DoubleBuffering();
			dc.TextOutW(200, 200, _T("숫자 퍼즐"));
			break;
		}
		case Page::pImage: {
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
	CButton* p, *q;
	int half_x, half_y;
	//mCurrentPage = pMenu;
	SetPage(pMenu);
	GetDlgItem(IDC_StartBtn)->ShowWindow(SW_HIDE);		// 첫 화면의 game start 버튼 숨기기
	
	// 버튼 위치 설정
	p = (CButton*)GetDlgItem(IDC_NUMBERbtn);
	p->ShowWindow(SW_SHOW);
	CRect rect, btn_img_rect, btn_rect;
	GetClientRect(&rect);					// 전체 화면 너비
	p->GetClientRect(&btn_rect);		// 숫자 버튼 크기 가져오기
	half_x = rect.Width() / 2;		
	half_y = rect.Height() / 2;	// 전체 화면 높이
	//show_rect.left = (rect.Width() - 400) / 2;
	//show_rect.top = (rect.Height() - 300) / 2;
	//show_rect.right = show_rect.left + 400;
	//show_rect.bottom = show_rect.top + 300;
	int offset = btn_rect.Height() + 100;
	p->MoveWindow(half_x - (btn_rect.Width()+100) - 60, half_y - btn_rect.Height() - offset, btn_rect.Width() + 100, btn_rect.Height() + 100);
	

	q = (CButton*)GetDlgItem(IDC_IMAGEbtn);
	q->ShowWindow(SW_SHOW);
	q->GetClientRect(&btn_img_rect);
	q->MoveWindow(half_x + 60, half_y - btn_img_rect.Height() - offset, btn_img_rect.Width() + 100, btn_img_rect.Height() + 100);
	
	Invalidate();
}


void CSlidingPuzzleDlg::OnSize(UINT nType, int cx, int cy)
{	// 윈도우 창이 변할 때마다 내부 컨트롤 키도 자동으로 움직이게 하는 함수
	//CDialogEx::OnSize(nType, cx, cy);

	//// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//CWnd* pCtl = GetDlgItem(IDC_StartBtn);
	//if (!pCtl) { return; }

	//CRect rectCtl;
	//pCtl->GetWindowRect(&rectCtl);
	//ScreenToClient(&rectCtl);

	//pCtl->MoveWindow(rectCtl.left, rectCtl.top, cx - 2 * rectCtl.left, cy - rectCtl.top - rectCtl.left, TRUE);
	
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


void CSlidingPuzzleDlg::OnBnClickedNumberbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetPage(pNumber);
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() / 2 -50;
	int height = rect.Height() / 2 + 60;
	// 아래 버튼들이 이미 그려져 있다면 다시 '숫자'버튼을 눌렀을 때 생성되지 않게 해야 한다. if문 사용...
	cbtn3.Create(_T("3X3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width - 120, height, width - 20 , height + 80), this, 103);
	cbtn4.Create(_T("4X4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width, height, width + 100, height + 80), this, 104);
	cbtn5.Create(_T("5X5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width + 120, height, width + 220, height + 80), this, 105);
}


// 해당 페이지  설정
void CSlidingPuzzleDlg::SetPage(Page page)
{
	// TODO: 여기에 구현 코드 추가.
	CRect rect, rect_btn;
	CButton* p;
	CClientDC dc(this);
	int width, height, offset_height;

	if (page == mCurrentPage) return;

	mCurrentPage = page;
	GetClientRect(&rect);
	switch (mCurrentPage) {
	case Page::pLOGO:
		p = (CButton*)GetDlgItem(IDC_StartBtn);
		p->GetWindowRect(&rect_btn);
		//ScreenToClient(rect_btn);

		width = rect_btn.Width();
		height = rect_btn.Height();

		offset_height = (rect.Height() - (LOG_RECT_HEIGHT + 60 + height)) / 2;


		rect_Logo.left = (rect.Width() - LOG_RECT_WIDTH) / 2;
		rect_Logo.top = (rect.Height() - LOG_RECT_HEIGHT) / 2 -offset_height;
		rect_Logo.right = rect_Logo.left + LOG_RECT_WIDTH;
		rect_Logo.bottom = rect_Logo.top + LOG_RECT_HEIGHT;
		
		rect_btn.left = rect_Logo.left + (rect_Logo.Width() - rect_Logo.Width() * 0.6) / 2;
		rect_btn.top = rect_Logo.bottom + 60;
		rect_btn.right = rect_btn.left + rect_Logo.Width() * 0.6; // width;
		rect_btn.bottom = rect_btn.top + rect_Logo.Height() * 0.25;
		p->MoveWindow(rect_btn);
		
		p->ShowWindow(SW_SHOW);
		break;
	case Page::pMenu:

		m_menu_rect.left = (rect.Width() - MENU_RECT_WIDTH) / 2;
		m_menu_rect.top = (rect.Height() - MENU_RECT_HEIGHT) / 2;
		m_menu_rect.right = m_menu_rect.left + MENU_RECT_WIDTH;
		m_menu_rect.bottom = m_menu_rect.top + MENU_RECT_HEIGHT;
		dc.RoundRect(m_menu_rect.left, m_menu_rect.top, m_menu_rect.right, m_menu_rect.bottom, 30, 30); 
		break;

	case Page::pNumber: 

		DoubleBuffering();
		dc.TextOutW(200, 200, _T("숫자 퍼즐"));
		break;
	
	case Page::pImage: {
		dc.TextOutW(200, 200, _T("이미지 퍼즐"));
		break;
	}

	}
}

void CSlidingPuzzleDlg::OnButton3Clicked() {
	m_LineNumber = 3;
	CString str;
	str.Format(_T("%d"), m_LineNumber);
	AfxMessageBox(str);
}
void CSlidingPuzzleDlg::OnButton4Clicked() {
	m_LineNumber = 4;
	AfxMessageBox(_T("123"));
}
void CSlidingPuzzleDlg::OnButton5Clicked() {
	m_LineNumber = 5;
	AfxMessageBox(_T("123"));
}

void CSlidingPuzzleDlg::OnBnClickedImagebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cbtn3.ShowWindow(SW_HIDE);
}
