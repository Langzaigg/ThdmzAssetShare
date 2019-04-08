#pragma once
#include <future>
#include <any>
#include "TaskList.h"

namespace Basic::Init
{
	void SimpleInit();
	void InitMustInMainThread();
	void InitOpenGL();

	//����ֵΪ����ͣ��֡��
	int CacheTexture(Basic::TaskList& cacheTaskList,std::any& cache);
}