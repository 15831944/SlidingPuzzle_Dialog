﻿
// SlidingPuzzleDlg.h: 헤더 파일
//

#pragma once
enum Page {		// 게임 페이지
	pNull, pLOGO, pMenu, pNumber, pImage, pGame
};
struct Box {
	byte row;	// 퍼즐의 행
	byte col;		// 열
	byte digit;	// 순서
	CRect rect;	// 위치
};
enum DIRECTION {		// 박스의 방향
	dNull, dUp, dDown, dRight, dLeft
};

struct RANKING_ {
	int time;
	int count;
};


#define LOG_RECT_WIDTH 600
#define LOG_RECT_HEIGHT 400
#define MENU_RECT_WIDTH 750
#define MENU_RECT_HEIGHT 650

#define DEFAULT_BOX_WIDTH 120
#define DEFAULT_BOX_HEIGHT 120
#define DEFAULT_BOX_MARGIN 10
#define FRAME_OFFSET 80
#define TOTAL 850

#define RANKING_MAX  5

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
	CImage logo_img;
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
	CStatic i_static3, i_static4, i_static5, i_static_show;
	CButton radio3, radio4, radio5;
	CImage cm3, cm4, cm5;
	CRect static1, static2, static3;		// 이미지 클릭시 사각형
	//CButton start_btn;
	afx_msg void OnButton3Clicked();
	afx_msg void OnButton4Clicked();
	afx_msg void OnButton5Clicked();
	afx_msg void OnBnClickedImagebtn();
	
	// 퍼즐 박스들 생성
	struct Box box[25];

	afx_msg void GameInit(int line);	// 게임 화면 초기화
	int box_size;
	int box_margin;
	int box_width;
	int box_height;
	int box_offset;

	afx_msg void RadioLine(UINT id);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedgamebtn();

	CRect back_rect;	// 뒤로가기 사각형
	CRect start_rect;	// 게임화면의 시작
	CRect show_img;  // 이미지 보여주기
	// 메뉴로 돌아갔을 때 버튼 크기 조절
	CRect p_num_btn, p_img_btn, p_game_btn;		
	CTime start_tm;	// Timer

	afx_msg void Mixing();		// 박스 섞기 위한 함수
	DIRECTION RandomDirection(int row, int col);		// 랜덤으로 방향 정하기
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void ChangeLocation(Box* pBlank, int to_row, int to_col);		// 박스 위치 변경
	int mixing_count;		// Mixing count
	BOOL flag_play;		// 게임 시작 플래그
	BOOL end_play;		// 게임 종료 플래그

	int selected_digit;		// 선택된 박스의 숫자
	int selected_row;
	int selected_col;
	CRect selected_rect;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void IsFinish();
	// 박스 움직일 때 어느 방향에서 들어왔는지 체크
	DIRECTION CheckDirection(int row, int col);

	CRect explan_menu;		// ? 사각형, 게임 설명
	CImage img_arry[3];		// 이미지 배열
	int img_LineNumber;		// 이미지 페이지에서 숫자 라인
	virtual void Serialize(CArchive& ar);
	int count;
	CString ranking;
	afx_msg void LoadFile();		// 파일 가져오기
	afx_msg void SaveFile();		// 파일 저장하기
	struct RANKING_ Ranking[3][RANKING_MAX];
		CTimeSpan play_time;		// 게임 진행되는 시간
	afx_msg void OnDestroy();
};
