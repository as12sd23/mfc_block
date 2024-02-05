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
	bool m_ball = false;
public:
	void SetItem();
	void SetRectItem(CBrick* brick, int i);
	void GetRectItem(int i);
	void SetItemDraw(CDC* memDC);
	BOOL GetAlive(int number);
	BOOL GetLaser();
	int GetItemEffect(CPlayerbar* player, CLife* life, CBall ball[]);
};