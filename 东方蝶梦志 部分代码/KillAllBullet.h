#pragma once
#include "StageTask.h"

namespace StageTask {
	class KillAllBullet :
		public StageTask::BaseTask
	{
	public:
		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������
	};
}
