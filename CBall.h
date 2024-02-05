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
	bool m_Catch = false;
public:
	void SetBallMove(int x, int y );
	void SetBall(int Center_X, int Center_Y);
	void GetBall();
	BOOL SetBrick_judgement(CBrick *brick, CPlayerbar *player, CItem *item);
	void SetBall_Move();
	void SetDraw(CDC *memDC);
	BOOL GetAlive();
	void SetStart(CPlayerbar *player);
	void SetItemBall(CBall *ball);
	CRect GetInfo();
	void SetItemBallXSpeed(int speed);
	void SetItemBallYSpeed(int speed);
	int GetXSpeed();
	int GetYSpeed();
};