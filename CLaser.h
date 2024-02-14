#pragma once
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"

class CLaser
{
private:
	CBrush m_Color;
	CRect m_beam[2];
	CRect brick_jugement;
	bool m_Alive[2];
public:
	void SetInfo();
	void SetDraw(CDC* memDC);
	int brick_destroy(CBrick* brick);
	void SetLaser(CRect player);
	BOOL GetAlive();
};

