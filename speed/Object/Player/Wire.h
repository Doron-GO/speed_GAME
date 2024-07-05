#pragma once
#include"../../Common/Vector2D.h"
#include"../../Common/Raycast.h"
#include "../../Common/Time.h"

class Player;

class Wire
{
public:

	Wire(Player& player,ColList& list);
	~Wire();

	void Update();
	void Draw(Vector2DFloat cameraPos);

	void SetSwingPalam();
	void SetAnchorPalam();

	//フェーズをEndSwingStateにして、player_.EndSwing();
	void StartSwingJump(); 
	void StartSwing(); //スイングフェーズに切り替える関数
	void EndSwing();//スイングフェーズに切り替える関数
	void Pump();
	bool IsHitHook();
	void SwingJump();
	void ChangeStandby();

private:

	void (Wire::* _state)();
	ColList col;
	Time timeManager_;

	Player&  player_;
	Raycast rayCast_;

	Vector2DFloat fulcrum_;
	VECTOR fulcrum_pos;//計算用
	float angle_;
	VECTOR vel_;
	float v_; //大きさ
	
	Vector2DFloat moveVec_;
	VECTOR Scale_;
	//長さ
	float length_;
	//力
	float pow_;

	void SwingState();
	void StandbyState();
	void EndSwingState();
	void AnchoringState();

};

