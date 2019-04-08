#pragma once
#include "Bullet.h"
#include "Animation2D.h"
#include "Collision.h"

#include "StageData.h"

namespace EnemyBullet {
	class CircleBullet :public Bullet {
	private:
		std::optional<Dmsl::DmslUnit> m_dmslUnit;	//�ű�
		Basic::Video::Renderer2D::Animation2D m_bulletImage;	//ͼ��
		bool m_animated;

		int m_minLiveOutScreen;		//����Ļ�����������ʱ��

		double m_size = 1.0;	//��С����
		double m_alpha = 1.0;	//͸����

		bool m_dmslUsing;	//�Ƿ�����ʹ��Dmsl

		int m_radius;	//�ӵ�ͼ��뾶

		bool m_nograze;
		double m_collRadius;	//�ӵ���ײ�뾶��ԭͼ��

		Collision::Circle m_collision;

		int m_goDie = -1;	//������ȫ�������е�֡��

		double m_r = 1, m_g = 1, m_b = 1;	//��ɫFliter

		bool m_hdrEnabled = false;
		//double m_hdrSharpness = 0;

		bool m_tailEnabled = false;

		bool m_forcedColli = false;	//����͸����ǿ�ƽ�����ײ���

		int m_style, m_subStyle;

		//����ͼ��Ƕ�
		enum ImageAngleMode {
			UseImageAngle,
			UseAngle,
			AutoRotate
		};
		ImageAngleMode m_imageAngleMode;
		double m_imageAngle = 0;

		void addATail(double angle) const;
		void callDmsl();
	public:
		~CircleBullet() override;
		void StopDmsl() override;
		void Update() override;
		void Draw() const override;
		void Kill() override;

		inline void SetImageAngleEnabled(bool b) {
			m_imageAngleMode = b ? UseImageAngle : UseAngle;
		}

		inline void EnableAutoRotate() {
			m_imageAngleMode = AutoRotate;
		}

		inline void SetImageAngle(double angle) {
			m_imageAngle = angle;
		}

		inline void SetForcedColli(bool t)
		{
			m_forcedColli = t;
		}

		//xλ��,yλ��,�����,��ʽ���,Dmsl����Ԫ��,��С��Ļ������ʱ��,�Ƿ񲻿��Ա����иɵ�,Dmsl�ű�
		void Create(double x, double y, int style, int subStyle, int dmslUnit, int minLiveOutScreen, bool invalid, const std::shared_ptr<const Dmsl::DmslVarying>& varyingIn);

		//���ĵ���
		void ChangeStyle(int style, int subStyle);
		//����n1֡�����ӵ�����Ϊn2�Ĵ�С��������1Ϊԭʼ��С��
		inline void Zoom(int n1, double n2, int slowMotion) {
			m_dataActor.Add(m_size, n2, n1, slowMotion);
			//if (GameObjectWithDmslControl::GetTaskNoteModeEnabled())
				//m_dataActor.Add(m_size, n2, n1, slowMotion);
			//else
				//GameObjectWithDmslControl::AddTask([this, n1, n2, slowMotion]() {
				//m_dataActor.Add(m_size, n2, n1, slowMotion);
			//});
		}

		inline void SetZoom(double zoom) {
			m_size = zoom;
		}

		//����n1֡�����ӵ�������͸����Ϊn2��0~1��
		inline void Fade(int n1, double n2, int slowMotion) {
			m_dataActor.Add(m_alpha, n2, n1, slowMotion);
			/*if (GameObjectWithDmslControl::GetTaskNoteModeEnabled())
				m_dataActor.Add(m_alpha, n2, n1, slowMotion);
			else
				GameObjectWithDmslControl::AddTask([this, n1, n2, slowMotion]() {
					m_dataActor.Add(m_alpha, n2, n1, slowMotion);
			});*/
		}

		inline void ColorChange(double r, double g, double b, int slowMotion, int frame) {
			m_dataActor.Add(m_r, r, frame, slowMotion);
			m_dataActor.Add(m_g, g, frame, slowMotion);
			m_dataActor.Add(m_b, b, frame, slowMotion);
		}

		void EnableHDR(bool) override;	//HDR����
		//void HDRSharpness(double) override;	//HDR����
		//void ChangeHDRSharpness(int time, double, int slowMotion) override;	//HDR����

		void EnableTail(bool) override;

		bool CollCheckWithCircle(const Collision::Circle&) const override;	//��Բ��ײ�������ײ���

		Bullet::Type WhatTypeAmI() const override;

		void* operator new(size_t);
		void operator delete(void* ptr);
	};

	//��Ӱ
	class CircleBulletTail :public Bullet {
	private:
		double m_alpha = 1;
		Basic::Video::Renderer2D::Sprite2D m_image;

		bool m_hdrEnabled = false;
	public:
		void StopDmsl() override;
		void Update() override;
		void Draw() const override;
		void Kill() override;

		void EnableHDR(bool) override;	//HDR����
		//void HDRSharpness(double) override;	//HDR����
		//void ChangeHDRSharpness(int time, double, int slowMotion) override;	//HDR����

		void EnableTail(bool) override;

		bool CollCheckWithCircle(const Collision::Circle&) const override;	//��Բ��ײ�������ײ���

		Bullet::Type WhatTypeAmI() const override;

		CircleBulletTail(int style, int subStyle, double size, double x, double y, double r, double g, double b, double angle, double alpha, bool hdr);

		void* operator new(size_t);
		void operator delete(void* ptr);
	};
}
