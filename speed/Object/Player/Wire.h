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

	//�t�F�[�Y��EndSwingState�ɂ��āAplayer_.EndSwing();
	void StartSwingJump(); 
	void StartSwing(); //�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
	void EndSwing();//�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
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
	VECTOR fulcrum_pos;//�v�Z�p
	float angle_;
	VECTOR vel_;
	float v_; //�傫��
	
	Vector2DFloat moveVec_;
	VECTOR Scale_;
	//����
	float length_;
	//��
	float pow_;

	void SwingState();
	void StandbyState();
	void EndSwingState();
	void AnchoringState();

};

