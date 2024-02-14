#pragma once
class CBrick
{
private:
	CRect m_Rect;
	CRect m_Recthitbox[8];
	CPoint m_Point;
	CBrush m_Color;
	bool m_Alive = false;
public:
	void SetInfo();
	void SetBrick(int x, int y);
	void GetBrick();
	void SetDrawBrick(CDC* memDC);
	BOOL GetAlive();
	CRect GetBrickhitboxInfo(int i);
	CRect GetBrickInfo();
};

