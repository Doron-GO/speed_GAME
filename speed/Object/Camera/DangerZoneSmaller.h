#pragma once
#include"../../Common/Vector2D.h"

class OutSide;

class DangerZoneSmaller
{

public:

	int count_;

	DangerZoneSmaller(Vector2DFloat& max, Vector2DFloat& min);
	~DangerZoneSmaller();
	void Smaller();
	void UpdateSmaller();
	void Update();
	void UpdateWait();
	void (DangerZoneSmaller::* _update)();
	void Activated();
	void ResetCounter();

private:

	Vector2DFloat scaleMin_;
	Vector2DFloat scaleMax_;
	//���S�G���A�̍��W�̍ő�l
	Vector2DFloat& outSideMax_;
	//���S�G���A�̍��W�̍ŏ��l
	Vector2DFloat& outSideMin_;

};

