#pragma once

/* ������Ϸ���߼�����Ϸ���Ľ��� */
class GameActBridge {
public:

	//�����߼����õ���Ϸ��Ļص�
	virtual void OnPlayerAllDied() {}	//���ȫ������ʱ
	virtual void OnStageClear() {}	//���ؿ�ͨ��ʱ
	virtual void FinishSpell(int spellHash, bool bonusGot) {}

	virtual ~GameActBridge() {}
};