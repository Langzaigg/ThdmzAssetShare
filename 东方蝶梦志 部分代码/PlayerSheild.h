#pragma once

#include "Sprite2D.h"

class PlayerSheild final
{
private:
	double m_px, m_py;

	bool m_isLeft;
	int m_time;
	const int m_fullTime;

	bool m_giveLife = true;	//��һ���л���Ƭ

	void halfKillBullet();	//С��Χ����
public:
	PlayerSheild(bool isLeft);
	bool OnUpdate(double x, double y);

	void OnDraw() const;

	inline bool IsLeft() const
	{
		return m_isLeft;
	}

	inline double GetPercent()
	{
		return m_time / double(m_fullTime);
	}

	void Bomb();
	void KillPlayer();

	inline bool Avliable() const
	{
		return m_time > 10;
	}
	bool IsItemPowerX2() const;		//�Ƿ�P����������2
	bool IsShootPowerX1dot3() const;	//�Ƿ������������1.3
};