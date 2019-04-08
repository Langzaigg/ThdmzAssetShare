#include "Precompiled.h"
#include "Movie.h"
#include "Game.h"

using namespace Basic::Input;

void Inputer::Movie::PushMsg(const Basic::Input::Message & m)
{
	m_frames[Game::GetGame().GetGameTime()].msg.push_back(m);
}

void Inputer::Movie::PushBeat(int i)
{
	m_frames[Game::GetGame().GetGameTime()].beat = i;
}

const  Basic::Input::Message&  Inputer::Movie::GetEvent(int frame, int num) const
{
	return m_frames.at(frame).msg.at(num);
}

unsigned Inputer::Movie::EventNum(int frame) const
{
	if (m_frames.count(frame))
		return m_frames.at(frame).msg.size();
	else
		return 0;
}

int Inputer::Movie::GetBeat(int frame) const
{
	return m_frames.count(frame) ? m_frames.at(frame).beat : -1;
}

void Inputer::Movie::SaveToStream(std::ostream& out) const
{
	//д���汾��
	//out.write((const char*)&VERSION, sizeof(VERSION));

	//д��֡��
	uint32_t size = m_frames.size();
	out.write((char*)&size, sizeof(size));

	//д��ÿһ֡
	for (auto& p : m_frames) {
		out.write((char*)&p.first, sizeof(p.first));	//д��֡��

		//д��Msg
		size = p.second.msg.size();
		out.write((char*)&size, sizeof(size));

		for (auto& msg : p.second.msg)
			out.write((char*)&msg, sizeof(msg));

		//д��ÿһ֡�Ľ���
		out.write((char*)&p.second.beat, sizeof(p.second.beat));
	}

	if (!m_seed.has_value())
		Crash(L"���ӰƬû�����������!");
	//д������
	out.write((char*)&(*m_seed), sizeof(*m_seed));
}

void Inputer::Movie::LoadFromStream(std::istream & in)
{
	Clear();

	//����汾��
	//unsigned inVer;
	//in.read((char*)&inVer, sizeof(VERSION));

	//if (inVer != VERSION)
		//Crash(L"¼���ȡʧ�ܣ�");

	//����֡��
	uint32_t size;
	uint32_t numFrames;
	in.read((char*)&numFrames, sizeof(numFrames));

	for (uint32_t i = 0; i < numFrames; ++i) {
		//����֡��
		uint32_t frame;
		in.read((char*)&frame, sizeof(i));

		auto& frameObj = m_frames[frame];

		//����Msg
		in.read((char*)&size, sizeof(size));
		for (unsigned j = 0; j < size; ++j) {
			Message m;
			in.read((char*)&m, sizeof(m));
			frameObj.msg.push_back(m);
		}

		//����ÿһ֡�Ľ���
		in.read((char*)&frameObj.beat, sizeof(frameObj.beat));
	}

	//��������
	uint32_t seed;
	in.read((char*)&seed, sizeof(seed));
	m_seed = seed;
}

void Inputer::Movie::Clear()
{
	m_frames.clear();
}


unsigned Inputer::Movie::GetSeed()
{
	if (!m_seed.has_value())
		m_seed.emplace(time(NULL));
	return *m_seed;
}