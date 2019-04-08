#include "NuzPrecompiled.h"
#include "NumberDisplay.h"
#include "glew.h"

Basic::Video::Renderer2D::NumberDisplay::NumberDisplay(const std::string & styleTex) {
	m_tex = LowerRenderer::ImageCacheManager::LoadImage(styleTex);

	int w, h;
	m_tex->GetSize(w, h);

	for (int i = 0; i <= 9; ++i) {

		const auto& imageRect = m_tex->GetUVRect(i);

		double singleW = imageRect.w * w, singleH = imageRect.h * h;
		m_singleW += singleW;
		
		drawNumber[i].DefineBegin(); {
			glBegin(GL_QUADS); {
				glTexCoord2d(imageRect.x, imageRect.y); glVertex2d(0,0);	//����
				glTexCoord2d(imageRect.x + imageRect.w, imageRect.y); glVertex2d(singleW, 0);	//����
				glTexCoord2d(imageRect.x + imageRect.w, imageRect.y + imageRect.h); glVertex2d(singleW, singleH);	//����
				glTexCoord2d(imageRect.x, imageRect.y + imageRect.h); glVertex2d(0, singleH);	//����
			}
			glEnd();
			glTranslated(singleW, 0, 0);
		}
		LowerRenderer::GLCallList::DefineEnd();
	}

	m_singleW /= 10;
}

void Basic::Video::Renderer2D::NumberDisplay::Draw() const
{
	glColor4d(m_r, m_g, m_b, m_alpha);
	if (m_leftTopPos) {
		//��������ģʽ
		//����λ��
		glTranslated(- m_singleW * (m_displayFormat == -1 ? m_number.size() : m_displayFormat), 0, 0);
	}
	glTranslated(m_x, m_y,0);
	glScaled(m_zoom, m_zoom, 0);

	glBindTexture(GL_TEXTURE_2D, *m_tex);

	if (m_displayFormat != -1) {
		//�Ȼ��Ƽ���0
		int zeroCnt = m_displayFormat - m_number.size();
		if (zeroCnt < 0) {
			//������
			//��ȫ������Ϊ9���ж�
			for (int i = 0; i < m_displayFormat; ++i) {
				drawNumber[9]();
				
			}
			return;
		}
		else {
			for (int i = 0; i < zeroCnt; ++i) {
				drawNumber[0]();
			}
		}
	}
	//�޸�ʽֱ�ӻ���
	for (auto p : m_number) {
		drawNumber[p]();
	}
	glLoadIdentity();
}
