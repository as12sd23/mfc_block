#pragma once
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"
#include "CLife.h"

class CBall
{
private:
	int x = 0, y = 0;
	int saveX = 0, saveY = 0;
	CRect m_Ball;
	CRect m_block_judgement;
	CBrush m_Ball_Brush;
	bool m_Alive = false;
public:
	void SetSpeedUp();
	void SetInfo();
	void SetBallMove(int a, int b, bool Catch );
	void SetBall(int Center_X, int Center_Y);
	void GetBall();
	int SetBrick_judgement(CBrick *brick, bool bounce);
	BOOL SetPlayerJudgement(CPlayerbar* player, bool Catch, int Timer);
	void SetBall_Move();
	void SetDraw(CDC *memDC);
	BOOL GetAlive();
	void SetStart(bool Catch);
	void SetItemBall(CRect ball);
	CRect GetInfo();
	void SetItemBallXSpeed(int speed);
	void SetItemBallYSpeed(int speed);
	int GetXSpeed();
	int GetYSpeed();
	void SetSpeedSlow();
	void SetSplitBall(int Speedx, int Speedy, CRect ball);
};