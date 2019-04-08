#pragma once
#include "CSVReader.h"
#include <memory>
struct StageData;

namespace StageTask {
	class BaseTask {
	public:
		virtual ~BaseTask() {}
		virtual void Create(Basic::CSVReader&, const StageData&) = 0;	//��C�п�ʼ��ȡ����
		virtual void Proc() = 0;	//ִ������
		virtual bool Finished() = 0;	//�Ƿ����������,һ����ִ��һ�Ρ�
	};

	std::shared_ptr<BaseTask> CreateTaskObject(const std::string& taskName);
}
