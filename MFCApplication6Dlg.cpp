
// MFCApplication6Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication6.h"
#include "MFCApplication6Dlg.h"
#include "afxdialogex.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CBall.h"
#include "CItem.h"
#include "CLife.h"
#include "CLaser.h"

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
public:
	void Stage(int Step);
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


// CMFCApplication6Dlg 대화 상자



CMFCApplication6Dlg::CMFCApplication6Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION6_DIALOG, pParent)
	, m_Edit_SCORE(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_Edit_SCORE);
}

BEGIN_MESSAGE_MAP(CMFCApplication6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTT_START, &CMFCApplication6Dlg::OnClickedButtStart)
	ON_BN_CLICKED(IDC_BUTT_EXIT, &CMFCApplication6Dlg::OnClickedButtExit)
END_MESSAGE_MAP()


// CMFCApplication6Dlg 메시지 처리기

BOOL CMFCApplication6Dlg::OnInitDialog()
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
	GetDlgItem(IDC_STATIC_SCORE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(FALSE);

	CClientDC dc(this);
	memDC.CreateCompatibleDC(&dc);
	bm.CreateCompatibleBitmap(&dc, 1920, 1080);
	memDC.SelectObject(&bm);

	m_background.CreateSolidBrush(RGB(255, 255, 255));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication6Dlg::OnPaint()
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
HCURSOR CMFCApplication6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CMFCApplication6Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		switch (pMsg->wParam)
		{
		case VK_RIGHT:
			if (m_Catch || m_GameStart)
			{
				m_Player.SetPlayerBar_Move(8);
				for (int i = 0; i < 3; i++)
				{
					if(m_Ball[i].GetAlive())
						m_Ball[i].SetBallMove(10, 0, m_Item.GetCatch());
				}
			}
			else
			m_Player.SetPlayerBar_Move(10);
			break;
		case VK_LEFT:
			if (m_Catch || m_GameStart)
			{
				m_Player.SetPlayerBar_Move(-8);
				for (int i = 0; i < 3; i++)
				{
					if (m_Ball[i].GetAlive())
					{
						m_Ball[i].SetBallMove(-10, 0, m_Item.GetCatch());
					}
				}
			}
			else
				m_Player.SetPlayerBar_Move(-10);
			break;
		case VK_UP:
			if (m_Catch || m_GameStart)
			{
				m_GameStart = false;
				m_Catch = false;
				for (int i = 0; i < 3; i++)
				{
					if (m_Ball[i].GetAlive())
					{
						m_Ball[i].SetStart(m_Item.GetCatch());
					}
				}
			}
			if (m_Item.GetLaser())
			{
				if (m_Laser_Timer >= 100)
				{
					for (int i = 0; i < 3; i++)
					{
						if (m_Laser[i].GetAlive() == false)
						{
							m_Laser[i].SetLaser(m_Player.GetPlayerInfo());
							m_Laser_Timer = 0;
						}
					}
				}
			}
			break;
		case VK_ESCAPE:
			KillTimer(1);
			OnOK();
			break;
		}
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCApplication6Dlg::OnClickedButtStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_SCORE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_SCORE)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_START)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->ShowWindow(FALSE);



	GetDlgItem(IDC_EDIT_SCORE)->SetFocus();
	Stage(1);
	for (int i = 0; i < 3; i++)
	{
		m_Ball[i].SetInfo();
		m_Laser[i].SetInfo();
	}
	for (int i = 0; i < 91; i++)
	{
		m_block[i].SetInfo();
	}
	m_Player.SetInfo();
	m_Life.SetInfo();
	m_Item.SetItem();
	m_GameStart = true;
	m_background_Size = CRect(0, 0, 900, 800);
	m_Player.SetPlayerBar(m_background_Size.Width(), m_background_Size.Height());
	m_Ball[0].SetBall(m_background_Size.Width(), m_background_Size.Height());
	SetTimer(1, 1, NULL);
}


void CMFCApplication6Dlg::OnClickedButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CMFCApplication6Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static int Stage_Count = 1, Ball_Timer = 0;
	int a = 0;
	Ball_Timer++;
	m_Laser_Timer++;
	m_CatchTimer++;
	m_BallSpeedUp++;
	CClientDC dc(this);
	memDC.SelectObject(&m_background);
	memDC.Rectangle(m_background_Size);
	m_Life.SetLife(m_background_Size.Width(),m_background_Size.Height());
	if (m_Stage_Turn)
	{
		if (Stage_Count > 2)
			Stage_Count = 1;
		Stage(Stage_Count);
		m_GameStart = true;
	}
	for (int i = 0; i < 91; i++)
	{
		m_block[i].SetDrawBrick(&memDC);
		for(int j = 0;j < 3;j++)
			m_Laser[j].brick_destroy(&m_block[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		m_Laser[i].SetDraw(&memDC);
	}
	m_Player.SetPlayerBar_Draw(&memDC);

	if (Ball_Timer >= 100)
	{
		m_Player.SetPlayerLeft(m_Item.GetCatch());
		Ball_Timer = 0;
	}

	int item_random = 100;
	bool bounce = true;
	for (int i = 0; i < 3; i++)
	{
		if (m_BallSpeedUp > 2000 && m_Catch == false)
		{
			m_Ball[i].SetSpeedUp();
			m_BallSpeedUp = 0;
		}
		m_Ball[i].SetBall_Move();
		for (int j = 0; j < 91; j++)
		{
			item_random = m_Ball[i].SetBrick_judgement(&m_block[j], bounce);
			if (item_random >= 0 && item_random < 7 && m_Item.GetAlive(item_random) == false)
			{
				m_Item.SetRectItem(m_block[j].GetBrickInfo(), item_random);
			}
			UpdateData(TRUE);
			if (item_random < 100)
			{
				m_Edit_SCORE += 20;
				bounce = false;
			}
			UpdateData(FALSE);
		}
		bounce = m_Ball[i].SetPlayerJudgement(&m_Player, m_Item.GetCatch(), m_CatchTimer);
		if (bounce && m_CatchTimer > 200)
		{
			m_Catch = true;
			m_CatchTimer = 0;
		}
		m_Ball[i].SetDraw(&memDC);
	}

	m_Item.SetItemDraw(&memDC);

	for (int i = 0; i < 91; i++)
	{
		if (m_block[i].GetAlive())
			a++;
	}
	if (a == 0)
	{
		Stage_Count++;
		m_Stage_Turn = true;
		MessageBox("GAME CLEAR", "알림", NULL);
	}

	int item = m_Item.GetItemEffect(&m_Player, &m_Life);
	if (item == 1)
	{
		for (int i = 0; i < 91; i++)
			m_block[i].GetBrick();
		m_Stage_Turn = true;
		Stage_Count++;
	}
	else if (item == 4)
	{
		for (int i = 0; i < 3; i++)
		{
			m_Ball[i].SetSpeedSlow();
		}
	}
	else if (item == 6)
	{
		int ball = 0, number = 5;
		for (int i = 0; i < 3; i++)
		{
			if (m_Ball[i].GetAlive())
			{
				ball++;
				number = 0;
			}
		}
		if (ball == 1)
		{
			int ballCountNumber = 0;
			for (int i = 0; i < 3; i++)
			{
				if (i != number)
				{
					if(ballCountNumber == 0)
						m_Ball[i].SetSplitBall(m_Ball[number].GetXSpeed() + 1, m_Ball[number].GetYSpeed(), m_Ball[number].GetInfo());
					else
						m_Ball[i].SetSplitBall(m_Ball[number].GetXSpeed() - 1, m_Ball[number].GetYSpeed(), m_Ball[number].GetInfo());
					ballCountNumber++;
				}
			}
		}
	}

	m_Life.SetDraw(&memDC);
	a = 0;
	for (int i = 0; i < 3; i++)
	{
		if (m_Ball[i].GetAlive())
			a++;
	}
	if (a == 0)
	{
		if (m_Life.SetDelete())
		{
			m_GameStart = true;
			m_Player.SetPlayerBar(m_background_Size.Width(), m_background_Size.Height());
			m_Ball[0].SetBall(m_background_Size.Width(), m_background_Size.Height());
			m_Item.SetBallDestroy(&m_Player);
		}
		else
		{
			KillTimer(1);
			MessageBox("GAME OVER", "알림", NULL);
			OnOK();
		}
	}
	dc.BitBlt(0, 0, 900, 800, &memDC, 0, 0, SRCCOPY);
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication6Dlg::Stage(int Step)
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	switch (Step)
	{
	case 1:
	{
		x = 2, y = 100;
		for (int i = 0; i < 91; i++)
		{
			m_block[i].SetBrick(x, y);
			x += 69;
			if (x >= 897)
			{
				x = 2;
				y += 31;
			}
		}
		break;
	}
	case 2:
	{
		x = 2, y = 60;
		int a = 0;
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < i + i; j++)
			{
				m_block[a++].SetBrick(x, y);
				x += 69;
			}
			x = 2;
			y += 31;
		}
		break;
	}
	}
}
