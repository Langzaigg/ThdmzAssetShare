#include "Precompiled.h"
#include "StageData.h"
#include "SnowRVReader.h"
#include "Globals.h"
#include <sstream>
#include "DmslLib.h"
#include "CSVReader.h"
#include "GameObjectManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "DmslLoader.h"
#include "Game.h"
#include "DMSLUtils.h"
using namespace std;

std::shared_ptr<StageData> LoadStage(const std::string & stageName, StageLevel level){
	auto p = std::make_shared<StageData>();
	p->stageName = stageName;
	p->level = level;
	Basic::SnowRVReader r("StageData/" + stageName + "/Main.rv");

	//����BGM
	//p->stageBgm.reset(new Basic::Sound::Bgm(r.GetString("STAGE_BGM")));
	//p->bossBgm.reset(new Basic::Sound::Bgm(r.GetString("BOSS_BGM")));
	p->stageBgm = r.GetInt("STAGE_BGM");
	p->bossBgm = r.GetInt("BOSS_BGM");


	ReloadStageFast(p);
	return p;
}

void ReloadStageFast(const std::shared_ptr<StageData>& p)
{
	if(p) p->stageTasks.clear();

	Basic::SnowRVReader r("StageData/" + p->stageName + "/Main.rv");

	//���عؿ���������
	Basic::CSVReader csv;

	std::string stageDmslName = r.GetString("STAGE_PROGRAM");
	csv.Load("StageData/" + p->stageName + "/" + r.GetString("TASKLIST"));

	//���عؿ�����
	while (!csv.IsLastLine()) {
		StageData::StageTaskData data;
		data.frames = csv.PopInt();
		data.task = StageTask::CreateTaskObject(csv.PopString());
		data.task->Create(csv,*p);
		p->stageTasks.push_back(data);
		csv.NextLine();
	}


	//���ؿ��Ƶ��˵�Dmsl
	Dmsl::DmslLoader loader;
	loader.Include("Se");
	loader.Include("Math");
	loader.Include("GameObject");
	loader.Include("EnemyLib");

	//��˳�����ÿ���ļ�
	std::vector<std::string> dmslPaths;
	Dmsl::Utils::Split(stageDmslName, dmslPaths,',');
	for (auto& dp : dmslPaths)
		loader.IncludeMain("StageData/" + p->stageName + "/" + dp);

	p->enemyScript = loader.CompileShared();																																																		
	Dmsl::LoadMathLibrary(*p->enemyScript);	//������ѧ��
	Enemy::Enemy::LinkEnemyDmslLib(*p->enemyScript);	//���ӵ��˿�
	Dmsl::LoadSePlayer(*p->enemyScript);	//������Ч��
	p->enemyScriptLinkTable = std::make_shared<Dmsl::GameObjectLibraryLinkTable>();
	Dmsl::LoadGameObjectLibrary(*p->enemyScript, *(p->enemyScriptLinkTable));
	p->enemyDiedProgramHandle = p->enemyScript->GetModuleHandle("died");
	p->enemyScript->Ready();
	p->enemyScript->SetDMOVFSSelect((int)p->level);

	p->dreamX = 1.2F * r.GetDouble("DREAM_X");

	//�����ӵ�ͼ��
	p->bulletLayerNum = r.GetInt("BULLETS_LAYER");
	{
		std::string src = r.GetString("NOKILL_BULLET_LAYERS_WHEN_PLAYER_DIED");
		if (src != "-1") {
			std::vector<std::string> v;
			Dmsl::Utils::Split(src, v, ',');
			for (auto& i : v) {
				p->bulletNoKillLayerWhenPlayerDied.push_back(atoi(i.c_str()));
			}
		}
	}


	//���ر���
	p->background.swap(Background::BaseBackground::CreateBackground(r.GetInt("BACKGROUND")));
}
