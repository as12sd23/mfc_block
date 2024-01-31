#include "pch.h"
#include "CLife.h"

void CLife::SetLife(int X, int Y)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Alive[i])
		{
			m_Life[i] = CRect(X, Y, X + 50, Y + 12); // X + 50 Y 12
		}
	}
}

BOOL CLife::GetAlive(int i)
{
	return m_Alive[i];
}

void CLife::SetAlive(int i)
{
	m_Alive[i] = true;
}

void CLife::SetDraw(CDC* memDC)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Alive[i])
		{
			memDC->SelectObject(m_Color);
			memDC->Rectangle(m_Life[i]);
		}
	}
}

void CLife::SetInfo()
{
	m_Color.CreateSolidBrush(RGB(140, 140, 140));
	m_Alive[0] = true;
	for (int i = 1; i < 10; i++)
	{
		m_Alive[i] = false;
	}
}

BOOL CLife::SetDelete()
{
	bool a = false;
	for (int i = 9; i >= 0; i--)
	{
		if (m_Alive[i])
		{
			m_Alive[i] = false;
			a = true;
			break;
		}
	}
	return a;
}