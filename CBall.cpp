#include "pch.h"
#include "CBall.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"

void CBall::SetBall(int Center_X, int Center_Y)  // 공 기본 세팅
{
	Center_X /= 2;
	Center_Y = Center_Y - (Center_Y / 9);
	m_Ball = CRect(Center_X - 7, Center_Y - 14, Center_X + 7, Center_Y);
	m_Ball_Brush.CreateSolidBrush(RGB(92, 209, 229));
	m_Alive = true;
}

void CBall::GetBall()  // 공 죽었을 때
{
	m_Ball = CRect(-10, -10, -10, -10);
	m_Alive = false;
	x = 0;
	y = 0;
}

BOOL CBall::SetBrick_judgement(CBrick *brick, CPlayerbar *player, CItem *item) // 공 판정
{
	bool a = false;
	if (brick->GetAlive())
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_block_judgement.IntersectRect(m_Ball, brick->GetBrickhitboxInfo(i)))
			{
				brick->GetBrick();
				if (i == 0 || i == 1)
					x *= -1;
				else if (i == 2 || i == 3)
					y *= -1;
				int random = rand() % 100;
				if (random >= 0 && random < 7 && item->GetAlive(random) == false)
				{
					item->SetRectItem(brick, random);
				}
				break;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_block_judgement.IntersectRect(m_Ball, player->GetPlayerBarInfo(i)) && player->GetPlayerBarInfo(i))
		{ // 게임 시작 bool 넣고 SetStart하면 false로 전환되는 시스템 Catch에도 써먹을 예정
			if (player->GetCatchInfo())
			{
				a = true;
				saveX = x;
				saveY = y;
			}
			else
			{
				int a = 0;
				a = x;
				if (i == 0)
				{
					if (x < 0)
						x -= 1;
					else
						x *= -1;
				}
				else if (i == 2)
				{
					if (x < 0)
						x *= -1;
					else
						x += 1;
				}
				else
				{
					if (player->GetPlayerLeft() > 0)
						x += 1;
					else if (player->GetPlayerLeft() < 0)
						x -= 1;
					if (x == 0 && a > 0)
						x = 1;
					else if (x == 0 && a < 0)
						x = -1;
				}
				if (x > 5)
					x = 4;
				else if (x < -5)
					x = -4;
				y *= -1;
				break;
			}
		}
	}
	if (m_Ball.left <= 0 || m_Ball.right >= 900)
	{
		x *= -1;
	}
	else if (m_Ball.top <= 0)
	{
		y *= -1;
	}
	else if (m_Ball.bottom >= 800)
	{
		GetBall();
	}
	return a;
}

void CBall::SetBall_Move()
{
	m_Ball.OffsetRect(x, y);
}

void CBall::SetDraw(CDC* memDC)
{
	if (m_Alive)
	{
		memDC->SelectObject(m_Ball_Brush);
		memDC->Ellipse(m_Ball);
	}
}

BOOL CBall::GetAlive()
{
	return m_Alive;
}

void CBall::SetStart(CPlayerbar *player)
{
	if (saveX == 0 && saveY == 0)
	{
		y = -3;
		x = 1;
	}
	else
	{
		x = saveX;
		y = saveY;
		saveX = 0;
		saveY = 0;
	}
	player->SetCatchItem();
}

void CBall::SetBallMove(int a, int b)
{
	if (m_Ball.right >= 857)
	{
		if (a < 0)
		{
			m_Ball.OffsetRect(a, b);
		}
	}
	else if (m_Ball.left <= 43)
	{
		if (a > 0)
		{
			m_Ball.OffsetRect(a, b);
		}
	}
	else
	{
		m_Ball.OffsetRect(a, b);
	}
}

void CBall::SetItemBall(CBall *ball)
{
	m_Ball = CRect(ball->GetInfo().left, ball->GetInfo().top, ball->GetInfo().right, ball->GetInfo().bottom);
}

CRect CBall::GetInfo()
{
	return m_Ball;
}

void CBall::SetItemBallXSpeed(int speed)
{
	x = speed;
}
void CBall::SetItemBallYSpeed(int speed)
{
	y = speed;
}
int CBall::GetXSpeed()
{
	return x;
}
int CBall::GetYSpeed()
{
	return y;
}