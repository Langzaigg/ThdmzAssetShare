#pragma once
#include "Sprite2D.h"
namespace Basic {
	namespace Video {
		namespace Renderer2D {
			class Animation2D final: public Basic::Video::Renderer2D::Sprite2D
			{
			private:
				int m_allFrame = 0, m_nowFrame = 0,m_begin = 0,m_timer = 0,m_screenFrame_frame = 0;
				Basic::Video::LowerRenderer::GLTexture::UVRect m_imageRect;
				void setSrc(int num);
			public:
				using Sprite2D::UseImage;
				//UseImage���ö�����ctx�ļ�,ÿ������Ļ֡��һ֡��������ʼ��ͼ���ţ��߹���ͼ���š�
				void UseImage(const std::string& ctx,int screenFrame_frame, int begin, int num = -1);
				inline void UseText(){}	//��Ҫʹ��UseText����
				void Update();
				inline void Draw() const
				{
					Sprite2D::Draw();
				}

				inline auto GetNowFrame()
				{
					return m_nowFrame;
				}

				//����ǰ������Ҫ�ȵ���Sprite2D::UseShader
			};
		}
	}
}