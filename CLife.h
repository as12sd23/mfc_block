#pragma once
class CLife
{
private:
	CRect m_Life[10];
	bool m_Alive[10];
	CBrush m_Color;
public:
	BOOL GetAlive(int i);
	void SetLife(int X, int Y);
	void SetDraw(CDC* memDC);
	void SetAlive();
	BOOL SetDelete();
	void SetInfo();
};

