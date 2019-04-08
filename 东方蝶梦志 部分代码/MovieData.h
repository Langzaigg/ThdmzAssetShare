#pragma once
#include <fstream>
#include <cstdint>
#include "StageData.h"
#include "Game.h"
#include "Movie.h"

namespace MovieData
{
	constexpr int32_t MOVIE_VERSION = 0;
	struct Head
	{
		enum Charater : int32_t
		{
			Reimu = 0,
			Marisa = 1
		};

		int32_t version = MOVIE_VERSION;	//¼��汾�ţ����԰泣Ϊ0������ʱΪ1
		Charater charater;	//��ɫ��
		int32_t level;	//�ȼ�����StageLevelǿת������
		bool isExtra = false;	//�Ƿ�ΪExtraģʽ
		wchar_t lastStage[8];	//������һ��Ĺؿ�����
		wchar_t playerName[10];	//��ǩ
		bool mirrored = false;
		uint64_t score;		//�ܷ���
	};

	struct MovieData
	{
		Head head;
		std::map<std::string, std::pair<GameInitData, Inputer::Movie>> stages;
	};

	void SaveMovie(const MovieData& movieData, std::ofstream& out);
	void ReadMovie(MovieData& movieData, std::ifstream& in);
};