#pragma once
/*
#include "BasicCharBullet.h"
#include "DataActor.h"
#include "Enemy.h"
#include "Sprite2D.h"

namespace Char {
	namespace Reimu {
		class BulletReimu2 final :public BasicCharBullet	//���и��ٵ�
		{
		private:
			Basic::Video::Renderer2D::Sprite2D m_sprite;
			double m_angle = 0;	//�Ƕ�
			//double m_enemyAngle = 0;	//�������ڽǶ�
			int m_nearestEnemy;	//����ĵ���
			//Enemy::Enemy* m_targetEnemy = nullptr;

			double m_startX, m_startY;	//��ʼλ��
			double m_berzierNow = 0;	//����������t

			Basic::DataActor m_dataActor;

			//int m_timer;

			void findNearestEnemy();	//Ѱ������ĵ���
		public:
			void Update() override;	//����
			void Draw() const override;	//����

			void Kill() override;	//ɱ��֮ǰ
			void Create(double x, double y) override;	//����ʱ�����봴������
			void OnColli(Enemy::Enemy &enemy) override;

			inline void SetAngle(double angle) {
				m_angle = angle;
			}
		};
	}
}*/