#pragma once
#include "GameObjectManager.h"
#include "BaseInputer.h"
#include "Player.h"
#include "StageData.h"
#include "PlayerBulletManager.h"
#include "EnemyManager.h"
#include "TaskList.h"
#include "Particle3D.h"
#include "ItemManager.h"
#include "DataActor.h"
#include "StageTaskRunner.h"
#include "Sp2DObject.h"
#include "GameActBridge.h"
#include "UIManager.h"
#include "BaseAfterEffect.h"
#include "ScoreManager.h"
#include "GLTexture.h"
#include "EnemyBulletManager.h"
#include "WarningLineSystem.h"
#include "EnemyAnimation.h"
/* ��Ϸ״̬��ʼ���� */
struct GameInitData {
	/* Player���� */
	double power;	//����

	/* �������� */
	uint16_t life, lifeKagera;
	
	/* ���� */
	uint64_t score;

	/* �γ� */
	double dream;

	/* ������� */
	double playerX, playerY;

	/* Graze */
	uint32_t graze;

	void WriteToStream(std::ostream&) const;
	void ReadFromStream(std::istream&);
};

/* ��Ϸ�߼����� */
class Game final
{
private:
	std::optional<UI::UIManager> m_ui;

	ScoreManager m_score;

	Player m_player;	//һ�����
	Inputer::BaseInputer* m_inputer = nullptr;	//������
	std::shared_ptr<StageData> m_stageData;	//�ؿ�����
	PlayerBulletManager m_playerBulletManager;	//�ҷ��ӵ�������
	Enemy::EnemyManager m_enemyManager;	//���˹�����
	Enemy::EnemyAnimation m_enemyAnimation;	//���˻�����Ч������

	int m_mainTimer;	//��Ϸ����ʱ��

	Basic::Video::Renderer3D::Particle3D m_parTop;	//�����������ϵͳ
	Basic::Video::Renderer3D::Particle3D m_parBottom;	//��Ϸͼ�����������ϵͳ

	EnemyBullet::EnemyBulletManager m_enemyBulletManager;	//�����ӵ�������
	GameObjectManager m_miscManager, m_miscManagerBottom;	//������Ϸ���������
	GameObjectManager m_inManager;

	Sp2DObject m_playerDeathCollDisplay, m_playerGrazeCollDisplay;	//�����ж���ʾ���Ͳ����ж���ʾ��

	Item::ItemManager m_items;

	Basic::TaskList m_taskList;
	Basic::DataActor m_dataActor;

	StageTask::StageTaskRunner m_runningStageTask;

	GameActBridge* m_gameActBridge = nullptr;

	std::vector<std::unique_ptr<AfterEffect::BaseAfterEffect>> m_afterEffects;

	WarningLineSystem m_warningLineSystem;

	bool m_drawStageBackground = true;

	int m_screenWidth, m_screenHeight;

	double m_bossPosY = -9999;	//-9999Ϊ�ر�
	double m_bossPosYAlpha = 0;
	Basic::Video::Renderer2D::Sprite2D m_bossPosDisplay;

	void loadStageTaskFromStageData();

	std::vector<std::function<void()>> m_importantTask;

	std::optional<std::shared_ptr<Basic::Video::LowerRenderer::GLTexture>> m_mirror;
public:

	void Init();
	void Quit();
	void Reset();	//����һ����Ϸ�߼�

	inline void SetBossPosY(double y) {
		if (y == -9999 && m_bossPosY != -9999) {
			m_taskList.AddTask([this]() {
				m_bossPosY = -9999;
			}, 50);
			m_dataActor.Add(m_bossPosYAlpha, 0, 50, 1);
		}
		else if (m_bossPosY == -9999 && y != -9999) {
			m_dataActor.Add(m_bossPosYAlpha, 1, 50, 1);
			m_bossPosY = y;
		}
		else m_bossPosY = y;
	}

	inline bool HaveBoss() {
		return m_bossPosY != -9999;
	}

	void SetMirrorMode(bool b);
	bool GetMirrorMode() const;

	bool IsMirrorMode() const;

	void Draw();
	void Update();
	void SetInputer(Inputer::BaseInputer&);	//����������
	void ReleaseKeys();	//ȡ�����еİ���״̬
	inline Inputer::BaseInputer& GetInputer() { return *m_inputer; }	//��ȡ������

	inline void AddAfterEffect(AfterEffect::BaseAfterEffect* b) {
		m_afterEffects.push_back(std::unique_ptr<AfterEffect::BaseAfterEffect>(b));
	}

	inline void GetScreenSize(int& w, int& h) {
		w = m_screenWidth;
		h = m_screenHeight;
	}

	inline Player& GetPlayer() { return m_player; }	//��ȡ��Ҷ���
	inline PlayerBulletManager& GetPlayerBulletManager() { return m_playerBulletManager; }	//��ȡ��Ҷ���
	inline auto& GetEnemyBulletManager() { return m_enemyBulletManager; }	//��ȡ�����ӵ�������
	inline auto& GetEnemyManager() { return m_enemyManager; }

	void SetStageData(const std::shared_ptr<StageData>&);	//���ùؿ�����
	const std::shared_ptr<StageData>& GetStageData() {	//��ȡ�ؿ�����
		return m_stageData;
	}

	inline int GetGameTime() { return m_mainTimer; }	//��ȡ��ǰ��Ϸʱ��

	inline Basic::Video::Renderer3D::Particle3D& GetParticleTop() {	//��ȡ���Ϸ�����ϵͳ
		return m_parTop;
	}
	inline Basic::Video::Renderer3D::Particle3D& GetParticleBottom() {	//��ȡ�·�����ϵͳ
		return m_parBottom;
	}

	inline Sp2DObject& GetPlayerDeathCollDisplay() {
		return m_playerDeathCollDisplay;
	}

	inline Sp2DObject& GetPlayerGrazeCollDisplay() {
		return m_playerGrazeCollDisplay;
	}

	inline GameObjectManager& GetUILayerGameObjectManager() {
		return m_miscManager;
	}

	inline void SetBackground(std::unique_ptr<Background::BaseBackground>&& bk)
	{
		m_stageData->background = std::move(bk);
	}

	inline auto& GetMiscManagerBottom() {
		return m_miscManagerBottom;
	}

	inline auto& GetMiscManagerTop() {
		return m_inManager;
	}

	inline Item::ItemManager& GetItemMgr() {
		return m_items;
	}

	inline Basic::TaskList& GetTaskList() {
		return m_taskList;
	}

	inline Basic::DataActor& GetDataActor() {
		return m_dataActor;
	}

	inline auto& GetEnemyAnimation()
	{
		return m_enemyAnimation;
	}

	inline void SetGameActBridge(GameActBridge* b) {
		m_gameActBridge = b;
	}

	inline GameActBridge* GetGameActBridge() {
		return m_gameActBridge;
	}

	inline void SetStageBackgroundEnabled(bool b) {
		m_drawStageBackground = b;
	}

	inline auto& GetUI() {
		return *m_ui;
	}

	inline auto& GetScoreManager() {
		return m_score;
	}

	inline auto GetLevel() {
		return m_stageData->level;
	}

	inline auto& GetWarningLineSystem() {
		return m_warningLineSystem;
	}

	void LoadFromInitData(GameInitData&);
	void WriteToInitData(GameInitData&);

	inline void AddImportantTask(const std::function<void()>& func)
	{
		m_importantTask.push_back(func);
	}

	std::shared_ptr<Basic::Video::LowerRenderer::GLTexture> Screenshot() const;

	static Game& GetGame();
};
