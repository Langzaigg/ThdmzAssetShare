#pragma once
#include "DataActor.h"
#include "TaskList.h"
#include "BaseAfterEffect.h"

namespace AfterEffect {
	class KeepingBarrelBlurWithPlayer :	//������ҵ�BarrelBlur
		public AfterEffect::BaseAfterEffect
	{
	private:
		Basic::TaskList m_taskList;
		Basic::DataActor m_dataActor;
		double m_power;
		bool m_finished = false;

		double m_offsetX = 0, m_offsetY = 0;
	public:
		//����Ч��ʱ���ᣬ����ʱ��������ʱ�����˳�ʱ�������Power�����뻺�����ߣ��˳���������
		KeepingBarrelBlurWithPlayer(int inFrame, int keepFrame, int endFrame, double highestPower, int fadeInSlowMotion = 0, int fadeOutSlowMotion = 0, double offsetX = 0, double offsetY = 0);

		void Draw() const override;
		void Update() override;

		bool Killed() override;
	};
}