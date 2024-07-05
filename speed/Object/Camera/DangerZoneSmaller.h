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
	//死亡エリアの座標の最大値
	Vector2DFloat& outSideMax_;
	//死亡エリアの座標の最小値
	Vector2DFloat& outSideMin_;

};

