#pragma once
#include "GameObjectWithDmslControl.h"
#include "Particle3D.h"
#include "Collision.h"

namespace Char {
	namespace Reimu {
		class ReimuBomb :
			public GameObjectWithDmslControl
		{
		private:
			Basic::Video::Renderer3D::Particle3D m_particle3D;

			Collision::Circle m_coll;

			int m_forceKill = 400;
			int m_timeOffset;

			int m_nearestEnemy = -1;

			static int m_searchNewEnemy;
			int m_nowSearch;

			enum {
				STATE0,	//ģʽ0���ոճ���ʱ��ת���������Ի���ת
				STATE1	//ģʽ1��ֻ�Ǹ����Ի���ת
			}m_state;

			static int m_num;

			double m_angleFromPlayer, m_radFromPlayer;	//state0ʱ��ת�Ƕȣ��뾶

			static double m_angleChanging;

			void updateState0();	//�ոճ���ʱ,תȦʱ
			void updateState1();	//�����Ի���ת

		public:
			ReimuBomb(double startAngle);
			~ReimuBomb();
			static inline bool Bombing() {
				return m_num != 0;
			}
			void Update() override;
			void Draw() const override;
			void Kill() override;

			static void SetPowerData(double single);
		};
	}
}
