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

	for (int i = 0; i < 7; i++)
	{
		m_Alive[i] = false;
	}
}
void CItem::SetRectItem(CBrick *brick, int i)
{
	m_Rect[i] = CRect(brick->GetBrickInfo().left + 10, brick->GetBrickInfo().top + 5, brick->GetBrickInfo().left + 58, brick->GetBrickInfo().top + 25);
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

void CItem::GetItemEffect(CPlayerbar *player, CBall *ball[], CLife *life)
{
	for (int i = 0; i < 7; i++)
	{
		if (m_Alive[i])
		{
			if (m_judgement.IntersectRect(m_Rect[i], player->GetPlayerInfo()))
			{
				GetRectItem(i);
				if (i == 0) // 목숨 추가
				{
					for (int j = 0; j < 10; j++)
					{
						if (life->GetAlive(j) == false)
						{
							life->SetAlive(j);
							break;
						}
					}
					m_Alive[i] = false;
				}
				else if (i == 1) // 레이저 발사
				{

				}
				else if (i == 2) // playerbar 길이 증가
				{
					player->SetPlayerBar_Item();
				}
				else if (i == 3) // playerbar에 공이 붙음
				{

				}
				else if (i == 4) // 공 속도 저하
				{
					int x = 0, y = 0;
					for (int i = 0; i < 3; i++)
					{
						if (ball[i]->GetAlive())
						{
							x = ball[i]->GetXSpeed();
							y = ball[i]->GetYSpeed();
							if (x > 0 && x / 2 == 0)
								x = 1;
							else if (x < 0 && x / 2 == 0)
								x = -1;
							else
								x /= 2;

							if (y > 0 && y / 2 == 0)
								y = 1;
							else if (y < 0 && y / 2 == 0)
								y = -1;
							else
								y /= 2;

							ball[i]->SetItemBallXSpeed(x);
							ball[i]->SetItemBallYSpeed(y);
						}
					}
					m_Alive[i] = false;
				}
				else if (i == 5) // stage 스킵
				{

				}
				else if (i == 6) // 공 3개 
				{
					int a = 4;
					int x = 0;
					for (int i = 0; i < 3; i++)
					{
						if (ball[i]->GetAlive())
						{
							a = i;
							x = ball[a]->GetXSpeed();
							if (x > 2)
								x = 2;
							else if (x < -2)
								x = -2;
							for (int j = 0; j < 3; j++)
							{
								if (a != j)
								{
									ball[j]->SetItemBall(ball[a]);
									if (x < 0)
										ball[j]->SetItemBallXSpeed(x--);
									else
										ball[j]->SetItemBallXSpeed(x++);
								}
							}
						}
					}
				}
			}
		}
	}
}