#pragma once
#include "Enemy.h"
#include "Dmsl.h"
#include "BossTask.h"
#include "Sprite2D.h"
#include <queue>
#include "Particle3D.h"
#include "TaskList.h"
#include "BossTimer.h"
#include "BossMahoujin.h"
#include "SpellCardDisplay.h"
#include "BossHPDisplay.h"
#include "BossBgCollector.h"
#include "BossSpellCardCountDisplay.h"
#include <optional>
#include "Stage5DoremiBook.h"


namespace Boss {
	class BossSpellScorer;

	class Boss :
		public Enemy::Enemy
	{
	public:
		struct Skill {
			double hpDisplayLowLimit;
			double hp;
			int timeLimit;
			bool timeSpellCard;
			std::unique_ptr<Dmsl::DmslUnit> dmslUnit;
			std::shared_ptr < Basic::Video::Renderer2D::Sprite2DWStreamLayout > spellCardNameDisplay;
			bool isSpellCard;
			bool useNewHPLine;
			int score;
			int spellHash;
		};

		struct AnimationData {
			std::string textureName;
			int screenFrame_frame, begin, num;
		};

	protected:
		double m_fullHP = 9999;	//��ǰ��HP

		bool m_started = false;	//�Ƿ��Ѿ�������Start()

		bool m_canFlip = true;	//�Ƿ����ת��

		int m_spellCardScore;
		int m_fullTimeLimit;

		bool m_canBeKill = false;	//���Ա�Kill����ɱ��

		std::shared_ptr<Dmsl::DmslVirtualMachine> m_dvm;

		std::queue<std::unique_ptr<Skill>> m_skills;
		std::vector<AnimationData> m_animations;

		std::shared_ptr<Basic::Video::Renderer2D::Sprite2D> m_spellLH;	//������������

		int m_skillTimer = 9999;
		bool m_isSpellCard = false;

		int m_delayTime = 0;

		int m_spellTimer = 0;	//��������ʱ�䣨֡��

		bool m_dontKillHPBecauseLastBomb = false;

		StageTask::StartBoss* m_startBossTask;

		BossTimer* m_bossTimer = nullptr;
		SpellCardDisplay* m_spellCardDisplay = nullptr;
		BossMahoujin* m_bossMahoujin = nullptr;
		BossSpellCardCountDisplay* m_spellCardCountDisplay = nullptr;
		BossSpellScorer* m_spellScorer = nullptr;

		BossHPDisplay* m_bossHpDisplay = nullptr;

		double m_hpDisplayLowerLimit = 100;	//����Ѫ���ٷֱ�
		double m_hpDisplayHighLimit = 0;	//����Ѫ���ٷֱ�

		int m_fullSpellCount = 0;	//SpellCard�ܸ���

		double m_fogR, m_fogG, m_fogB;	//����Ч����RGB

		double m_lastLowerHP = 0;

		std::queue<std::vector<double>> m_hpPoints;

		Boss::BossBgCollector m_bg;

		bool m_isTimeSkill = false;	//�Ƿ�Ϊʱ��

		bool m_needDeleteObjects = true;

		int m_deathType;

		std::queue<std::unique_ptr<Dmsl::DmslUnit>> m_readyToInsert;

		bool m_cardBonus = true;	//�Ƿ�����տ�

		int m_inAnimation, m_outAnimation;	//�����볡����

		int m_effectPowerUp = 0;

		void popSkill();

	public:
		Boss(std::shared_ptr<Dmsl::DmslVirtualMachine> dvm);
		virtual ~Boss();

		void SetStartBossTask(StageTask::StartBoss*);
		void AddSkill(Skill*);
		void AddAnimation(const AnimationData&);
		inline auto& GetSpellCardStandImage() {
			return *m_spellLH;
		}
		inline auto& GetDmslLinkTable() { return Enemy::GetVMContext().table; }

		inline auto& GetBgCollector() { return m_bg; }

		void FirstFrameRun();
		void Update() override;

		void Draw() const override;

		void UseCharAnimation(int n);

		void Start();

		void Kill() override;	//ע�⣺�п��ܻᱻGameObjectɱ��

		virtual void SpellCardOver();

		inline void EffectPowerUp() {
			m_effectPowerUp = 160;

			double x, y;
			GetPos(x, y);
			Basic::Sound::SeManager::Play("ch00", x);
		}

		inline void SetFogColor(double r, double g, double b) {
			m_fogR = r;
			m_fogG = g;
			m_fogB = b;
		}

		inline void SetInOutAnimation(int in, int out) {
			m_inAnimation = in;
			m_outAnimation = out;
		}

		inline void DisableFlip() {
			m_canFlip = false;
			m_enemyImage.SetFlip(false, false);
		}

		void CallPrivateUnit(int unit, const std::shared_ptr<const Dmsl::DmslVarying>& varying) override;

		static Boss* GetBoss();
	};
}