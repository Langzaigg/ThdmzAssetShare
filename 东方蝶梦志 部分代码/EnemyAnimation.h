#pragma once
#include <vector>

namespace Enemy {
	class EnemyAnimation
	{
	private:
		struct Animation
		{
			double angle;
			double frame;
			double r, g, b;
			double x, y;
		};

		std::vector<Animation> m_animation;

	public:
		void Push(double x,double y,double r, double g, double b);
		void Update();
		void Draw() const;	//���棡����Ҫ������FastBuffer��ʹ��ǰ���FastBuffer��ʹ�ú�FastBufferΪ�ա�

		inline void Clear()
		{
			m_animation.clear();
		}
	};
}
