#pragma once
#include "StageTask.h"
#include "GameObject.h"
#include "Dmsl.h"
#include <vector>
#include "Sprite2D.h"

namespace StageTask {
	class StageTitle :
		public StageTask::BaseTask
	{
	public:
		class StageTitleObj :public GameObject {
		private:
			Dmsl::DmslUnit m_dmslUnit;
			Basic::Video::Renderer2D::Sprite2D m_sp;
		public:
			static void Init();

			StageTitleObj(int dmslUnit, int texUnit);
			void Update() override;
			void Draw() const override;
			void Kill() override;
		};
	private:
		bool m_finished = false;
		std::unique_ptr<StageTitleObj> m_obj;
	public:
		void Create(Basic::CSVReader&, const StageData&) override;	//��C�п�ʼ��ȡ����
		void Proc() override;	//ִ������
		bool Finished() override;	//�Ƿ����������,һ����ִ��һ�Ρ�
	};
}