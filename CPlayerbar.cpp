#include "pch.h"
#include "CPlayerbar.h"

void CPlayerbar::SetPlayerBar(int Center_X, int Center_Y)
{
	Center_X /= 2;
	Center_Y = Center_Y - (Center_Y / 9);
	m_Playerbar = CRect(Center_X - 50, Center_Y, Center_X + 50, Center_Y + 25);
	m_PlayerHitbox[0] = CRect(Center_X - 50, Center_Y, Center_X - 30, Center_Y + 25);
	m_PlayerHitbox[1] = CRect(Center_X - 17, Center_Y, Center_X + 17, Center_Y + 25);
	m_PlayerHitbox[2] = CRect(Center_X + 30, Center_Y, Center_X + 50, Center_Y + 25);
	m_PlayerColor.CreateSolidBrush(RGB(140, 140, 140));
}

void CPlayerbar::SetPlayerBar_Move(int x)
{
	if (m_Playerbar.right >= 900)
	{
		if (x < 0)
		{
			m_Playerbar.OffsetRect(x, 0);
			for (int i = 0; i < 3; i++)
			{
				m_PlayerHitbox[i].OffsetRect(x, 0);
			}
		}
	}
	else if (m_Playerbar.left <= 0)
	{
		if (x > 0)
		{
			m_Playerbar.OffsetRect(x, 0);
			for (int i = 0; i < 3; i++)
			{
				m_PlayerHitbox[i].OffsetRect(x, 0);
			}
		}
	}
	else
	{
		m_Playerbar.OffsetRect(x, 0);
		for (int i = 0; i < 3; i++)
		{
			m_PlayerHitbox[i].OffsetRect(x, 0);
		}
	}
}

void CPlayerbar::SetPlayerBar_Draw(CDC *memDC)
{
	memDC->SelectObject(m_PlayerColor);
	memDC->Rectangle(m_Playerbar);
}

CRect CPlayerbar::GetPlayerBarInfo(int i)
{
	if (i >= 0 && i < 3)
		return m_PlayerHitbox[i];
}

void CPlayerbar::SetPlayerLeft()
{
	if (m_Item)
	{
		m_PlayerLeft = m_Playerbar.left + 25;
		m_PlayerRight = m_Playerbar.right - 25;
	}
	else
	{
		m_PlayerLeft = m_Playerbar.left;
		m_PlayerRight = m_Playerbar.right;
	}
}

int CPlayerbar::GetPlayerLeft()
{
	return m_Playerbar.left - m_PlayerLeft;
}

CRect CPlayerbar::GetPlayerInfo()
{
	return m_Playerbar;
}

void CPlayerbar::SetPlayerBar_Item()
{
	m_PlayerLeft = m_Playerbar.left;
	m_PlayerRight = m_Playerbar.right;
	m_Playerbar = CRect(m_Playerbar.left - 25, m_Playerbar.top, m_Playerbar.right + 25, m_Playerbar.bottom);
	m_PlayerHitbox[0] = CRect(m_Playerbar.left, m_Playerbar.top,m_Playerbar.left + 20, m_Playerbar.bottom);
	m_PlayerHitbox[1] = CRect(m_Playerbar.left + 7, m_Playerbar.top, m_Playerbar.right - 33, m_Playerbar.bottom);
	m_PlayerHitbox[2] = CRect(m_Playerbar.right - 20, m_Playerbar.top, m_Playerbar.right, m_Playerbar.bottom);
	m_Item = true;
}

void CPlayerbar::GetPlayerbar_Item()
{
	m_Item = false;
	m_Playerbar = CRect(m_Playerbar.left + 25, m_Playerbar.top, m_Playerbar.right - 25, m_Playerbar.bottom);
	m_PlayerHitbox[0] = CRect(m_Playerbar.left, m_Playerbar.top, m_Playerbar.left + 20, m_Playerbar.bottom);
	m_PlayerHitbox[1] = CRect(m_Playerbar.left + 7, m_Playerbar.top, m_Playerbar.right - 33, m_Playerbar.bottom);
	m_PlayerHitbox[2] = CRect(m_Playerbar.right - 20, m_Playerbar.top, m_Playerbar.right, m_Playerbar.bottom);
}

void CPlayerbar::SetCatchItem()
{
	if (m_catch)
		m_catch = true;
	else
		m_catch = false;
}

BOOL CPlayerbar::GetCatchInfo()
{
	return m_catch;
}