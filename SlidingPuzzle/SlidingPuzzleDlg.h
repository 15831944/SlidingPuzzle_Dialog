﻿
// SlidingPuzzleDlg.h: 헤더 파일
//

#pragma once
enum Page {
	pNull, pLOGO, pMenu, pNumber, pImage, pGame
};
struct Box {
	byte row;	// 퍼즐의 행
	byte col;		// 열
	byte digit;	// 순서
	CRect rect;	// 위치
};

#define LOG_RECT_WIDTH 600
#define LOG_RECT_HEIGHT 400
#define MENU_RECT_WIDTH 700
#define MENU_RECT_HEIGHT 600

#define DEFAULT_BOX_WIDTH 120
#define DEFAULT_BOX_HEIGHT 120
#define DEFAULT_BOX_MARGIN 10
#define FRAME_OFFSET 50
#define TOTAL 850


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

	// 더블버퍼링으로 화면그리기
	void DoubleBuffering(CPaintDC *dc);
	
	// 숫자 퍼즐 라인 크기 저장
	int m_LineNumber;
	// 이미지 선택
	int m_Imgnum;
	afx_msg void OnBnClickedNumberbtn();
	// 해당 페이지 설정
	void SetPage(Page p);
	// 로고 사각형 좌표
	CRect rect_Logo;
	// 메뉴 화면 (둥근) 사각형
	CRect m_menu_rect;
	// 메뉴 화면 숫자 버튼
	CButton cbtn3, cbtn4, cbtn5;
	// 메뉴 화면 이미지 
	CStatic i_static3, i_static4, i_static5;
	CButton radio3, radio4, radio5;
	CImage cm3, cm4, cm5;
	CRect static1, static2, static3;
	//CButton start_btn;
	afx_msg void OnButton3Clicked();
	afx_msg void OnButton4Clicked();
	afx_msg void OnButton5Clicked();
	afx_msg void OnBnClickedImagebtn();
	
	// 퍼즐 박스들 생성
	struct Box box[25];
	afx_msg void GameInit(int line);
	int box_size;
	int box_margin;
	int box_width;
	int box_height;
	int box_offset;

	afx_msg void RadioLine(UINT id);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedgamebtn();
};
