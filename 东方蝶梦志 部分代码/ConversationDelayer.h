#pragma once
#include <optional>
namespace Conversation {
	class ConversationDelayer
	{
		std::optional<int> m_clickWatchDog;
	public:

		bool NowClickable() const;	//��ǰ�Ƿ�ɵ��
		void Click();	//���һ��
		void Update();	//����һ֡
	};

}