#pragma once
#include <memory>
#include "GLTexture.h"
#include "GameObjectWithDmslControl.h"
#include "Enemy.h"

namespace Char {
	/* �������ҷ��ӵ� */
	class BasicCharBullet :public GameObjectWithDmslControl {
	protected:
		double m_colliRadius = 0;	// ��ײ�뾶
		bool m_checkColli = true;	// �Ƿ�����ײ
	public:

		virtual ~BasicCharBullet() {}

		void Update() override = 0;	//����
		void Draw() const override = 0;	//����

		void Kill() override = 0;	//ɱ��֮ǰ���ڴ˺������һ�δ��ʱ�䡣
		virtual void Create(double x, double y) = 0;	//����ʱ�����봴������ͻ���

		// ������ײʱ���õĺ���
		virtual void OnColli(Enemy::Enemy &enemy) = 0;

		void SetRadius(double radius)
		{
			m_colliRadius = radius;
		}

		void SetCheckCollision(bool check)
		{
			m_checkColli = check;
		}

		// ��ȡ��ײ�뾶
		double GetRadius()
		{
			return m_colliRadius;
		}

		// �Ƿ�����ײ
		bool GetCheckCollision()
		{
			return m_checkColli;
		}
		//virtual Collision& GetCollision() = 0;	//��ȡ��ײ��
	};
}