#include <DxLib.h>
#include "Stage.h"
#include"../../Manager/ImageMng.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Item/ItemBox.h"
#include"Blocks.h"

Stage::Stage() 
{	
	loadMap_.LoadTSX("Src/Json/stageTSX_.json");
	loadMap_.LoadStage("Src/Json/stage_2.json");
	blocks_ = std::make_unique<Blocks>(loadMap_);

}

Stage::~Stage()
{
}

void Stage::Init(std::vector<std::shared_ptr<Player>> players) 
{
	itemBox_ = std::make_unique<ItemBox>(loadMap_, players);
	backImg_ = LoadGraph("Src/Img/Stageimage/siro.png");
}

void Stage::Update()
{
	itemBox_->Update();
	blocks_->Update();
}

void Stage::Draw(Vector2DFloat cameraPos)
{	
	DrawRotaGraph2F(0 + cameraPos.x, 0 + cameraPos.y,
		0.0f, 0.0f,
		10.0, 0.0,backImg_, 0);

	const Vector2D &worldArea = loadMap_.GetWorldArea();
	const Vector2D&tileSize = loadMap_.GetTileSize();
	const MapData & mapData = loadMap_.GetMapData();
	int X = static_cast<int> (tileSize.x );
	int Y = static_cast<int> (tileSize.y );
	int cameraX = static_cast<int> (cameraPos.x);
	int cameraY = static_cast<int> ( cameraPos.y);
	for (const auto& layer : loadMap_.GetMapData()) 
	{
		for (int y = 0; y < worldArea.y; y++)
		{
			for (int x = 0; x < worldArea.x; x++)
			{
				if (x + y * worldArea.x < layer.second.size())
				{
					auto gid = layer.second[x + y * worldArea.x];
					if (gid >= 0&& !(gid==5)&&!(gid == 6))
					{
						DrawGraph(x *X + cameraX, y *Y+ cameraY,
							ImageMng::GetInstsnce().GetID(loadMap_.GetMapKey())
							[gid], true);
					}
				}
			}
		}
	}

	itemBox_->Draw(cameraPos);
	blocks_->Draw(cameraPos);
}

const  Vector2D& Stage::GetWorldArea()
{
	return loadMap_.GetWorldArea();
}

const  Vector2D& Stage::GetTileSize()
{
	return loadMap_.GetTileSize();
}

const  std::string& Stage::GetMapKey()
{
	return loadMap_.GetMapKey();
}

const ColList& Stage::GetColList(void)
{
	return loadMap_.GetColList();
}

const ColList& Stage::GetWallColList(void)
{
	return loadMap_.WallGetColList();
}

const ColList& Stage::GetWireColList(void)
{
	return loadMap_.WireGetColList();
}

const PointColList& Stage::CheckPointGetColList(void)
{
	return loadMap_.CheckPointGetColList();
}

const std::unique_ptr<Blocks> & Stage::GetBlocks()
{
	return blocks_;
}
