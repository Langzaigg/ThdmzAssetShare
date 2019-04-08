#pragma once

namespace AfterEffect {
	class BaseAfterEffect {
	public:
		virtual ~BaseAfterEffect() {}
		virtual void Draw() const = 0;	//��ʱ����ʱ���Ѿ���������TEXTURE0
		virtual void Update() = 0;
		virtual bool Killed() = 0;
	};
}
