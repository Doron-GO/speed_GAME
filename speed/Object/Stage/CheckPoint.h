#pragma once
#include"../../Common/Vector2D.h"
#include"../../Common/Collision.h"
#include"../../Common/Raycast.h"
#include<vector>
#include<memory>
#include<list>

class Player;
using vec =Vector2DFloat;
using CHECKPOINT= std::pair<bool, vec>;
using CHECKPOINTS= std::vector < std::pair<bool, Vector2DFloat>>;

constexpr int CHECKPOINT_MAX =6;

class CheckPoint
{
public:

	CheckPoint(std::vector<std::shared_ptr<Player>> players, PointColList checkpoint);
	~CheckPoint();

	void Update();
	void Draw(Vector2DFloat pos);
	Vector2DFloat GetCheckPoint()const; 
	CHECKPOINT GetCheckPoint2()const;
	const bool IsGoal();
	void SetSingleMode();

	void SinglePlay();
	void MultiPlay();
private:

	void (CheckPoint::* _work)();
	std::vector<std::shared_ptr<Player>> players_;

	std::vector<Vector2DFloat> checkPoints_;

	CHECKPOINTS checkPoints3_;

	//
	Raycast rayCast_;

	//チェックポイント当たり判定リスト
	PointColList checkPointColList_;

	//次に向かうチェックポイントナンバー
	int currentCheckPoint_;

	//プレイヤーがゴールしたかどうか
	int goalFlag_;

};

