#pragma once
#include"../Vector2D.h"
#include"../Common/Raycast.h"
#include "../Common/Time.h"

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

	//�t�F�[�Y��EndSwingPhase�ɂ��āAplayer_.EndSwing();
	void StartSwingJump(); 
	void StartSwing(); //�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
	void EndSwing();//�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
	void Pump();
	bool IsHitHook();
	void SwingJump();
	void ChangeStandby();

private:

	void (Wire::* _phase)();

	void SwingPhase();
	void StandbyPhase();
	void EndSwingPhase();
	void AnchoringPhase();


	ColList col;
	Time timeManager_;

	Player&  player_;
	Raycast rayCast_;

	Vector2DFloat fulcrum_;
	VECTOR fulcrum_pos;//�v�Z�p
	float angle_;
	VECTOR vel_;
	float v_;
	
	Vector2DFloat moveVec_;
	Vector2DFloat gravity_;
	Vector2DFloat yNorm_;			//�����琎�̐��K���ςݐ����x�N�g��
	
	VECTOR Scale_;

	float gMag_;			//�d�͂̑傫��
	float theta_;			//�p�x
	float omega_;			//�p���x
	float length_;			//����
	float pow_;

};

