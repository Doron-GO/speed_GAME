#pragma once
#include<list>
#include<vector>
#include "../Common/Vector2D.h"

using Collision = std::pair<Vector2DFloat, Vector2DFloat>;//二点の場所
using ColList = std::list<Collision>;
using PointColList = std::vector<Collision>;


