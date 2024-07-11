#pragma once
#include<memory>
#include"LoadMap.h"
#include"../../Common/Vector2D.h"

class ItemBox;
class Player;
class Blocks;

class Stage
{
public:

	struct Line {
		Vector2DFloat p; //�n�_
		Vector2DFloat end;//�I�_

	};

	Stage();
	~Stage();
	void Init(std::vector<std::shared_ptr<Player>> players);
	void Update();
	void Draw(Vector2DFloat cameraPos);

	const  Vector2D& GetWorldArea()const;
	const  Vector2D& GetTileSize()const;
	const std::string& GetMapKey()const;
	const ColList& GetColList(void)const;
	const ColList& GetWallColList(void)const;
	const ColList& GetWireColList(void)const;
	const PointColList& CheckPointGetColList(void)const;
	const  std::unique_ptr<Blocks> &GetBlocks();
private:

	LoadMap loadMap_;
	std::unique_ptr<ItemBox> itemBox_;
	std::unique_ptr<Blocks> blocks_;
	int backImg_;

};

