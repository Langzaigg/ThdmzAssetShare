#pragma once
#include "StageTask.h"
namespace StageTask {
	class EnableEnemyCSV :
		public StageTask::BaseTask
	{
	private:
		bool m_finished = false;
		bool m_enable;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������,һ����ִ��һ�Ρ�
	};
}