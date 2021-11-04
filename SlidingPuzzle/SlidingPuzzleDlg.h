
// SlidingPuzzleDlg.h: 헤더 파일
//

#pragma once
enum Page {
	pNull, pLOGO, pMenu, pNumber, pImage
};

#define LOG_RECT_WIDTH 550
#define LOG_RECT_HEIGHT 350
#define MENU_RECT_WIDTH 700
#define MENU_RECT_HEIGHT 600

// CSlidingPuzzleDlg 대화 상자
class CSlidingPuzzleDlg : public CDialogEx
{
// 생성입니다.
public:
	CSlidingPuzzleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLIDINGPUZZLE_DIALOG };
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
	enum Page mCurrentPage;

	afx_msg void OnBnClickedStartbtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 더블버퍼링으로 화면그리기
	void DoubleBuffering();
	
	// 숫자 퍼즐 라인 크기 저장
	int m_LineNumber;
	afx_msg void OnBnClickedNumberbtn();
	// 해당 페이지 설정
	void SetPage(Page p);
	// 로고 사각형 좌표
	CRect rect_Logo;
	// 메뉴 화면 사각형
	CRect m_menu_rect;
	// 메뉴 화면 숫자 버튼
	CButton cbtn3, cbtn4, cbtn5;
	afx_msg void OnButton3Clicked();
	afx_msg void OnButton4Clicked();
	afx_msg void OnButton5Clicked();
	afx_msg void OnBnClickedImagebtn();
};
