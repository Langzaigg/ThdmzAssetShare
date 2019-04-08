#include "Precompiled.h"
#include "Shooter.h"

#include "Game.h"
void Shooter::Shooter::Execute(std::function<void(double angle, double offset_x, double offset_y)> func,double org_x,double org_y)
{
	if (spy) {
		double x, y;
		Game::GetGame().GetPlayer().GetPos(x, y);

		org_x += radius;

		angle = atan2(y - org_y, x - org_x) / 3.1415926535897932384 * 180;
	}
	
	for (int i = 0; i < ways; ++i) {
		//���Բ�ϵĽǶ�
		double pointAngle = 360.0 / ways*i;
		pointAngle += 360.0/2.0/ways;
		
		//�任������
		double pointAngle2 = (vecangle - pointAngle * range / 360 +range / 2);
		pointAngle2 = pointAngle2 * 3.1415926535897932384 / 180;

		//��������
		double x = cos(pointAngle2) * radius;
		double y = sin(pointAngle2) * radius;

		//��������
		pointAngle = (- pointAngle * range / 360 + range / 2);
		pointAngle = pointAngle * 3.1415926535897932384 / 180;

		double x2 = cos(pointAngle);
		double y2 = sin(pointAngle);

		//������������Ƕ�
		double outAng = atan2(y2, x2)+ angle / 180.0 * 3.1415926535897932384;
		outAng = outAng * 180 / 3.1415926535897932384;

		//����
		func(outAng, x, y);
	}
}
