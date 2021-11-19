
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
	ON_BN_CLICKED(IDC_NUMBERbtn, &CSlidingPuzzleDlg::OnBnClickedNumberbtn)
	ON_BN_CLICKED(103, &CSlidingPuzzleDlg::OnButton3Clicked)
	ON_BN_CLICKED(104, &CSlidingPuzzleDlg::OnButton4Clicked)
	ON_BN_CLICKED(105, &CSlidingPuzzleDlg::OnButton5Clicked)
	ON_BN_CLICKED(IDC_IMAGEbtn, &CSlidingPuzzleDlg::OnBnClickedImagebtn)
	ON_CONTROL_RANGE(BN_CLICKED, 109, 111, &CSlidingPuzzleDlg::RadioLine)
	ON_WM_LBUTTONDOWN()
	  ON_BN_CLICKED(IDC_game_btn, &CSlidingPuzzleDlg::OnBnClickedgamebtn)
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
	::MoveWindow(m_hWnd, rc.left, rc.top, rc.right - rc.left + 430, rc.bottom - rc.top + 500, TRUE);	// 창 늘리기
	
	cm3.Load(_T(".\\Image\\Buri1.png"));
	cm4.Load(_T(".\\Image\\Taegeukgi.png"));
	cm5.Load(_T(".\\Image\\MFC.png"));
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
			brush.CreateSolidBrush(RGB(180, 198, 166));
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
			CRect rect;
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(180, 198, 166));
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
			CRect rect;
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(180, 198, 166));
			pBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);
			dc.SelectObject(pBrush);
			brush.DeleteObject();
			m_menu_rect.left = (rect.Width() - MENU_RECT_WIDTH) / 2;
			m_menu_rect.top = (rect.Height() - MENU_RECT_HEIGHT) / 2;
			m_menu_rect.right = m_menu_rect.left + MENU_RECT_WIDTH;
			m_menu_rect.bottom = m_menu_rect.top + MENU_RECT_HEIGHT;
			dc.RoundRect(m_menu_rect.left, m_menu_rect.top, m_menu_rect.right, m_menu_rect.bottom, 30, 30);
			break;
		}
		case Page::pImage: {
			CRect rect, img_rect, basic_rect;
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(180, 198, 166));
			pBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);
			dc.SelectObject(pBrush);
			brush.DeleteObject();
			m_menu_rect.left = (rect.Width() - MENU_RECT_WIDTH) / 2;
			m_menu_rect.top = (rect.Height() - MENU_RECT_HEIGHT) / 2;
			m_menu_rect.right = m_menu_rect.left + MENU_RECT_WIDTH;
			m_menu_rect.bottom = m_menu_rect.top + MENU_RECT_HEIGHT;
			dc.RoundRect(m_menu_rect.left, m_menu_rect.top, m_menu_rect.right, m_menu_rect.bottom, 30, 30);

			i_static3.GetClientRect(&img_rect);

			CPen pen, * pPen;
			pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			pPen = dc.SelectObject(&pen);
			if (m_Imgnum == 1) {
				dc.Rectangle(static1.left - 1, static1.top - 1, static1.right + 1, static1.bottom + 1);
			}
			if (m_Imgnum == 2) {
				dc.Rectangle(static2.left - 1, static2.top - 1, static2.right + 1, static2.bottom + 1);
			}
			if (m_Imgnum == 3) {
				dc.Rectangle(static3.left - 1, static3.top - 1, static3.right + 1, static3.bottom + 1);
			}
			dc.SelectObject(pPen);
			pen.DeleteObject();
			i_static3.SetBitmap(cm3);
			i_static4.SetBitmap(cm4);
			i_static5.SetBitmap(cm5);
			SetStretchBltMode(i_static3.GetDC()->m_hDC, COLORONCOLOR);
			SetStretchBltMode(i_static4.GetDC()->m_hDC, COLORONCOLOR);
			SetStretchBltMode(i_static5.GetDC()->m_hDC, COLORONCOLOR);
			cm3.Draw(i_static3.GetDC()->m_hDC, 0, 0, img_rect.Width(), img_rect.Height());
			cm4.Draw(i_static4.GetDC()->m_hDC, 0, 0, img_rect.Width(), img_rect.Height());
			cm5.Draw(i_static5.GetDC()->m_hDC, 0, 0, img_rect.Width(), img_rect.Height());
			break;
		}
		case Page::pGame:
			CRect rect;
			DoubleBuffering(&dc);
			GetClientRect(&rect);
			brush.CreateSolidBrush(RGB(255, 194, 134));
			pBrush = dc.SelectObject(&brush);
			back_rect = CRect(20, rect.Height() - 70, 70, rect.Height() - 20);
			dc.FillRect(&back_rect, &brush);
			dc.SetBkColor(RGB(255, 194, 134));
			dc.DrawTextW(_T("back"), back_rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			
			dc.SelectObject(pBrush);
			brush.DeleteObject();

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
	CButton* p, *q, *x;
	
	int half_x, half_y;
	//mCurrentPage = pMenu;
	SetPage(pMenu);
	GetDlgItem(IDC_StartBtn)->ShowWindow(SW_HIDE);		// 첫 화면의 game start 버튼 숨기기
	
	// 버튼 위치 설정
	p = (CButton*)GetDlgItem(IDC_NUMBERbtn);
	p->ShowWindow(SW_SHOW);
	CRect rect, btn_rect, btn_img_rect, btn_start;
	GetClientRect(&rect);					// 전체 화면 너비
	p->GetClientRect(&btn_rect);		// 숫자 버튼 크기 가져오기
	p_num_btn = btn_rect;
	half_x = rect.Width() / 2;		
	half_y = rect.Height() / 2;	// 전체 화면 높이
	int offset = btn_rect.Height() + 100;
	p->MoveWindow(half_x - (btn_rect.Width()+100) - 60, half_y - btn_rect.Height() - offset, btn_rect.Width() + 100, btn_rect.Height() + 100);
	
	q = (CButton*)GetDlgItem(IDC_IMAGEbtn);
	q->ShowWindow(SW_SHOW);
	q->GetClientRect(&btn_img_rect);
	p_img_btn = btn_img_rect;
	q->MoveWindow(half_x + 60, half_y - btn_img_rect.Height() - offset, btn_img_rect.Width() + 100, btn_img_rect.Height() + 100);
	
	x = (CButton*)GetDlgItem(IDC_game_btn);
	x->ShowWindow(SW_SHOW);
	x->GetClientRect(&btn_start);
	p_game_btn = btn_start;
	x->MoveWindow(half_x - 100, half_y + 180, btn_start.Width() + 100, btn_start.Height() + 50);
	//WS_DISABLED
	Invalidate();
}


// 더블버퍼링으로 화면그리기 
void CSlidingPuzzleDlg::DoubleBuffering(CPaintDC* dc)
{
	/*CWnd* pWnd = NULL;

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

	pWnd->ReleaseDC(pDCc);*/
	struct Box* b;
	CString str, str_time;
	//CBrush brush, * pBrush;
	CBrush game_background, game_screen, game_box;
	CRect rect, rc;
	CBitmap* old_bitmap, bitmap;
	GetClientRect(&rect);
	CDC mem_dc;
	mem_dc.CreateCompatibleDC(dc);
	bitmap.CreateCompatibleBitmap(dc, rect.right, rect.bottom);
	old_bitmap = mem_dc.SelectObject(&bitmap);

	game_background.CreateSolidBrush(RGB(180, 198, 166));	// 다이얼로그 바탕 색 지정
	mem_dc.SelectObject(&game_background);

	mem_dc.FillRect(&rect, &game_background);		// 바탕색 칠함
	
	// 타이머
	mem_dc.SetBkColor(RGB(180, 198, 166));
	str_time.Format(_T("00:00:00"));
	mem_dc.DrawTextW(str_time, CRect(10, 10, 100, 20), DT_SINGLELINE | DT_VCENTER);

	//GetClientRect(&rc);
	// 게임 화면 바탕을 위한 그리기 설정
	game_screen.CreateSolidBrush(RGB(255, 241, 175));
	int size = box_size * box_size;
	rc.left = box_offset - box_margin;
	rc.top = box_offset - box_margin;
	rc.right = box_offset + box_size * box_width;
	rc.bottom = box_offset + box_size * box_height;
	mem_dc.FillRect(&rc, &game_screen);

	// 폰트 지정
	CFont font, * pFont;
	font.CreatePointFont(200, _T("Times New Roman"));
	pFont = mem_dc.SelectObject(&font);
	
	// 박스 그리기
	game_box.CreateSolidBrush(RGB(102, 128, 106));
	for (int i = size - 1; i >= 0; i--) {	// 한 칸은 남겨 두어야 하기 때문에 뒤에서부터
		b = &box[i];
		if (b->digit != size) {
			mem_dc.FillRect(&b->rect, &game_box);
			mem_dc.SetTextColor(RGB(255, 255, 255));		// 박스 안 글자 색 지정
			mem_dc.SetBkColor(RGB(102, 128, 106));
			str.Format(_T("%d"), b->digit);
			mem_dc.DrawTextW(str, &b->rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
		
	}
	dc->BitBlt(0, 0, rect.right, rect.bottom, &mem_dc, 0, 0, SRCCOPY);
	mem_dc.SelectObject(old_bitmap);
	bitmap.DeleteObject();
	mem_dc.DeleteDC();

	game_background.DeleteObject();
	game_screen.DeleteObject();
	game_box.DeleteObject();
}


void CSlidingPuzzleDlg::OnBnClickedNumberbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetPage(pNumber);
	//CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() / 2 -50;
	int height = rect.Height() / 2 + 40;
	// 아래 버튼들이 이미 그려져 있다면 다시 '숫자'버튼을 눌렀을 때 생성되지 않게 해야 한다. if문 사용...
	
	if (cbtn3.GetSafeHwnd() == NULL){
	cbtn3.Create(_T("3X3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width - 120, height, width - 20, height + 80) , this, 103);
	cbtn4.Create(_T("4X4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width, height, width + 100, height + 80), this, 104);
	cbtn5.Create(_T("5X5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(width + 120, height, width + 220, height + 80), this, 105);
	}
	
		if (radio3.GetSafeHwnd() != NULL) {
			radio3.ShowWindow(SW_HIDE);
			radio4.ShowWindow(SW_HIDE);
			radio5.ShowWindow(SW_HIDE);
		}
		if (i_static3.GetSafeHwnd() != NULL) {
			i_static3.ShowWindow(SW_HIDE);
			i_static4.ShowWindow(SW_HIDE);
			i_static5.ShowWindow(SW_HIDE);
		}

		if (cbtn3.GetSafeHwnd() != NULL) {
			cbtn3.ShowWindow(SW_SHOW);
			cbtn4.ShowWindow(SW_SHOW);
			cbtn5.ShowWindow(SW_SHOW);
		}
	
	Invalidate();
}

void CSlidingPuzzleDlg::OnBnClickedImagebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetPage(pImage);
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() / 2 - 50;
	int height = rect.Height() / 2 + 40;
	static1 = CRect(width - 120, height, width - 20, height + 80);
	static2 = CRect(width, height, width + 100, height + 80);
	static3 = CRect(width + 120, height, width + 220, height + 80);
	CRect img_rect;
	if (i_static3.GetSafeHwnd() == NULL) {
		i_static3.Create(NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(width - 120, height, width - 20, height + 80), this, 106);
		i_static4.Create(NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(width, height, width + 100, height + 80), this, 107);
		i_static5.Create(NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(width + 120, height, width + 220, height + 80), this, 108);
		radio3.Create(_T("3X3"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(width - 120, height + 100, width - 20, height + 120), this, 109);
		radio4.Create(_T("4X4"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(width, height + 100, width + 100, height + 120), this, 110);
		radio5.Create(_T("5X5"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(width + 120, height + 100, width + 220, height + 120), this, 111);
	}
		if (radio3.GetSafeHwnd() != NULL) {
			radio3.ShowWindow(SW_SHOW);
			radio4.ShowWindow(SW_SHOW);
			radio5.ShowWindow(SW_SHOW);
		}
		if (cbtn3.GetSafeHwnd() != NULL) { // 숫자 버튼이 있으면 
			cbtn3.ShowWindow(SW_HIDE);
			cbtn4.ShowWindow(SW_HIDE);
			cbtn5.ShowWindow(SW_HIDE);
		}
		
		if (i_static3.GetSafeHwnd() != NULL) {
			i_static3.ShowWindow(SW_SHOW);
			i_static4.ShowWindow(SW_SHOW);
			i_static5.ShowWindow(SW_SHOW);
		}

	Invalidate();
}

// 해당 페이지  설정
void CSlidingPuzzleDlg::SetPage(Page page)
{
	// TODO: 여기에 구현 코드 추가.
	CRect rect, rect_btn;
	CButton* p;
	CClientDC dc(this);
	int width, height;
	float offset_height;
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

		offset_height = (rect.Height() - (LOG_RECT_HEIGHT + 60 + LOG_RECT_HEIGHT*0.25)) / 2;
		
		rect_Logo.left = (rect.Width() - LOG_RECT_WIDTH) / 2;
		rect_Logo.top = (rect.Height() - LOG_RECT_HEIGHT) / 2 - offset_height;
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
		break;
	
	case Page::pImage: {
		break;
	}

	}
}

void CSlidingPuzzleDlg::OnButton3Clicked() {
	m_LineNumber = 3;	
}
void CSlidingPuzzleDlg::OnButton4Clicked() {
	m_LineNumber = 4;
}
void CSlidingPuzzleDlg::OnButton5Clicked() {
	m_LineNumber = 5;
}



void CSlidingPuzzleDlg::GameInit(int line) {		// 라인에 맞춰 박스 초기 세팅하기
	struct Box* b;
	CRect rect;
	GetClientRect(&rect);
	box_size = line;
	box_margin = DEFAULT_BOX_MARGIN;
	box_offset = FRAME_OFFSET;
	box_width = (rect.Width() - box_offset * 2) / box_size;		// 정해진 게임 화면을 라인만큼 분활
	box_height = (rect.Height() - box_offset * 2) / box_size;
	
	for (int row = 0; row < box_size; row++) {
		for (int col = 0; col < box_size; col++) {
			b = &box[row * box_size + col];
			b->row = row;
			b->col = col;
			b->digit = row * box_size + col + 1;
			b->rect.left = col * box_width + box_offset;
			b->rect.top = row * box_height + box_offset;
			b->rect.right = b->rect.left + box_width - box_margin;
			b->rect.bottom = b->rect.top + box_height - box_margin;
		}
	}
}


// 이미지 페이지에서 발생하는 라인 점검
void CSlidingPuzzleDlg::RadioLine(UINT id) {
	switch (id) {
	case 109:
		m_LineNumber = 3;
		break;
	case 110:
		m_LineNumber = 4;
		break;
	case 111:
		m_LineNumber = 5;
		break;
	}
}

void CSlidingPuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (mCurrentPage == pImage) {

		if (PtInRect(static1, point)) {
			m_Imgnum = 1;	// 첫번째 이미지
		}

		if (PtInRect(static2, point)) {
			m_Imgnum = 2;	// 두번째 이미지
		}
		if (PtInRect(static3, point)) {
			m_Imgnum = 3;	// 세번째 이미지
		}
	}
	CString str;
	str = _T("메뉴로 돌아가겠습니까?");
	if (mCurrentPage == pGame) {
		if (PtInRect(back_rect, point)) {
			if (AfxMessageBox(str, MB_YESNO | MB_ICONQUESTION) == IDYES) {
			//	mCurrentPage = pMenu;
				OnBnClickedStartbtn();
				//Invalidate();
			}
			else {
				return;
			}
			
		}
	}
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSlidingPuzzleDlg::OnBnClickedgamebtn()
{
	if (mCurrentPage == pMenu) {
		AfxMessageBox(_T("숫자 or 이미지를 선택해주세요"));
		return;
	}
	if (mCurrentPage == pNumber) {
		if (!m_LineNumber) {
			AfxMessageBox(_T("숫자를 선택해주세요"));
			return;
		}
		if (m_LineNumber) {	// 숫자 선택이 되었다면
			GameInit(m_LineNumber);
			mCurrentPage = pGame;
			cbtn3.ShowWindow(SW_HIDE);
			cbtn4.ShowWindow(SW_HIDE);
			cbtn5.ShowWindow(SW_HIDE);
		}
	}
	if (mCurrentPage == pImage) {
		if (!m_Imgnum || !m_LineNumber) {		// 숫자 버튼을 누르고 이미지로 넘어오게 되면 LineNumber 섞일 수도 있으니 주의
			AfxMessageBox(_T("이미지와 숫자를 선택해주세요"));
			return;
		}
		GameInit(m_LineNumber);
		mCurrentPage = pGame;
		i_static3.ShowWindow(SW_HIDE);
		i_static4.ShowWindow(SW_HIDE);
		i_static5.ShowWindow(SW_HIDE);
		radio3.ShowWindow(SW_HIDE);
		radio4.ShowWindow(SW_HIDE);
		radio5.ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_NUMBERbtn)->MoveWindow(p_num_btn);
	GetDlgItem(IDC_IMAGEbtn)->MoveWindow(p_img_btn);
	GetDlgItem(IDC_game_btn)->MoveWindow(p_game_btn);

	GetDlgItem(IDC_NUMBERbtn)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IMAGEbtn)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_game_btn)->ShowWindow(SW_HIDE);
	/*CRect rect;
	GetClientRect(&rect);
	m_back.Create(_T("👈"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, rect.Height() - 70, 70, rect.Height() - 20), this, 112);*/
	Invalidate();
}
