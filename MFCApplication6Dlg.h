
// MFCApplication6Dlg.h: 헤더 파일
//

#pragma once
#include "CBrick.h"
#include "CBall.h"
#include "CPlayerbar.h"
#include "CItem.h"
#include "CLife.h"

// CMFCApplication6Dlg 대화 상자
class CMFCApplication6Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication6Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };
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
	CBitmap bm;
	CDC memDC;
	CBrush m_background;
	CBrick m_block[91];
	CPlayerbar m_Player;
	CRect m_background_Size;
	CBall m_Ball[3];
	CItem m_Item;
	CLife m_Life;
	bool m_GameStart = false;
	bool m_Stage_Turn = false;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedButtStart();
	afx_msg void OnClickedButtExit();
	void Stage(int step);
	int m_Edit_SCORE;
};
