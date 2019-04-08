#pragma once
#include "Dmsl.h"
#include "GameObjectWithDmslControl.h"
#include <memory>
#include "StageData.h"
#include "Collision.h"
namespace EnemyBullet {
	class Bullet :public GameObjectWithDmslControl {
	protected:
		//bool m_invailed;	//�Ƿ���Ա����������
		static Dmsl::GameObjectLibraryLinkTable m_dmslLinkTable;
		static std::unique_ptr<Dmsl::DmslVirtualMachine> m_bulletScript;

		bool m_invincible = false;

		static void linkScript(Dmsl::DmslVirtualMachine&);
	public:
		enum class Type {
			Circle, CircleTail, LimitedLazer, UnlimitedLazer, Grid
		};

		~Bullet() override;

		static void SetLevel(StageLevel l);
		static void LoadScript();

		inline bool GetInvincible() {
			return m_invincible;
		}

		inline void SetInvincible(bool b) {
			m_invincible = b;
		}

		void Update() override = 0;
		void Draw() const override = 0;
		void Kill() override = 0;
		virtual void StopDmsl() = 0;
		virtual Type WhatTypeAmI() const = 0;

		virtual bool CollCheckWithCircle(const Collision::Circle&) const = 0;	//��Բ��ײ�������ײ���

		virtual void EnableHDR(bool) = 0;	//HDR����
		//virtual void HDRSharpness(double) = 0;	//HDR����
		//virtual void ChangeHDRSharpness(int time,double, int slowMotion) = 0;	//HDR����

		virtual void EnableTail(bool) = 0;	//������ر���Ӱ

		//xλ��,yλ��,�����,��ʽ���,Dmsl����Ԫ��,��С��Ļ������ʱ��,�Ƿ񲻿��Ա����иɵ�,Dmsl�ű�
		//������
		//virtual void Create(double x, double y, int style, int subStyle, int dmslUnit, int minLiveOutScreen, bool invalid, Dmsl::DmslVirtualMachine& dmsl, double dmslArg) = 0;
	};
}
