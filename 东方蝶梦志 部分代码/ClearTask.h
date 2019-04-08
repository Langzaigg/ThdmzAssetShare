#pragma once
#include "StageTask.h"

namespace StageTask {
	class ClearTask :
		public StageTask::BaseTask
	{
	private:
		unsigned m_baseScore;
		bool m_first = true;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������,һ����ִ��һ�Ρ�
	};
}
