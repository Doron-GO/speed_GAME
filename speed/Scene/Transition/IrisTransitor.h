#pragma once
#include "Transitor.h"

class IrisTransitor :
    public Transitor
{
public:
	IrisTransitor(bool irisOut = false, int interval = 60, bool isTiled = false, int gHandle = -1);
	~IrisTransitor();
	virtual void Update() override;
	virtual void Draw() override;

private:
	int handleForMaskScreen_;//�}�X�N�]���p�O���t�B�b�N�n���h��
	int maskH_;//�}�X�N�n���h��
	float diagonalLength_;//�Ίp���̒���
	bool irisOut_ = false;//�A�C���X�A�E�g�t���O(false�Ȃ�A�C���X�C��)
	bool isTiled_;
	int gHandle_;
};

