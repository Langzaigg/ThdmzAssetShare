#pragma once
#include <string>
namespace SaveSystem
{

	//��ֹ����Ϸ�߼������ô��࣡����
	class PlayerProfile
	{
	private:
		struct PODFileContent
		{
			wchar_t playerName[10];
			bool practiceEnabled[7] = { true,false,false,false,false,false,false };
			bool gameStartExtraEnabled = false;
			bool mirrorModeEnabled = false;
			bool mirrorEnabled = false;

			uint32_t spellGotTimes[10000];
			uint32_t spellTimes[10000];
		};

		PODFileContent m_podContent;

		PlayerProfile();

		void flush();
	public:
		void SetPlayerName(const wchar_t* name);
		std::wstring GetPlayerName() const;

		//stageNumber - 0ΪStage1��1ΪStage2��6ΪStageEx
		bool GetPracticeEnabled(int stageNumber) const;

		//stageName
		void EnablePractice(const std::string& stageName);

		//�Ƿ�GameStart�����ʹ��Extra�ؿ�
		bool GameStartExtraEnabled() const;

		//����GameStart���Extra�ؿ�
		void EnableGameStartExtra();

		//��ȡ��������
		std::tuple<uint32_t, uint32_t> GetSpellGotNumber(int spellHash);

		//�����޸�
		void SpellFinished(int spellHash,bool gotBonus);

		static PlayerProfile& Get();
	};
}