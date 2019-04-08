#pragma once
#include <string>
#include <SDL.h>
#include "Asset.h"
#include <memory>
#include "LowerSound.h"
namespace Basic {
	namespace Sound {
		class BgmPlayer;

		/* �Ķ��ó���ǰ�����Ķ����������ۡ���79ҳ */

		namespace BGMData {
			struct BGMData {
				int loopNum, headNum;
				int title, beatType;
				double frame_beat;
			};

			void Init();
			const BGMData& GetBGMData(int n);
		}

		class BgmPlayer final
		{
		private:
			static const BGMData::BGMData* m_now;
			static int m_nowBeatNum;
			static bool m_isBeat;
			static bool m_paused;
			static double m_cnt;
		public:

			static void Play(int n,bool fadeIn = false);
			static void Esc();
			static void Resume();
			static void Stop(bool fadeOut = true);

			inline static int GetBeatNum() {return m_nowBeatNum;}	//һ��ȫ�����ڵ�ǰ�ĵڶ��ٸ���
			inline static bool IsBeatFrame() {return m_isBeat;}	//��ǰ֡�Ƿ�����˽���

			inline static void Update() {	//ֻ����ActivityEngine�е���
				if (m_paused) return;
				m_cnt+=1;
				if (m_now->frame_beat <= m_cnt) {
					m_cnt -= m_now->frame_beat;
					m_isBeat = true;
					++m_nowBeatNum;
					if (m_nowBeatNum >= m_now->beatType) {
						m_nowBeatNum = 0;
					}
				}
				else m_isBeat = false;
			}

			inline static void SetPaused(bool b)
			{
				m_paused = b;
			}

			inline static const BGMData::BGMData& GetBgmData() {
				return *m_now;
			}
		};
	}
}