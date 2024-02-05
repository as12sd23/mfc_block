#include "pch.h"
#include "CLaser.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"
void CLaser::SetInfo()
{
	m_Color.CreateSolidBrush(RGB(255, 18, 18));
	for (int i = 0; i < 20; i++)
	{
		m_Alive[i] = false;
	}
}
void CLaser::SetDraw(CDC* memDC)
{
	for (int i = 0; i < 20; i++)
	{
		if (m_Alive[i])
		{
			m_beam[i].OffsetRect(0, -3);
			memDC->SelectObject(m_Color);
			memDC->Rectangle(m_beam[i]);
		}
	}
}
void CLaser::brick_destroy(CBrick *brick, CItem *item)
{
	for (int i = 0; i < 20; i++)
	{
		if (m_Alive[i])
		{
			if (brick_jugement.IntersectRect(brick->GetBrickInfo(), m_beam[i]))
			{
				m_Alive[i] = false;
				brick->GetBrick();
				int random = rand() % 100;
				if (random >= 0 && random < 7 && item->GetAlive(random) == false)
				{
					item->SetRectItem(brick, random);
				}
				break;
			}
		}
	}
}

void CLaser::SetLaser(CPlayerbar* player)
{
	int Count = 0;
	for (int i = 0; i < 20; i++)
	{
		if (m_Alive[i] == false)
		{
			m_Alive[i] = true;
			Count++;
			if (Count == 1)
				m_beam[i] = CRect(player->GetPlayerInfo().left, player->GetPlayerInfo().top, player->GetPlayerInfo().left + 10, player->GetPlayerInfo().top + 10);
			else if (Count == 2)
				m_beam[i] = CRect(player->GetPlayerInfo().right - 10, player->GetPlayerInfo().top, player->GetPlayerInfo().right, player->GetPlayerInfo().top + 10);
		}
		if (Count >= 2)
			break;
	}
}