#pragma once
#include "Sprite2D.h"
#include "DataActor.h"

namespace UI {
	class DreamSystem
	{
	private:
		Basic::Video::Renderer2D::Sprite2D m_main, m_line, m_pointer;
		Basic::DataActor m_dataActor;
		double m_data;
		double m_alpha;
		bool m_enabled = true;
	public:
		DreamSystem();
		void Reset();
		void Draw() const;
		void Update();

		void SetData(double);	//��Ϊ��������Ϊ����

		void ZeroAlpha();
		void HalfAlpha();	//��ҿ���ʱ����
		void FullAlpha();	//���Զ��ʱ��ʾ

		//void Enable(bool);
	};
}