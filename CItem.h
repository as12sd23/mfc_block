#pragma once
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CLife.h"

class CItem
{
private:
	CBrush m_Color[7];
	CRect m_Rect[7];
	CRect m_judgement;
	bool m_Alive[7];
public:
	void SetItem();
	void SetRectItem(CBrick* brick, int i);
	void GetRectItem(int i);
	BOOL GetAlive(int number);
	void SetItemDraw(CDC* memDC);
	void GetItemEffect(CPlayerbar *player, CBall *ball[], CLife *life);
};

