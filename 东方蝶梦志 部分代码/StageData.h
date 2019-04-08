#pragma once
#include "BGMPlayer.h"
#include "Dmsl.h"
#include <string>
#include <array>
#include <memory>
#include "StageTask.h"
#include "DmslLib.h"
#include "BaseBackground.h"
enum class StageLevel {
	E = 0, N = 1, H = 2, L = 3
};

struct StageData {	//�ؿ�����
	std::string stageName;	//�ؿ�����

	//std::shared_ptr<Basic::Sound::Bgm> stageBgm, bossBgm;	//���к�Boss��BGM
	int stageBgm, bossBgm;

	int bulletLayerNum;
	std::vector<int> bulletNoKillLayerWhenPlayerDied;

	std::shared_ptr<Dmsl::DmslVirtualMachine> enemyScript;	//�����ж��ű�
	uint32_t enemyDiedProgramHandle;	//��������ʱִ�еĳ���

	std::shared_ptr<Dmsl::GameObjectLibraryLinkTable> enemyScriptLinkTable;	//�ж��ű��������ӱ�

	struct EnemyData {
		int birth_time;	//���˳���ʱ��
		double hp;	//HP
		int style;	//ʹ�õĵ��˷��
		int dmslUnit;	//ʹ�õı��

		double x, y;	//��ʼλ��
		int minScreenLife;	//��С��Ļ������ʱ��

		std::shared_ptr<const Dmsl::DmslVarying> varying;
	};

	StageLevel level;

	std::unique_ptr<Background::BaseBackground> background;

	double dreamX;

	struct StageTaskData {
		int frames;
		std::shared_ptr<StageTask::BaseTask> task;
	};
	std::vector<StageTaskData> stageTasks;
};

std::shared_ptr<StageData> LoadStage(const std::string& stageName, StageLevel);	//���عؿ�
void ReloadStageFast(const std::shared_ptr<StageData>& p);	//���ٵ����¼����Ѿ����صĹؿ�