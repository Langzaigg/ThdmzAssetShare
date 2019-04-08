#pragma once
#include "NuzPrecompiled.h"
namespace Basic {
	namespace Input {
		enum class Key : int8_t {
			Shoot = 0,
			Bomb = 1,
			Slow = 2,

			Enter = 3,
			Esc = 4,
			F1 = 11,
			F2 = 12,
			F3 = 13,
			F4 = 14,

			Error = -1
		};

		struct Message {
			enum class Type : int8_t{
				KeyDown,
				KeyUp,
				VecMotion,
				WinFocusLost
			}type;
			union {
				Key key;	//������Ϣ�����»�̧��ļ�
				struct {	//ҡ����Ϣ��ҡ�˷�λ
					int32_t x;
					int32_t y;
				}vec;
			};
		};

		void Init();
		void WriteJoystickButtonSetting();
		void LoadJoystickButtonSetting();
		bool Translate(Message& out, const SDL_Event& in);	//������Ϣ�������Ƿ�Ϊ��Чֵ

		bool GetKeyboardMessage(Message&);

		void ResetKeyboardState();

		void EnableInput(bool);

		class JoystickSetupper
		{
		public:
			JoystickSetupper(std::function<void(int)>&&);
			~JoystickSetupper();
		};
	}
}