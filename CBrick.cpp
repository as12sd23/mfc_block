#include "pch.h"
#include "CBrick.h"


void CBrick::SetInfo()
{
	m_Color.CreateSolidBrush(RGB(255, 217, 236));
}
void CBrick::SetBrick(int x, int y)
{
	m_Rect = CRect(x, y, x + 68, y + 30);
	m_Recthitbox[0] = CRect(x, y + 13, x + 5, y + 17); // left
	m_Recthitbox[1] = CRect(x + 63, y + 13, x + 68, y + 17); // right
	m_Recthitbox[2] = CRect(x, y + 20, x + 68, y + 30); // bottom
	m_Recthitbox[3] = CRect(x, y, x + 68, y + 10); // top
	m_Alive = true;
}
void CBrick::GetBrick()
{
	m_Alive = false;
}
void CBrick::SetDrawBrick(CDC* memDC)
{
	if (m_Alive)
	{
		memDC->SelectObject(m_Color);
		memDC->Rectangle(m_Rect);
	}
}
BOOL CBrick::GetAlive()
{
	return m_Alive;
}
CRect CBrick::GetBrickhitboxInfo(int i)
{
	if (i >= 0 && i < 4)
		return m_Recthitbox[i];
}
CRect CBrick::GetBrickInfo()
{
	return m_Rect;
}