#pragma once
#include "Dmsl.h"
#include "Bullet.h"
#include "Sprite2D.h"

namespace EnemyBullet {
	class LimitedLazer :
		public EnemyBullet::Bullet
	{
	private:
		std::optional<Dmsl::DmslUnit> m_dmslUnit;
		bool m_dmslKilled = false;	//�����ҪֹͣDmsl����������Ϊtrue

		Basic::Video::Renderer2D::Sprite2D m_sp, m_spShooter;
		bool m_hdrEnabled = false;

		enum {
			BIRTH,
			LIVING,
			GODIE
		}m_birthState;	//�ճ�����״̬�������״̬Ϊtrue���޸�λ��ֻ�������ȡ�

		double m_spShooterAlpha;

		Basic::TaskList m_taskList;
		Basic::DataActor m_dataActor;

		double m_nowSpLength;
		double m_length;

		double m_rotateCenter;

		double m_width;

		bool m_grazed;

		void callDmsl();
		void updateData();

		bool m_showShooter = true;
	public:
		void Create(double x, double y, int style, bool invalid, int dmslUnit, const std::shared_ptr<const Dmsl::DmslVarying>& varyingIn, int live = 200);

		void Update() override;
		void Draw() const override;
		void Kill() override;

		void SetRotateCenter(double center);

		void SetLength(double length);
		void ChangeLength(double end, int time, int func);

		void SetWidth(double width);
		void ChangeWidth(double end, int time, int func);

		virtual void StopDmsl();
		virtual Type WhatTypeAmI() const;

		virtual bool CollCheckWithCircle(const Collision::Circle&) const;	//��Բ��ײ�������ײ���

		virtual void EnableHDR(bool);	//HDR����
											//virtual void HDRSharpness(double) = 0;	//HDR����
											//virtual void ChangeHDRSharpness(int time,double, int slowMotion) = 0;	//HDR����

		virtual void EnableTail(bool);	//��������Ч

		inline void SetShowShooter(bool show)
		{
			m_showShooter = show;
		}

		void* operator new(size_t);
		void operator delete(void* ptr);
	};
}
