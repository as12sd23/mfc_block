#include "pch.h"
#include "CLaser.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"
void CLaser::SetInfo()
{
	m_Color.CreateSolidBrush(RGB(255, 18, 18));
	for (int i = 0; i < 2; i++)
	{
		m_Alive[i] = false;
	}
}
void CLaser::SetDraw(CDC* memDC)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_Alive[i])
		{
			m_beam[i].OffsetRect(0, -3);
			memDC->SelectObject(m_Color);
			memDC->Rectangle(m_beam[i]);
			if (m_beam[i].bottom <= 0)
				m_Alive[i] = false;
		}
	}
}
int CLaser::brick_destroy(CBrick *brick)
{
	int random = 100;
	for (int i = 0; i < 2; i++)
	{
		if (m_Alive[i])
		{
			if (brick->GetAlive())
			{
				if (brick_jugement.IntersectRect(brick->GetBrickInfo(), m_beam[i]))
				{
					m_Alive[i] = false;
					brick->GetBrick();
					random = rand() % 100;
					break;
				}
			}
		}
	}
	return random;
}

void CLaser::SetLaser(CRect player)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_Alive[i] == false)
		{
			m_Alive[i] = true;
			if(i == 0)
				m_beam[0] = CRect(player.left, player.top, player.left + 10, player.top + 10);
			if(i == 1)
				m_beam[1] = CRect(player.right - 10, player.top, player.right, player.top + 10);
		}
	}
}

BOOL CLaser::GetAlive()
{
	bool laser = false;
	for (int i = 0; i < 2; i++)
	{
		if(m_Alive[i])
			laser = true;
	}
	return laser;
}