#pragma once
#include "BasicInput.h"
#include <map>

#include <ostream>
#include <istream>
#include <string>
#include <vector>
namespace Inputer {
	class Movie
	{
	private:
		struct Frame {
			std::vector<Basic::Input::Message> msg;
			uint8_t beat;
		};
		std::map<uint32_t, Frame> m_frames;

		std::optional<uint32_t> m_seed;
	public:
		//¼��ʱ
		void PushMsg(const Basic::Input::Message&);
		void PushBeat(int);

		//����ʱ
		const Basic::Input::Message& GetEvent(int frame, int num) const;
		unsigned EventNum(int frame) const;
		int GetBeat(int frame) const;

		//�洢
		void SaveToStream(std::ostream& out) const;
		void LoadFromStream(std::istream& in);

		void Clear();

		unsigned GetSeed();
	};
}
