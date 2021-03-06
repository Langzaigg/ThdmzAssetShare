#pragma once
#include <string>
#include "GLTexture.h"
#include "GLCallList.h"
#include <memory>
#include <map>
namespace Basic {
	namespace Video {
		namespace Renderer2D {

			const int FASTBUFFER_BLEND_NORMAL = 0;
			const int FASTBUFFER_BLEND_HDR = 1;

			/* 移动和复制Sprite2D及其子类都是不被允许的操作 */
			class Sprite2D
			{
			private:
				double m_r = 1, m_g = 1, m_b = 1;
				double m_alpha = 1, m_angle = 0;
				double m_x, m_y;
				double m_centerX = 0, m_centerY = 0;

				bool m_flipX = false, m_flipY = false;


				struct SingleFastBuffer {
					std::vector<double> drawVerts, texCoords, colors;
				};
				static std::map<std::shared_ptr<Basic::Video::LowerRenderer::GLTexture>, SingleFastBuffer> m_fastBuffer[2];
			protected:
				std::shared_ptr<Basic::Video::LowerRenderer::GLTexture> m_tex;
				int m_texNum = 0;
				int m_w, m_h;

				double m_drawVerts[8] = { 0 }, m_drawTexCoords[8];

			public:

				Sprite2D(const Sprite2D&) = delete;
				Sprite2D(Sprite2D&&) = delete;
				const Sprite2D& operator = (Sprite2D&&) = delete;
				const Sprite2D& operator = (const Sprite2D&) = delete;

				Sprite2D();
				virtual ~Sprite2D();
				const double* GetDrawVerts() const{ return m_drawVerts; }
				const double* GetDrawTexCoords() const { return m_drawTexCoords; }
				void UseImage(const std::string& ctx, int num = 0);
				void UseImage(SDL_Surface*,bool needConvert = false);
				void Clear();
				inline void SetFlip(bool x, bool y) {	//设置精灵是否绕x轴，y轴翻转。
					m_flipX = x, m_flipY = y;
				}
				inline void SetAlpha(double alpha)
				{
					m_alpha = alpha;
				}
				inline void SetColorFliter(double r, double g, double b)
				{
					m_r = r;
					m_g = g;
					m_b = b;
				}

				void UpdateVertex();

				inline auto& GetTexture() const {
					return m_tex;
				}

				inline auto GetSpriteSize() const {
					return std::make_pair(m_w, m_h);
				}

				inline void GetSize(int& w, int& h) { m_tex->GetSize(m_texNum,w,h); }


				inline void SetPos(double x, double y)
				{
					m_x = x; m_y = y;
				}

				inline std::pair<double, double> GetPos() const
				{
					return std::make_pair(m_x, m_y);
				}

				inline void SetCenter(double x, double y) {
					m_centerX = x;
					m_centerY = y;
				}

				inline void SetSize(int w, int h)
				{
					m_w = w / 2;
					m_h = h / 2;
					SetPos(m_x, m_y);
				}
				inline void SetAngle(double angle) {
					m_angle = angle;
				}

				inline void SetZoom(double zoom) {
					int w, h;
					m_tex->GetSize(w, h);
					auto rect = m_tex->GetUVRect(m_texNum);
					SetSize(int(rect.w*zoom * w), int(rect.h*zoom*h));
				}
				void Draw() const;
				void OldDraw() const;

				void DrawToFastBuffer(int fastBufferIndex = 0) const;
				static void DrawFastBuffer();
				static void ClearFastBuffer();
			};

		}
	}
}
