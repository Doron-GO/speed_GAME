#pragma once
#include<list>
#include<vector>
#include "../Vector2D.h"


using Collision = std::pair<Vector2DFloat, Vector2DFloat>;//��_�̏ꏊ
using ColList = std::list<Collision>;
using PointColList = std::vector<Collision>;


