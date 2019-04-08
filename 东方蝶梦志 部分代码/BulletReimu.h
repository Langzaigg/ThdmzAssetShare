#pragma once
#include "BasicCharBullet.h"
#include "Sprite2D.h"
namespace Char {
	namespace Reimu {
		class BulletReimu final :public BasicCharBullet
		{
		private:
			Basic::Video::Renderer2D::Sprite2D m_sprite;
			int m_imageNum = 0;
			double m_imageAlpha = 1.0;
			double m_power = 1.2;

			bool m_marisaMode = false;

			bool m_powerX1dot3 = false;
		public:
			BulletReimu(bool marisaMode = false);

			inline void SetPower(double power) {
				m_power = power;
			}

			void Update() override;	//����
			void Draw() const override;	//����

			void Kill() override;	//ɱ��֮ǰ
			void Create(double x, double y) override;	//����ʱ�����봴������
			void SetImageNum(int num);
			void SetImageAlpha(double alpha);
			void OnColli(Enemy::Enemy &enemy) override;

			void SetAngle(double);
			inline auto& GetSprite() {
				return m_sprite;
			}

			void* operator new(size_t);
			void operator delete(void* ptr);
		};
	}
}