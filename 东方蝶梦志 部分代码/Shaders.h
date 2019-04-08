#pragma once
#include "glew.h"
namespace Basic {

	namespace Shaders {
		void Init();

		//��ͼ������0������Ԫ
		
		//��ɫȦ׼��
		void NegaCircle(float centerX, float centerY, float size);
		void NegaCircle2(float centerX, float centerY, float size);

		//ˮ��
		void WaterWave(float time, float texFactor = 12.0, float ampFactor = 0.01,float centerX = 0,float centerY = 0);

		//�߶�Sin�μ���
		void SinClip(float time, float mul,float heightMul,float height);

		//Բ�δ�С�޶���ˮ��
		void CircleWave(float time,float progress);

		//Barrel BlurЧ��
		void BarrelBlur(float power = 0.3f,float centerX = 0,float centerY = 0);

		//��ҳ��Ч��
		//TEXTURE1 - Source
		//TEXTURE0 - Target
		void PaperRoll(float time);

		//ܳ������
		void GrassAndMoon(float time);

		//Mask
		//0 - Texture
		//1 - Mask
		void MarisaMask(float time);

		//���������ͼ
		void GodRay(float r, float lowestLum, float x, float y);

		//Stage3 ǽ��
		void Stage3RWall(float fogEnd,float time, float playerX, float playerY);

		//�ذ��ϵĻ���
		//	��Ҫ��0�ϰ�Cloud
		void FlameOnBoard(float time);

		//����
		//	��Ҫ0�ϰ�Cloud
		void VistaLight(float time);

		void Stage4Grass(float depth);
		void Stage4Relfection(float time);

		//6�漫��
		//	��Ҫ��0�ϰ�FB
		void Stage6VolumeCloudBefore();
		void Stage6VolumeCloud();

		//Ex��ڰ�Ч��
		//	��0�ϰ󶨱��ڰ׻���ͼ��
		void StageExBW();
		void StageExRelfection(float time);

		//Ex�����Ч��
		//	��0�ϰ�Ҫ��ߵ�ͼ��
		void StageExLineDraw();

		//��˹ģ��
		void GaussBlurW(float radius);
		void GaussBlurH(float radius);

		//��ɫ�����
		void ColorMixer(float delta);

		//�ƶ���Ч
		void DreamSheildBroken(float centerX, float centerY, float time,int mode);

		//Mirrorģʽ�µ���ɫ��Ч
		void MirrorModeWBEffect(float centerX, float centerY);
	}
}
