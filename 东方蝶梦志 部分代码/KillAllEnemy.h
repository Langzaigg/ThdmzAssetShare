#pragma once
#include "StageTask.h"

namespace StageTask {
	class KillAllEnemy :public BaseTask
	{
	public:
		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������
	};
}