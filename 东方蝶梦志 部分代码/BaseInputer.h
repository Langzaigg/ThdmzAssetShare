#pragma once
#include "BasicInput.h"
#include <queue>
namespace Inputer {
	/* ���������� */
	class BaseInputer
	{
	public:
		virtual ~BaseInputer() {};
		virtual bool PopMessage(Basic::Input::Message&) = 0;
		inline double Rand1() { 	//0~1�����
			return double(rand()) / RAND_MAX;
		};
		inline double Rand2() {	//-1~1�����
			return -1 + 2 * double(rand()) / RAND_MAX;
		}
		virtual int GetFrameBeat() = 0;	//��ȡ��ǰ�Ľ���
		virtual void PushMessage(const Basic::Input::Message&) = 0;
		virtual unsigned GetRandSeed() = 0;
	};

	/* ��ͨ������ */
	class NormalInputer final :public BaseInputer {
	private:
		std::queue<Basic::Input::Message> m_msgs;
	public:
		bool PopMessage(Basic::Input::Message&) override;
		int GetFrameBeat() override;
		void PushMessage(const Basic::Input::Message&) override;
		unsigned GetRandSeed() override;
	};
}