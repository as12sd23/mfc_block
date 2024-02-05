#pragma once
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"

class CLaser
{
private:
	CBrush m_Color;
	CRect m_beam[20];
	CRect brick_jugement;
	bool m_Alive[20];
public:
	void SetInfo();
	void SetDraw(CDC* memDC);
	void brick_destroy(CBrick* brick, CItem* item);
	void SetLaser(CPlayerbar* player);
};

