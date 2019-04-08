#pragma once
#include <string>
#include <map>
#include <queue>
namespace ConversationScript {
	const double Left = 0.0f;
	const double Right = 1.0f;

	class Script {
	public:
		struct Event {
			double arg;
			enum class Cmd {
				Show,
				Hide,
				Act,
				Una,
				SetLNum,
				SetRNum,
				ColorR,
				ColorG,
				ColorB,
				Program,
				Print,
				WaitClick,
				WaitTime,
				Br,
				Cls,
				Showname,
				BossBGM,
				StopBGM
			}cmd;
		};
	private:
		std::string m_rightLHName;
		std::vector<std::wstring> m_texts;
		std::vector<Event> m_events;
	public:

		void LoadScript(const std::string& name);	//���ؽű�

		inline const std::string& GetRightLHName()
		{
			return m_rightLHName;
		}	//��ȡ�������ļ���

		inline const std::wstring& GetText(int textNum) {	//�������ֱ�Ż�ȡ����
			return m_texts[textNum];
		}


		void GetCommand(std::queue<Event>&);	//��ȡָ�����
	};
}
