#pragma once
class CPlayerbar
{
private:
	CRect m_Playerbar;
	CRect m_PlayerHitbox[3];
	CBrush m_PlayerColor;
	int m_PlayerLeft;
	int m_PlayerRight;
public:
	void SetInfo();
	void SetPlayerBar(int Center_X, int Center_Y);
	void SetPlayerBar_Move(int x);
	void SetPlayerBar_Draw(CDC *memDC);
	void SetPlayerBar_Item();
	CRect GetPlayerBarInfo(int i);
	void SetPlayerLeft(bool Catch);
	int GetPlayerLeft();
	CRect GetPlayerInfo();
	void GetPlayerbar_Item();
};