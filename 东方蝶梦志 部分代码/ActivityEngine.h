#pragma once
#include "NuzPrecompiled.h"
#include "TaskList.h"

namespace Basic {
	namespace ActivityEngine {
		class Activity;

		class ActivityEngine final
		{
		private:

			int m_cnt = 0;

			Basic::TaskList m_taskList;
			std::stack<std::shared_ptr<Activity>> m_now;	//��ǰ��еĻ
			int m_frameMode = 0;
			bool m_run;	//����汣������
			ActivityEngine() = default;
		public:
			void SetFPS(int fps);	//����֡�ʣ�0Ϊ�����ƣ�������ֱͬ��ʱ��������Ϊ0
			void Goto(std::shared_ptr<Activity>);	//��ת�����ƽ����
			void Call(std::shared_ptr<Activity>);	//������ǰ�ͬʱ�����»
			void Return();	//������ǰ���������һ�
			void Run(std::shared_ptr<Activity>);	//������һ���,û�н��붯��
			inline void Exit() {	//�˳������
				m_run = false;
				//exit(0);
			}

			inline auto GetTopActivity() {
				return m_now.top();
			}

			inline auto& GetTaskList() {
				return m_taskList;
			}

			inline int GetFrameTime() { return m_cnt; }

			static ActivityEngine& GetActivityEngine();
		};

	}
}