#include "pch.h"
#include "CItem.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CBall.h"
#include "CLife.h"

void CItem::SetItem()
{
	m_Color[0].CreateSolidBrush(RGB(95, 0, 255));		// 목숨추가 아이템
	m_Color[1].CreateSolidBrush(RGB(255, 54, 54));		// 레이저 아이템
	m_Color[2].CreateSolidBrush(RGB(19, 19, 255));		// plyaerbar 길이 증가 아이템
	m_Color[3].CreateSolidBrush(RGB(47, 237, 40));		// ball이 playerbar에 달라붙는 아이템
	m_Color[4].CreateSolidBrush(RGB(255, 187, 0));		// ball 속도가 느려지는 아이템
	m_Color[5].CreateSolidBrush(RGB(255, 18, 239));		// 스테이지 넘기는 아이템
	m_Color[6].CreateSolidBrush(RGB(0, 216, 255));		// ball이 3개로 나뉘는 아이템

	m_Ball = false;
	m_Catch = false;
	m_Laser = false;
	m_Long = false;
	for (int i = 0; i < 7; i++)
	{
		m_Alive[i] = false;
	}
}
void CItem::SetRectItem(CRect brick, int i)
{
	m_Rect[i] = CRect(brick.left + 10, brick.top + 5, brick.left + 58, brick.top + 25);
	m_Alive[i] = true;
}
void CItem::GetRectItem(int i)
{
	m_Rect[i] = CRect(-5, -5, -5, -5);
	m_Alive[i] = false;
}
BOOL CItem::GetAlive(int number)
{
	return m_Alive[number];
}

void CItem::SetItemDraw(CDC* memDC)
{
	for (int i = 0; i < 7; i++)
	{
		if (m_Alive[i])
		{
			m_Rect[i].OffsetRect(0, 2);
			memDC->SelectObject(m_Color[i]);
			memDC->Rectangle(m_Rect[i]);
		}
	}
}
BOOL CItem::GetLaser()
{
	return m_Laser;
}
BOOL CItem::GetCatch()
{
	return m_Catch;
}
BOOL CItem::GetLong()
{
	return m_Long;
}
BOOL CItem::GetBall()
{
	return m_Ball;
}
void CItem::SetBallDestroy(CPlayerbar *player)
{
	m_Catch = false;
	m_Long = false;
	m_Laser = false;
}
int CItem::GetItemEffect(CPlayerbar* player, CLife* life)
{
	int item = 100;
	for (int i = 0; i < 7; i++)
	{
		if (m_Alive[i])
		{
			if (m_judgement.IntersectRect(m_Rect[i], player->GetPlayerInfo()))
			{
				GetRectItem(i);
				if (i == 0) // 목숨 추가
				{
					life->SetAlive();
				}
				else if (i == 1) // 레이저 발사
				{
					if (m_Ball == false)
					{
						m_Catch = false;
						if(m_Long)
							player->GetPlayerbar_Item();
						m_Long = false;

						m_Laser = true;
					}
				}
				else if (i == 2) // playerbar 길이 증가
				{
					if (m_Ball == false)
					{
						m_Catch = false;
						m_Laser = false;
						m_Long = true;
						player->SetPlayerBar_Item();
					}
				}
				else if (i == 3) // playerbar에 공이 붙음
				{
					if (m_Ball == false)
					{
						m_Laser = false;
						if (m_Long)
							player->GetPlayerbar_Item();
						m_Long = false;
						m_Catch = true;
						item = 3;
					}
				}
				else if (i == 4) // 공 속도 저하
				{
					item = 4;
				}
				else if (i == 6) // 공 3개 
				{
					m_Laser = false;
					m_Catch = false;
					if (m_Long)
						player->GetPlayerbar_Item();
					m_Long = false;
					m_Ball = true;
					item = 6;
				}
				m_Alive[i] = false;
				if (i == 5) // stage 스킵
					item = 1;
			}

			if (m_Rect[i].bottom >= 900)
			{
				GetRectItem(i);
				m_Alive[i] = false;
			}
		}
	}
	return item;
}