#pragma once
#include "BasicOption.h"
#include "Sprite2D.h"
#include "DataActor.h"
#include <array>
namespace Char {
	namespace Reimu {
		class ReimuOption :
			public Char::BasicOption
		{
		private:
			std::array<Basic::Video::Renderer2D::Sprite2D,4> m_sp;
			double m_pos[4][2];

			double m_angle = 0;
			double m_angleSpeed = 1.5;

			int m_nowPower = 1;

			Basic::DataActor m_dataActor;

			bool m_slowMode = false;

			double m_px, m_py;	//���λ��
			uint32_t m_timer = 0;	//��0~999��ѭ��

		public:
			ReimuOption();

			void OnUpdate(double x, double y) override;	//����
			void OnDraw() const override;	//Ҫ�����ʱ

			void OnSlowStart() override;	//��ʼSlowģʽʱ
			void OnSlowStopped() override;	//Slowģʽֹͣʱ

			void ShootBegin(bool flip) override;	//��ʼ�����ӵ�ʱ
			void ShootUpdate(bool flip) override;	//�����ӵ�ʱ
			void ShootEnd(bool flip) override;	//ֹͣ�����ӵ�ʱ

			void SetPower(int) override;	//����Power

			static void SetPowerData(double fast, double slow);
			static void SetNonSlowPowerAngle(double angle);
		};
	}
}