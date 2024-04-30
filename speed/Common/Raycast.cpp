#include "Raycast.h"
#include"../_debug/_DebugDispOut.h"
#include<DxLib.h>
bool Raycast::CheckCollision(Ray ray, Collision collision, Vec playerPos)
{// ���㉺���E�̈��
    Raycast::Line lines[4] = {  

    //��̕�   
    {collision.first,
        (collision.first )+ Vec{collision.second.x,0} },
    //�E��
    {(collision.first) + Vec{collision.second.x,0} ,
            collision.first + collision.second },
    //���̕�
    { collision.first + collision.second ,
    collision.first + Vec{0,collision.second.y } },
    //����
    { collision.first + Vec{0,collision.second.y} ,
    collision.first }
    };

    bool reslut = false;
    for (auto line : lines)
    {
        reslut |=   CheckRay(ray,line, playerPos);
    }
    return reslut;
}

bool Raycast::CheckCollision(Collision collision, Vec playerPos)
{

    bool reslut = false;
    reslut |= CheckRectangle(collision, playerPos);

    return reslut;
}

bool Raycast::CheckRay(Ray ray, Line line, Vec offset)
{

    //�f�o�b�O�p�̎��ۂ̓����蔻���Ԃ����C���[�t���[���ŕ\������
    //_dbgDrawLine(
    //    static_cast<int>(line.p.x ),
    //    static_cast<int>(line.p.y ),
    //    static_cast<int>(line.end.x ),
    //    static_cast<int>(line.end.y ),
    //    0xff0000
    //);

    auto checkCross = [](Vec vec1, Vec& vec2)
    {
        return (vec1.x*vec2.y)-(vec2.x*vec1.y);
    };
    
    auto veclLine= line.end - line.p ;

    //ray.vec: �n�_����̕����x�N�g��
   auto crossRayLine= checkCross(ray.vec, veclLine);
   if (crossRayLine == 0.0)
   {
       //�O�ς̌��ʂ��O�̏ꍇ���t�͐�Ό������Ȃ��̂ł͂���
       return false;
   }

   Vec v =  line.p- ray.p;
  
   auto cross_vRay  = checkCross(v, ray.vec);
   auto cross_vLine = checkCross(v, veclLine);

  auto t1 = cross_vRay / crossRayLine;
  auto t2 = cross_vLine / crossRayLine;

  if (t1 > 0.0 && t1 <= 1.0 && t2 > 0.0 && t2 <= 1.0)
  {
      return true;
  }

    return false;
}

bool Raycast::CheckRectangle(Collision collision, Vec pos)
{
    if (collision.first.y < pos.y && collision.first.x<pos.x &&
        collision.second.y>pos.y && collision.second.x > pos.x)
    {
        return true;
    }
    return false;
}

bool Raycast::RectToRectCollision(Vec pMin, Vec pMax, Vec iMin, Vec iMax)
{
    if (RightSide(pMax, iMin) && LeftSide(iMax, pMin) &&
        TopSide(pMax, iMin) && DownSide(iMax, pMin))
    {
        return true;
    }
    return false;
}
bool Raycast::TopSide(Vec Max, Vec Min)
{
    return (Max.y <= Min.y);
}

bool Raycast::DownSide(Vec Max, Vec Min)
{
    return (Max.y <= Min.y);
}

bool Raycast::LeftSide(Vec Max, Vec Min)
{
    return (Min.x <= Max.x);
}

bool Raycast::RightSide(Vec Max, Vec Min)
{
    return (Min.x <= Max.x);
}
