#pragma once
#include "BasicInput.h"

namespace Activities::Title
{
	class TitleMenuStackFrame
	{
	public:
		virtual ~TitleMenuStackFrame() {}
		virtual void OnEntryToThis() {}				//����ʱ��ʾ
		virtual void OnEntryOther() {}				//���������Ӳ˵�ʱ����
		virtual void OnBackToThisShow() {}			//���Ӳ˵����ص����˵�ʱ
		virtual void OnWannaBackToThisShow() {}		//�������ص����˵�������δ����ʱ

		virtual void OnDraw() const {}				//��ͨ��Ⱦʱ
		virtual void OnDrawYSJD() const {}			//��ɫ������Ⱦʱ
		virtual void OnDrawPost() const {}			//������Ⱦʱ

		virtual void OnUpdate(float deltaTime) {}	//ÿ֡

		virtual void OnEvent(const Basic::Input::Message&) {}	//�¼�
	};
}
