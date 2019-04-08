#pragma once
#include "StageData.h"
#include "Enemy.h"
#include "GameObjectManager.h"
#include <stack>
namespace Enemy {
	class EnemyManager final
	{
	private:
		std::shared_ptr<StageData> m_stageData;	//�ؿ�����
		int m_nextEnemy = 0;	//��һ�����˵ı��

		GameObjectManager m_enemys;	//��������

		bool m_canCreateByCSV = true;

	public:
		EnemyManager();
		void Reset();	//����״̬
		void ForceKillAll();	//ǿ��ɱ�����е���
		void KillAll();	//ɱ�����е���
		void SetStageEnemyData(const std::shared_ptr<StageData>& e);	//���õ��˳�������
		inline auto GetStageEnemyData() {
			return m_stageData;
		}

		inline auto GetEnemyCSVEnabled() {
			return m_canCreateByCSV;
		}

		//����EnemtData��������
		//BirthTime���ᱻ�Զ�����
		/*inline void InsertEnemy(const StageData::EnemyData& em)
		{
			auto newEnemy = CreateEnemy(em.style);
			newEnemy->Create(em);
			m_enemys.Insert(newEnemy);
		}*/

		//����Ѵ����õĵ���e
		inline void InsertEnemy(Enemy* e) {
			m_enemys.Insert(e);
		}

		void Update();
		void Draw() const;	//ʹ��Sprite2D::UseShader

		auto Size() const {
			return m_enemys.Size();
		}

		auto& operator [](int n) {
			return dynamic_cast<Enemy&>(m_enemys[n]);
		}

		inline auto begin() {
			return m_enemys.begin();
		}

		inline auto end() {
			return m_enemys.end();
		}

		inline void EnableCreateByCSV(bool b) {
			m_canCreateByCSV = b;
		}
	};
}