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

	//�X�E�B���O���n�܂�O�ɃX�E�B���O�ɕK�v�ȃp�����[�^��ݒ肷��
	void SetSwingPalam();
	
	//�i�s�����̎΂ߏ�Ƀt�b�N��L�΂�
	void SetAnchorPalam();

	//�t�F�[�Y��EndSwingState�ɂ��āAplayer_.EndSwing();
	void StartSwingJump(); 

	//�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
	void StartSwing(); 

	//�X�C���O�t�F�[�Y�ɐ؂�ւ���֐�
	void EndSwing();

	//�X�C���O�����X�ɉ���������
	void Pump();
	
	//�t�b�N�ƃu���b�N�Ƃ̓����蔻��
	bool IsHitHook();

	//�X�C���O���ɃW�����v
	void SwingJump();

	//�X�C���O�ҋ@��ԃX�e�[�g�ɕύX
	void ChangeStandby();

private:

	void (Wire::* _state)();

	//�t�b�N��t����̂��\�ȃu���b�N�̃��X�g
	ColList col;

	Time timeManager_;

	Player&  player_;

	//�����蔻��
	Raycast rayCast_;

	//�x�_�̍��W
	Vector2DFloat fulcrum_;

	//�x�_�̍��W(�v�Z�p)
	VECTOR fulcrum_pos;

	//�X�C���O���̊p�x
	float angle_;

	//�ړ��������
	VECTOR vel_;

	 //�傫��
	float v_;
	
	Vector2DFloat moveVec_;

	VECTOR Scale_;
	
	//����
	float length_;
	
	//��
	float pow_;

	//�X�C���O���
	void SwingState();

	//�X�C���O�ҋ@���
	void StandbyState();

	//�X�C���O�I�����
	void EndSwingState();

	//���C���[��L�΂��Ă�����
	void AnchoringState();

};

