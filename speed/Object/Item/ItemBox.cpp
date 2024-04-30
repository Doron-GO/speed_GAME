#include<DxLib.h>
#include "ItemBox.h"
#include"../Stage/LoadMap.h"
#include"../Manager/ImageMng.h"
#include"../../Player/Player.h"

ItemBox::ItemBox(LoadMap& loadMap,std::vector<std::shared_ptr<Player>> players)
	:loadMap_(loadMap),players_(players),count_(0)
{
	LoadDivGraph("Src/Img/nebula.png", 61, 8, 8, 100, 100, itemBoxImg_);
}

ItemBox::~ItemBox()
{
}

void ItemBox::Draw(Vector2DFloat offset)
{
	auto& worldArea = loadMap_.GetWorldArea();
	const auto& tileSize = loadMap_.GetTileSize();
	auto& mapData = loadMap_.GetMapData();
	for (const auto& col : loadMap_.itemBoxGetColList())
	{
		DrawRotaGraph2F((col.first.x+16.0f ) + offset.x, (col.first.y-16.0f)+ offset.y,
			50.0f, 50.0f, 0.5f, 0.0f, itemBoxImg_[(count_ / 2) % 61], true);
	}
	count_++;
}

void ItemBox::Update()
{	
	for (const auto& player :players_)
	{
		for (const auto& col : loadMap_.itemBoxGetColList())
		{
			//if (rayCast_.CheckCollision(col, player->pos_))
			if (rayCast_.RectToRectCollision(player->col_.min_, player->col_.max_,col.first, col.second ))
			{
				if (player->IsItem() == Player::ItemList::NON)
				{
					if (player->TestItem())
					{
						player->SetItemList(1);	
						auto ii = std::make_shared<Missile>();
						ii->grndColList_ = loadMap_.GetColList();
						player->SetItem(ii);
					}
					else
					{
						player->SetItemList(2);
						auto ii = std::make_shared<Laser>();
						player->SetItem(ii);
					}
				}
			}
		}
	}

}

bool ItemBox::IsBox(Vector2DFloat pos)
{
	return false;
}
