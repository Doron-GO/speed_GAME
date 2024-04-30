#include <math.h>
#include <DxLib.h>

#include "IrisTransitor.h"

IrisTransitor::IrisTransitor(bool irisOut, int interval, bool isTiled, int gHandle) 
	:Transitor(interval),irisOut_(irisOut),isTiled_(isTiled),gHandle_(gHandle)
{
	//�E�B���h�E�T�C�Y
	VECTOR screenSize = { 1600,1000 };

	//�}�X�N���C���[�̍쐬
	handleForMaskScreen_ = MakeScreen(screenSize.x, screenSize.y, true);
	maskH_ = CreateMaskScreen();

	//�E�B���h�E�̑Ίp���̒���
	diagonalLength_ = hypotf(screenSize.x, screenSize.y) / 2.0f;
}

IrisTransitor::~IrisTransitor()
{
	DeleteMaskScreen();
}

void IrisTransitor::Update()
{
	if (frame_ < interval_) {
		//++frame_;
		frame_+=2;
		SetDrawScreen(newRT_);
	}
	else if (frame_ == interval_) {
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

void IrisTransitor::Draw()
{
	if (IsEnd()) {
		return;
	}

	auto rate = (float)frame_ / (float)interval_;
	int backRT = oldRT_;
	int maskedRT = newRT_;
	if (irisOut_) {
		backRT = newRT_;
		maskedRT = oldRT_;
		rate = 1.0f - rate;
	}
	//
	float radius = (diagonalLength_)*rate;
	SetDrawScreen(handleForMaskScreen_);
	ClearDrawScreen();

	VECTOR pos = { 1024 / 2,768 / 2 };
	DrawCircleAA(pos.x, pos.y, radius, 32, 0xffffff, true);

	//�B���֐�(���݂̃O���t�B�b�N�n���h�����}�X�N�X�N���[���ɓ]��)
	SetMaskScreenGraph(handleForMaskScreen_);
	//�`��̈�𔽓]����
	SetMaskReverseEffectFlag(true);

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseMaskScreenFlag(false);
	DrawGraph(0, 0, backRT, true);
	SetUseMaskScreenFlag(true);
	DrawGraph(0, 0, maskedRT, true);
	SetUseMaskScreenFlag(false);
}