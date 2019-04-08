#pragma once

namespace Char {
	class BasicOption {
	protected:
		bool m_died;
	public:
		virtual ~BasicOption() {};

		inline bool Died() {
			return m_died;
		}

		virtual void OnUpdate(double x, double y) = 0;	//����
		virtual void OnDraw() const = 0;	//Ҫ�����ʱ

		virtual void OnSlowStart() = 0;	//��ʼSlowģʽʱ
		virtual void OnSlowStopped() = 0;	//Slowģʽֹͣʱ

		virtual void ShootBegin(bool flip) = 0;	//��ʼ�����ӵ�ʱ
		virtual void ShootUpdate(bool flip) = 0;	//�����ӵ�ʱ
		virtual void ShootEnd(bool flip) = 0;	//ֹͣ�����ӵ�ʱ

		virtual void SetPower(int) = 0;	//���û���
	};
}