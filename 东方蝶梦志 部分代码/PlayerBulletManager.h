#pragma once
#include "BasicCharBullet.h"
#include <vector>

class PlayerBulletManager final
{
private:
	std::vector<std::unique_ptr<Char::BasicCharBullet>> m_bullets;

	// ����ӵ�����˵���ײ
	void CheckCollision();
public:
	void Draw() const;
	void Update();

	void KillAll();	//ɱ���Ѵ��ڵ��ӵ�
	void ForceKillAll();	//ǿ��ɱ�������Ѵ��ڵ��ӵ�
	void Shoot(Char::BasicCharBullet*, double x, double y);	//�����ӵ������ӵ�ί���ڴ˺������ֶ��ͷš�
};
