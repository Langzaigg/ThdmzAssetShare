#pragma once
#include "BaseAfterEffect.h"

namespace AfterEffect {
	class ScreenVibrator :
		public AfterEffect::BaseAfterEffect
	{
	private:
		double m_xVibWidth, m_yVibHeight;
		double m_xSinArg, m_ySinArg;
		bool m_killed = false;
	public:
		ScreenVibrator(int leftTime, double leftX, double leftY, int leftSlowMotion, int keepTime, int rightTime);

		void Draw() const override;	//��ʱ����ʱ���Ѿ���������TEXTURE0
		void Update() override;
		bool Killed() override;
	};
}
