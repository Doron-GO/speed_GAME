#include "PlayerManager.h"
#include "Player.h"
#include"../Object/Item/ItemBase.h"
#include"../Object/Stage/Blocks.h"

PlayerManager::PlayerManager(bool& conclusion, Blocks& blocks):conclusion_(conclusion),
new_LeadNum_(PLAYER_NUM::P_1), old_LeadNum_(PLAYER_NUM::P_1), last_Num_(PLAYER_NUM::P_1), winner_(0), count_(0), blocks_(blocks)
{
	winImg_=LoadGraph("Src/Img/UIimage/WIN.png");
	restertImg_ =LoadGraph("Src/Img/UIimage/RESTERT.png");
}

PlayerManager::~PlayerManager()
{
}


void PlayerManager::Init(int playerNum, ColList gruound, ColList Wall, ColList wire)
{
	for (int Num = 1; Num <= playerNum; Num++)
	{	
		std::shared_ptr<Player> player;
		player = std::make_shared<Player>(Num, blocks_);
		player->Init(gruound, Wall, wire);
		players_.push_back(player);
	}
	goalFlag_ = false;
}

void PlayerManager::Update(Input& input)
{
	if (!singlePlay_)
	{
		HormingTargrt();
	}
	ItemCol(); 
	Conclusion();
	for (const auto& player : players_)
	{
		if (player->IsAlive())
		{
			player->Update(input);
		}
	}
	
}

void PlayerManager::Draw(Vector2DFloat cameraPos)
{
	for (const auto& player : players_)
	{
		if (player->IsAlive())
		{
			player->Draw(cameraPos);
		}
	}
	if (conclusion_)
	{
		DrawRotaGraph2F(800.0f, 300.0f, 200.0f, 20.0f, 2.0, 0.0, winImg_,true);
		//DrawRotaGraph2F(800.0f, 760.0f, 208.0f, 20.0f, 2.0, 0.0, restertImg_,true);
	}
}

const Vector2DFloat& PlayerManager::GetPlayerPos(int playerNum)
{
	return players_[playerNum]->pos_;
}

const Players PlayerManager::GetPlayers()
{
	return players_;
}

void PlayerManager::DecideOnTheBeginning2(std::pair<bool, Vector2DFloat>checkPoint)
{
	leadDistance_.clear();
	//�v���C���[�ƃ`�F�b�N�|�C���g�Ƃ̋������i�[���Ă���B
	for (auto& p : players_)
	{
		iD_.first = (p->padNum_) - 1;
		Vector2DFloat checkPointPos= {0.0f, 0.0f};
		if (checkPoint.first)
		{
			checkPointPos = { players_[(p->padNum_) - 1]->GetPos().x,checkPoint.second.y };
		}
		else
		{
			checkPointPos = {checkPoint.second.x, players_[(p->padNum_) - 1]->GetPos().y}; 
		}
		iD_.second = players_[(p->padNum_) - 1]->GetPos().distance(checkPointPos);
		leadDistance_.push_back(iD_);
	}
	for (auto& p1 : players_)
	{
		for (auto& p2 : players_)
		{
			if (p1->IsAlive() && p2->IsAlive())
			{
				auto num1 = (p1->padNum_) - 1;
				auto num2 = (p2->padNum_) - 1;
				//�v���C���[N���v���C���[N+1���O��������A�v���C���[N��擪�ɂ���B 
				if (leadDistance_[num1].second < leadDistance_[num2].second)
				{
					if (leadDistance_[num1].second < leadDistance_[(int)new_LeadNum_].second)
					{
						new_LeadNum_ = static_cast<PLAYER_NUM>(leadDistance_[num1].first);
					}
				}
				else
				{//�Ō���̃v���C���[���E�����Ă�����Ƃ肠�����ʂ̃v���C���[���Ō�������ɂ���
					if (!(players_[(int)last_Num_]->IsAlive()))
					{
						last_Num_ = static_cast<PLAYER_NUM>(leadDistance_[num1].first);
					}
					//�O�Ō���̃v���C���[����낾������
					if (leadDistance_[(int)last_Num_].second <
						leadDistance_[num1].second)
					{
						last_Num_ = static_cast<PLAYER_NUM>(leadDistance_[num1].first);
					}
				}
			}
		}
	}

}

void PlayerManager::HormingTargrt()
{
	for (auto& player1 : players_)
	{
		if (!player1->IsAlive())
		{
			leadDistance_.clear();
			continue;
		}
		for (auto& player2 : players_)
		{
			if (player1->padNum_ == player2->padNum_) { continue; }
			iD_.second = (player2->padNum_) - 1;
			iD_.first = players_[(player1->padNum_) - 1]->GetPos().distance(player2->GetPos());
			TTleadDistance_.push_back(iD_);
		}
		auto pp = std::min_element(TTleadDistance_.begin(), TTleadDistance_.end());
		player1->SetTarget(players_[pp->second]->GetPos());
		TTleadDistance_.clear();
	}	 
}

void PlayerManager::Conclusion()
{
	if (conclusion_|| goalFlag_)
	{
		for (auto& player : players_)
		{
			if (player->IsAlive())
			{
				winner_ = player->padNum_;
			}
			else
			{
				continue;
			}
		}
		if (!players_[winner_ - 1]->IsWin())
		{
			players_[winner_-1]->Conclusion();
		}
	}
}

void PlayerManager::Goal()
{
	goalFlag_ = true;
}


void PlayerManager::ItemCol()
{
	for (auto& player1 :players_)
	{
		if (!(player1->GetItem()->IsActivate())) { continue; }
		for (auto& player2 : players_)
		{
			if (player1->padNum_ == player2->padNum_) { continue; }
			auto item = player1->GetItem();
			auto iCol = item->col_;
			auto pCol = player2->col_;
			if (IsItemCollision(pCol.min_, pCol.max_, iCol.min_, iCol.max_))
			{
				item->End();
				player2->Damage(item->type_);
 			}
		}
	}
}

const PlayerManager:: PLAYER_NUM PlayerManager::GetOldLeadNum()
{
	return old_LeadNum_;
}

const PlayerManager:: PLAYER_NUM PlayerManager::GetNewLeadNum()
{
	return new_LeadNum_;
}

const PlayerManager:: PLAYER_NUM PlayerManager::GetLastLeadNum()
{
	return last_Num_;
}

void PlayerManager::SetOld()
{
	old_LeadNum_ = new_LeadNum_;
}

bool PlayerManager::IsItemCollision(Vec pMin, Vec pMax, Vec iMin, Vec iMax)
{
	if (RightSide(pMax, iMin)&& LeftSide(iMax, pMin)&&
		TopSide(pMax, iMin)&& DownSide(iMax, pMin))
	{	
		return true;
	}
	return false;
}

bool PlayerManager::TopSide(Vec Max, Vec Min)
{
	return (Max.y<=Min.y);
}

bool PlayerManager::DownSide(Vec Max, Vec Min)
{
	return (Max.y <= Min.y);
}

bool PlayerManager::LeftSide(Vec Max, Vec Min)
{
	return (Min.x <= Max.x);
}
 
bool PlayerManager::RightSide(Vec Max, Vec Min)
{
	return (Min.x <= Max.x);
}

void PlayerManager::SinglePlay()
{
	singlePlay_ = true;
}

