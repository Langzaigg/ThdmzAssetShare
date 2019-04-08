#pragma once
#include "TitleMenuStackFrame.h"
#include "TitleMainMenu.h"
#include "Menu.h"
#include "VecMatcher.h"
namespace Activities::Title::MenuStack
{
	class TitleStageSelectMenu : public TitleMenuStackFrame
	{
	public:
		using Callback = std::function<void(int stageID)>;	//����ؿ�ID��ͬ��
	private:
		Title::TitleMainMenu* const m_menuManager;

		Basic::Menu::Menu m_menu;

		std::shared_ptr<Basic::Menu::MenuItem> makeMenuItem(int stageID);	//0~5Ϊ��ͨ�ؿ�1~6��6ΪExtra
		std::vector<std::shared_ptr<Basic::Menu::MenuItem>> makeMenu(bool isExtra);

		Callback m_callback;

		Basic::Input::VecMatcher m_mat;
	public:
		TitleStageSelectMenu(Title::TitleMainMenu* m,bool isExtra);
		void OnEvent(const Basic::Input::Message&) override;

		void OnEntryOther() override;

		void OnUpdate(float t) override;
		void OnDrawYSJD() const override;

		inline void SetCallback(Callback&& cb)
		{
			m_callback = std::move(cb);
		}
	};
}
