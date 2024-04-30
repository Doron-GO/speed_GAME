#pragma once
#include"../Vector2D.h"
#include"Collision.h"
using Vec = Vector2DFloat;

struct Raycast
{
	struct Ray {

		Vec p; //�n�_
		Vec vec;//�����x�N�g��
	};
	struct Line {
		Vec p; //�n�_
		Vec end;//�I�_

	};
	bool CheckCollision(Ray ray, Collision collision , Vec playerPos);
	bool CheckCollision( Collision collision , Vec playerPos);
	bool CheckRay(Ray ray, Line line, Vec offset);
	bool CheckRectangle(Collision collision, Vec pos);

	//�����蔻�������֐�
	bool RectToRectCollision(Vec pMin, Vec pMax, Vec iMin, Vec iMax);
	//�̓����蔻��ォ��̏���
	bool TopSide(Vec Max, Vec Min);
	bool DownSide(Vec Max, Vec Min);
	bool LeftSide(Vec Max, Vec Min);
	bool RightSide(Vec Max, Vec Min);



	//bool CheckRectangle(Ray ray, Collision collision, Vector2DFloat playerPos)
};

