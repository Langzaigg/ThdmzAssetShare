#pragma once
#include "Sprite2D.h"
#include "BasicOption.h"
#include "SnowRVReader.h"
#include <string>
#include <memory>

namespace Char {
	class BasicChar	//������Ϸ����
	{
	private:
		double m_normalSpeed, m_slowSpeed;
	public:
		virtual ~BasicChar() {};

		virtual void Reset() {};

		virtual int GetSprite2DImageNum() = 0;	//��ҵ�ͼ����

		inline void SetNormalSpeed(double s) {
			m_normalSpeed = s;
		}
		inline void SetSlowSpeed(double s) {
			m_slowSpeed = s;
		}
		inline double GetNormalSpeed() const {	//��ȡ��ͨ�ٶ�
			return m_normalSpeed;
		}
		inline double GetSlowSpeed() const {	//��ȡ�����ٶ�
			return m_slowSpeed;
		}

		virtual double GetPowerTop() = 0;	//��ȡ��������
		virtual void PowerUp(double now, double add) = 0;	//��������ʱ����ǰ������Ļ����Լ���������

		virtual void ShootBegin(double x, double y, bool flip) = 0;	//��ʼ�����ӵ�ʱ
		virtual void ShootUpdate(double power, double x, double y, bool flip) = 0;	//�����ӵ�ʱ
		virtual void ShootEnd(bool flip) = 0;	//ֹͣ�����ӵ�ʱ

		virtual void Update(double x, double y) = 0;	//������ĸ���

		virtual std::unique_ptr<BasicOption> CreateOption() = 0;	//����һ��Optionָ�룬����Player����

		virtual void Bomb(bool flip) = 0;	//����ʱ

		virtual bool Bombing() = 0;

		virtual const char* GetName() = 0;
	};

	void LoadAndSetConfig();
}