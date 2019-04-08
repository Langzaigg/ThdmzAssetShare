#pragma once
#include "Activity.h"
#include "Game.h"
#include "GameActBridge.h"
#include "RecoderInputer.h"
#include "ReplayerInputer.h"
#include "SnowRVReader.h"
#include "Sprite2DWStreamLayout.h"
#include "GamePausedActivity.h"

/* ��Ϸ� */
/* ��������Ϸ�߼���� */

//#define REPLAYMODE

namespace Activities {


	class GameMainActForDesign final :public Basic::ActivityEngine::Activity
	{
	private:
		class BridgeForDesign :public GameActBridge {
		private:
			GameMainActForDesign* m_act = nullptr;
		public:
			void OnPlayerAllDied() override;	//�������ʱ
			void OnStageClear() override;	//���ؿ�ͨ��ʱ

			void SetActivity(GameMainActForDesign* act) {
				m_act = act;
			}
		};

		std::shared_ptr<StageData> m_stageData;

		std::shared_ptr<Activities::GamePausedActivity> m_pauseActivity;

/*#ifdef REPLAYMODE
		Inputer::ReplayerInputer m_inputer;
#else
		Inputer::RecoderInputer m_inputer;
		GameInitData m_gameInitData;
#endif*/
		bool m_replayMode = false;

		std::unique_ptr<Inputer::BaseInputer> m_inputer;
		GameInitData m_gameInitData;

		bool m_debug_3xSpeed = false;	//���ԣ�F1�Ƿ���->�Ƿ��������������ٶ�

		BridgeForDesign m_bridge;

		std::optional<Basic::SnowRVReader> m_debugInfo;
	public:
		GameMainActForDesign(bool replayMode = false);
		~GameMainActForDesign();
		
		void OnEntry() override;
		void OnDraw() const override;
		void OnUpdate(float deltaTime) override;
		void OnEvent(const Basic::Input::Message&) override;
	};

}