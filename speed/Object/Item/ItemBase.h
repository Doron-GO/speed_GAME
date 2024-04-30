#pragma once
#include"../../Vector2D.h"
#include"../../Common/Collision.h"
#include"../../Common/Raycast.h"

class ItemBase
{
public:

	enum class ITEM_TYPE
	{
		MISSILE,
		LASER
	};

	 ItemBase();
	 virtual ~ItemBase();

	virtual void Update();
	virtual void Draw(Vector2DFloat offset);
	virtual void SetPos(Vector2DFloat pos);
	virtual void Activate(Vector2DFloat playerpos);
	virtual bool IsEnd();
	virtual void End();
	virtual bool IsActivate();
	virtual bool IsExplosion();
	const Vector2DFloat GetPos();

	struct COL
	{
		Vector2DFloat min_;
		Vector2DFloat max_;

	};
	COL col_;
	ITEM_TYPE type_;
	ColList grndColList_;//���ɃM�~�b�N�̂Ȃ������蔻��

protected:
	Vector2DFloat itemPos_;
	Vector2DFloat targetPos_;
	bool activateFlag_;
	bool explosionFlag_;
	int img_[11];
	int drawCount_;
	int count_;

	Raycast raycast_;
};

