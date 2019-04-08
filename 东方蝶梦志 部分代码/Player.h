#pragma once
#include "BaseInputer.h"
#include "BasicChar.h"
#include "Animation2D.h"
#include "SeManager.h"
#include "GameObjectWithDmslControl.h"
#include "BasicOption.h"
#include "Collision.h"
#include "TaskList.h"
#include <vector>
#include <memory>
#include <optional>
#include "DataActor.h"
#include "PlayerSheild.h"
class Player final//:public GameObject	//��ҿ�����
{
public:
	enum PlayerState{
		NORMAL,	//����ģʽ��
		BIRTHING,	//���ڳ���
		DIED,	//�Ѿ�����
		COMMING_TO_DEATH	//������
	};
private:
	Basic::Video::Renderer2D::Animation2D m_charAnime;	//�Ի�����
	Char::BasicChar* m_char;

	double m_normalSpeed = 0, m_slowSpeed = 0;	//��ͨ�ٶ��������ٶ�
	double m_vec_angle;
	double m_vec_speed;
	bool m_vec_push = false;
	bool m_slow = false;	//����ģʽ
	bool m_shoot = false;	//�Ƿ�Ϊ���״̬

	int m_invincible = 0;	//�޵�״̬

	unsigned m_timer = 0;	//��ʱ��

	bool m_flip = false;

	double m_speedMul = 1.0;	//�ƶ��ٶȱ���

	double m_power = 0;
	double m_powerTop;

	Basic::DataActor m_dataActor;

	Basic::TaskList m_comingToDeath;	//����ר�������ֻ�ܴ����������

	double m_collDisplayProgress = 0;	//�����ж����ʾ���Ͳ����ж����ʾ���Ķ������ȣ�1Ϊ��ʾ��0Ϊ����
	double m_collAngle = 0;	//Graze�ж�����ת����
	double m_collAngleSpeed = 0.5f;	//Graze�ж�����ת�����ٶ�

	Collision::Circle m_graze, m_death;

	PlayerState m_state = DIED;

	/* ������� */
	double m_x = -9999, m_y = -9999;

	/* �Ż������� */
	std::unique_ptr<Char::BasicOption> m_options;

	/* ���ֿ��� */
	bool m_bombEnabled = true;
	bool m_shootEnabled = true;

	/* �������� */
	bool m_shootBombEnabled = true;

	//int m_shootDisable_counter = 0;

	std::optional<PlayerSheild> m_sheild;

	/* Shoot Key Event */
	std::function<void()> m_shootKeyEvent = []() {};

public:
	inline void SetBombEnable(bool b) {
		m_bombEnabled = b;
	}
	inline void SetMoveSpeedMul(double m) {
		m_speedMul = m;
	}
	void SetShootEnable(bool b);
	bool GetShootEnabled() const;

	void Draw() const;	//����ǰҪ����ΪSprite2D����ɫ��
	void Update();
	void SetChar(Char::BasicChar&);

	void OnEvent(const Basic::Input::Message&);

	inline void SetShootBombEnabled(bool b)
	{
		m_shootBombEnabled = b;
	}

	void ForceKill();
	void Kill();
	void Birth();

	void PowerUp(double add);

	std::optional<PlayerSheild>& GetSheild();
	

	void SetPower(double power);

	inline void Invincible(int frame) { m_invincible = frame; }	//�����޵�״̬��֡����
	inline bool IsInvincible() { return m_invincible > 0; }

	inline const Collision::Circle& GetGrazeCollision() const {
		return m_graze;
	}

	inline const Collision::Circle& GetDeathCollision() const {
		return m_death;
	}

	inline bool Died() const {
		return m_state == DIED;
	}

	inline auto GetState() const {
		return m_state;
	}

	void OnGraze();

	void SetOption(Char::BasicOption* o) {
		m_options.reset(o);
		m_options->SetPower(int(m_power));
	}

	inline Char::BasicOption& GetOption() const {
		return *m_options;
	}

	inline Char::BasicChar* GetChar() const {
		return m_char;
	}
	inline void GetPos(double& x, double& y) const {
		x = m_x;
		y = m_y;
	}

	void SetPos(double x, double y);

	void SetShootKeyEvent(std::function<void()> e) {
		m_shootKeyEvent = e;
	}

	inline bool Bombing() const {
		return m_char->Bombing();
	}

	inline bool Slow() const {
		return m_slow;
	}

	inline bool PowerMax() const {
		return m_power == m_char->GetPowerTop();
	}

	inline auto GetPower() const {
		return m_power;
	}
};
