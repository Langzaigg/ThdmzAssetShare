#pragma once
#include "Dmsl.h"
#include "Animation2D.h"
#include "GameObjectWithDmslControl.h"
#include "Collision.h"
#include "SeManager.h"
#include "StageData.h"
#include <memory>
#include "DmslLib.h"
namespace Enemy {
	class Enemy :public GameObjectWithDmslControl
	{
	protected:
		struct RunningDmslUnit {
			bool running;
			std::unique_ptr<Dmsl::DmslUnit> ptr;
		};
		bool* m_stopRunning;
		std::vector<RunningDmslUnit> m_dmslUnit;	//�ű�
		Basic::Video::Renderer2D::Animation2D m_enemyImage;	//ͼ��
		std::shared_ptr<Dmsl::GameObjectLibraryLinkTable> m_dmslLinkTable;
		std::shared_ptr<Dmsl::DmslVirtualMachine> m_dvm;
		uint32_t m_enemyDiedProgramLink;

		int m_minLiveOutScreen;		//����Ļ�����������ʱ��
		int m_invicible;	//�޵�ʱ��

		double m_hp;	//����ֵ
		double m_fullHP;	//��ʱ������ֵ
		int m_radius;	//���˽�ɫ�뾶

		bool m_xFilpEnabled;

		Collision::Circle m_collision;

		//int m_

		struct ParticleEffect {	//��ɱ��ʱ��������Ч
			double r, g, b, speed;
			int num;
		}m_particleWhenKilled;

		bool m_colliEnabled = true;	//�Ƿ�������ײ��

		void callDmsl();

		Enemy* m_hpLink = nullptr;

		bool m_stamina = true;

	protected:
		double m_dreamX;

	public:
		static void LinkEnemyDmslLib(Dmsl::DmslVirtualMachine& dmsl);	//����Dmsl���˿�

		Enemy();
		Enemy(const VMContext & c);

		inline bool GetColliEnabled() {
			return m_colliEnabled;
		}

		inline void SetStaminaEnabled(bool b) {
			m_stamina = b;
		}

		/*inline void SetColliEnabled(bool b) {
			m_colliEnabled = b;
		}*/

		inline double GetHP() {
			return m_hp;
		}

		inline void SetHP(double hp) {
			m_hp = hp;
		}

		virtual void Update() override;
		void Draw() const override;

		virtual void Create(const StageData::EnemyData&, bool createdByScript = false, Enemy* hpLink = nullptr);	//����ʱ
		virtual void Kill() override;	//��ͨ��ɱ��

		inline void StopDmsl() {
			*m_stopRunning = false;
		}

		inline const auto& GetCollision() const {
			return m_collision;
		}

		void DecHP(double hp);

		virtual void CallPrivateUnit(int unit, const std::shared_ptr<const Dmsl::DmslVarying>& varying);

		/*void* operator new(size_t);
		void operator delete(void* ptr);*/
	};

	//Enemy* CreateEnemy(int style);
	Enemy* CreateEnemy(int style, GameObjectWithDmslControl::VMContext c);
}
