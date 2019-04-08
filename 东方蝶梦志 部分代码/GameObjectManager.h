#pragma once
#include <vector>
#include "GameObject.h"
#include <memory>
#include <stack>

class GameObjectManager final
{
private:

	//std::mutex m_insertLock;
//protected:
	std::shared_ptr<std::stack<std::unique_ptr<GameObject>>> m_ready;
	std::shared_ptr<std::vector<std::unique_ptr<GameObject>>> m_gos;
public:
	GameObjectManager();
	~GameObjectManager();
	void Draw() const;
	void Update();	//����������Ϸ����

	void KillAll();	//ɱ���Ѵ��ڵ���Ϸ����
	void ForceKillAll();	//ǿ��ɱ�������Ѵ��ڵ���Ϸ����
	void Insert(GameObject* p);

	void Prep(size_t count);

	std::vector<std::unique_ptr<GameObject>>::iterator begin();

	std::vector<std::unique_ptr<GameObject>>::iterator end();

	size_t Size() const;

	GameObject& operator [](int n);
};
