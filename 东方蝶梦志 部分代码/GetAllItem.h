#pragma once
#include "StageTask.h"
namespace StageTask {
	class GetAllItem :
		public StageTask::BaseTask
	{
	private:
		bool m_finished = false;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������
	};
}