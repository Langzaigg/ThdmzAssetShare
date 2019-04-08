#pragma once
#include "BasicInput.h"
namespace Basic {
	namespace ActivityEngine {

		//���
		//����ͬSnow::Activity
		class Activity {
		public:
			virtual ~Activity() {}
			virtual void OnUpdate(float deltaTime) = 0;	//�߼�����ʱ
			virtual void OnDraw() const = 0;	//��Ҫ����ʱ
			virtual void OnFadeIn(int frame) {}	//ʹ��Goto����ʱ������Ԥ���ܺ�ʱ��֡��
			virtual void OnFadeInUpdate(double finished) {}	//ʹ��Goto��������ڵ��룬���붯����ɰٷֱȡ���
			virtual void OnFadeOut(int frame) {}	//ʹ��Goto�г�ʱ������Ԥ���ܺ�ʱ��֡��
			virtual void OnFadeOutUpdate(double finished) {}	//ʹ��Goto�г������ڵ��������붯����ɰٷֱȡ���
			virtual void OnEntry() {}	//ʹ��Goto����ʱ��OnFadeInǰ��
			virtual void OnLeave() {}	//ʹ��Goto�뿪�ʱ��OnFadeOut�Ҷ���������
			virtual void OnEvent(const Basic::Input::Message&) {}	//�������ʱ��ֻ��ջ���Ļ�����յ���Ϣ��
		};
	}
}