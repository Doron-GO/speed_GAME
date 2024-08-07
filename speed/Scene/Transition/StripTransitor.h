#pragma once
#include "Transitor.h"
class StripTransitor :
    public Transitor
{
private:
	int width_ = 100;
public:
	StripTransitor(int width = 100, int interval = 60);
	virtual void Update() override;
	virtual void Draw() override;
};

