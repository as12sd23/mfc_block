#include "pch.h"
#include "CBall.h"
#include "CBrick.h"
#include "CPlayerbar.h"
#include "CItem.h"

void CBall::SetInfo()
{
	m_Ball_Brush.CreateSolidBrush(RGB(92, 209, 229));
}
void CBall::SetBall(int Center_X, int Center_Y)  // 공 기본 세팅
{
	Center_X /= 2;
	Center_Y = Center_Y - (Center_Y / 9);
	m_Ball = CRect(Center_X - 7, Center_Y - 14, Center_X + 7, Center_Y);
	m_Alive = true;
}

void CBall::GetBall()  // 공 죽었을 때
{
	m_Ball = CRect(-10, -10, -10, -10);
	m_Alive = false;
	x = 0;
	y = 0;
}

int CBall::SetBrick_judgement(CBrick* brick, bool bounce) // 공 판정
{
	int random = 100;
	if (m_Alive)
	{
		if (brick->GetAlive())
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_block_judgement.IntersectRect(m_Ball, brick->GetBrickhitboxInfo(i)))
				{
					brick->GetBrick();
					if (bounce)
					{
						if (i == 0 || i == 1)
							x *= -1;
						else if (i == 2 || i == 3)
							y *= -1;
					}
					random = rand() % 100;
					break;
				}
			}
		}
	}
	return random;
}
BOOL CBall::SetPlayerJudgement(CPlayerbar* player, bool Catch, int Timer)
{
	bool bounce = false;
	if (m_Alive)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_block_judgement.IntersectRect(m_Ball, player->GetPlayerBarInfo(i)) && player->GetPlayerBarInfo(i))
			{ // 게임 시작 bool 넣고 SetStart하면 false로 전환되는 시스템 Catch에도 써먹을 예정

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

				if (Catch && Timer > 200)
				{
					saveX = x;
					saveY = y;
					x = 0;
					y = 0;
					bounce = true;
				}
				break;
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
	}
	return bounce;
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

void CBall::SetStart(bool Catch)
{
	if (Catch == false)
	{
		y = -4;
		x = 2;
	}
	else
	{
		x = saveX;
		y = saveY;
		saveX = 0;
		saveY = 0;
	}
}

void CBall::SetBallMove(int a, int b, bool Catch)
{
	if (Catch == false)
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
	else
	{
		if (m_Ball.right >= 900)
		{
			if (a < 0)
			{
				m_Ball.OffsetRect(a, b);
			}
		}
		else if (m_Ball.left <= 0)
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
}

void CBall::SetSpeedUp()
{
	if (y > 0)
		y++;
	else
		y--;

}
void CBall::SetItemBall(CRect ball)
{
	m_Ball = CRect(ball.left, ball.top, ball.right, ball.bottom);
	m_Alive = true;
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
void CBall::SetSpeedSlow()
{
	if (m_Alive)
	{
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
	}
}

void CBall::SetSplitBall(int Speedx, int Speedy, CRect ball)
{
	if (m_Alive == false)
	{
		m_Ball = CRect(ball.left, ball.top, ball.right, ball.bottom);
		m_Alive = true;
		x = Speedx;
		y = Speedy;
	}
}