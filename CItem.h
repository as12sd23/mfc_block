#pragma once
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CLife.h"
#include "CBall.h"

class CItem
{
private:
	CBrush m_Color[7];
	CRect m_Rect[7];
	CRect m_judgement;
	bool m_Alive[7];
	bool m_Laser = false;
	bool m_Catch = false;
	bool m_Long = false;
	bool m_Ball = false;
public:
	void SetItem();
	void SetRectItem(CRect brick, int i);
	void GetRectItem(int i);
	void SetItemDraw(CDC* memDC);
	BOOL GetAlive(int number);
	BOOL GetLaser();
	BOOL GetCatch();
	BOOL GetLong();
	BOOL GetBall();
	int GetItemEffect(CPlayerbar* player, CLife* life);
	void SetBallDestroy(CPlayerbar *player);
};