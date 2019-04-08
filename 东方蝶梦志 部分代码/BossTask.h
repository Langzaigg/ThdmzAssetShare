#pragma once
#include "Dmsl.h"
#include "StageTask.h"
#include "GameObjectWithDmslControl.h"

namespace StageTask {
	class CreateBoss :
		public StageTask::BaseTask
	{
	private:
		static CreateBoss* m_lastBossTask;

		bool m_finishd = false;
		GameObjectWithDmslControl* m_bossObj;

		const bool m_withWBEffect;

	public:
		CreateBoss(bool withWBEffect = false);

		inline static CreateBoss* GetLastBossTask() {
			return m_lastBossTask;
		}

		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		inline void BossDied() {	//��������
			m_finishd = true;
		}
		bool Finished() override;	//�Ƿ����������,һ����ִ��һ�Ρ�

		inline auto GetBossObj() {
			return m_bossObj;
		}

		~CreateBoss();
	};

	class StartBoss :
		public StageTask::BaseTask
	{
	private:
		GameObjectWithDmslControl* m_bossObj;

		bool m_finished = false;
		bool m_first = true;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;
		void Proc() override;
		bool Finished() override;

		void Stop();
	};

	class BossPowerEffect :public StageTask::BaseTask {
	private:
		double m_x, m_y;
		bool m_finished = false;
		int m_frames = 0;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;
		void Proc() override;
		bool Finished() override;
	};

	class BossAttachStage5DoremiBook : public StageTask::BaseTask {
	private:
		bool m_finished = false;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;
		void Proc() override;
		bool Finished() override;
	};
}