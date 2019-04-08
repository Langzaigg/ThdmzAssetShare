#pragma once
#include "GameObject.h"
#include "DataActor.h"
#include "TaskList.h"
#include <functional>
namespace Utils {
	/* ������Ч */
	class FlashObject :
		public GameObject
	{
	private:
		Basic::DataActor m_dataActor;
		Basic::TaskList m_taskList;

		double m_r = 1, m_g = 1, m_b = 1, m_alpha = 0;

		std::function<void()> m_call = []() {};
	public:
		//�����ڴ˴�����ʱ����
		FlashObject(int leftTime, int leftSlowMotion, int rightTime, int rightSlowMotion, int keep, double highestAlpha = 1);

		//������ɫ
		inline void SetColor(double r, double g, double b) {
			m_r = r;
			m_g = g;
			m_b = b;
		}

		//�����м�ʱҪ���������
		inline void SetCall(std::function<void()> c) {
			m_call = c;
		}

		//����DrawOnTop
		void SetDrawOnTop(bool b) {
			m_drawOnTop = b;
		}

		void Draw() const override;
		void Update() override;
		void Kill() override;
	};
}