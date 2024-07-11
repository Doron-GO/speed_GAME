#include<DxLib.h>
#include<string>
#include"../../_debug/_DebugDispOut.h"
#include"../../_debug/_DebugConOut.h"
#include"../../Manager/ImageMng.h"
#include"../../Config.h"
#include"Player.h"
#include"Wire.h"


#pragma region MyRegion

const std::string PATH_SOUND_EXPLOSION_ = PATH_SOUND +"Explosion.mp3";
const std::string PATH_SOUND_LAUNCHER = PATH_SOUND+"Launcher.mp3";
const std::string PATH_IMG_EXPLOSION = PATH_IMG + "BigExplosion.png";
const std::string PATH_IMG_ITEM_MISSILE = PATH_IMG + "Missile.png";

#pragma endregion

Player::Player(int playerNum, Blocks& blocks):padNum_(playerNum),  blocks_(blocks)
{
	damageCount_ = 0;
	missileImg_=0;
	expCount_=0;
	slideY_ = -35.0f;

	aliveFlag_= true;
	winFlag_ = false;
	AnchoringFlag_ = false;
	doubleJump_ = true;
	winFlag_ = false;

	//������
	explosionSounds_.emplace(EXP_SOUND_TYPE::EXPLOSION,LoadSoundMem(PATH_SOUND_EXPLOSION_.c_str()));
	explosionSounds_.emplace(EXP_SOUND_TYPE::LAUNCHER, LoadSoundMem(PATH_SOUND_LAUNCHER.c_str()));

	LoadDivGraph(PATH_IMG_EXPLOSION.c_str(), 8, 8, 1, 32, 32, explosionImg_);
	missileImg_ = LoadGraph(PATH_IMG_ITEM_MISSILE.c_str());

	item_ = std::make_shared<ItemBase>();

	moveVec_ = { 0.0f,0.0f};
	movePow_ = { 0.0f,0.0f};
	up_ = { 0.0f,-50.0f };

	itemList_ = ItemList::NON;
	dir_LR_ = DIR_LR::RIGHT;

	_state = &Player::MoveState;
	_damage = &Player::Nothing;

}

Player::~Player()
{
	for (int num =0 ;num < EXPLOSION_IMG_NUM;num++)
	{
		DeleteGraph(explosionImg_[num]);
	}
	DeleteGraph(missileImg_);

}

void Player::Init(ColList colList, ColList wallColList, ColList wireColList)
{
	pos_ = { START_PLAYER_POSITION.x-padNum_*-20.0f,START_PLAYER_POSITION.y };
	grndColList_ = colList;
	wallcolList_ = wallColList;

	 char num = '0'+padNum_;
	 std::string act = "Src/Img/actList/act";//string����������
	 act += num;						 //	�������A��
	 act +=".list";					 //	�������A��
	AnimeMng::GetInstance().LoadAnime(act.c_str());
	std::string objID = "Player";
	objID += num;
	animeStr_.objID_ = objID.c_str();
	AnimeMng::GetInstance().SetAnime(animeStr_, "Idle");
	wire_ = std::make_unique<Wire>(*this,wireColList);

}

void Player::Update(Input& input)
{
	input_.Update(padNum_);
	if (!aliveFlag_)
	{
		return;
	}

	(this->*_damage)();
	(this->*_state)(input_);
	BlocksCollision();

	//�_���[�W���[�V�������ł͂Ȃ����������Ă��Ȃ�������
	if (_damage == &Player::Nothing && !IsWinner())
	{
		Move(input_);	
		Anchoring(input_);
		wire_->Update();
		ItemUse();	
	}

	ItemUpdate();
	if (!IsSwingState())
	{
		pos_.y += movePow_.y;
		//�ǂɓ������Ă����牡�ړ������Ȃ�
		if (_damage == &Player::Nothing &&(CollisionVec({moveVec_.x ,0.0f})||CollisionVec(diagonallyVec_)) )
		{
			pos_.x += movePow_.x;
		}
	}
	AnimeMng::GetInstance().UpdateAnime(animeStr_);

}

void Player::Draw(Vector2DFloat cameraPos)
{
	auto pos = pos_ + cameraPos;
	if (winFlag_)
	{
		if (expCount_ <= 34)
		{
			int cnt = expCount_ / 4;
			if (cnt >= EXPLOSION_IMG_NUM )
			{
				cnt = EXPLOSION_IMG_NUM - 1;
			}
			DrawRotaGraph2F(pos.x, pos.y ,
				15.f, 16.0f,
				10.0, 0.0,
				explosionImg_[cnt], true);
			expCount_++;
		}
	}
	if (aliveFlag_)
	{
		//���������̃L�����N�^�[�`��
		DrawRotaGraph2F(pos.x, pos.y+0.3f,
			24.0f, 35.0f,
			1.5, 0.0,
			ImageMng::GetInstsnce().GetID(animeStr_.imgKey_)[(*animeStr_.animID_)[GraphHD]],
			true, static_cast<int>(dir_LR_), 0);
		ItemDraw(cameraPos);
	}
		
	switch (itemList_)
	{
	case Player::ItemList::NON:
		now_Item_ = "NON";
		break;
	case Player::ItemList::MISSILE:
		DrawRotaGraph2F(pos.x-13.0f, pos.y-40.0f,
			4.0f, 10.0f,
			1.5, 0.0,missileImg_, true);
		now_Item_ = "MISSILS";
		break;
	case Player::ItemList::LASER:
		now_Item_ = "LASER";
		break;
	}
	wire_->Draw(cameraPos);

}

const Vector2DFloat& Player::GetPos()
{
	return pos_;
}

const Vector2DFloat Player::GetDiagonallyVecVec()
{
	return diagonallyVec_;
}

const Vector2DFloat Player::GetMoveVec()
{
	return moveVec_;
}

void Player::StartSwingJump()
{
	_state = &Player::SwingJumpState;
}


void Player::MoveState(Input& input)
{
	//���������Ȃ�������t�H�[���ɂ���
	if (CollisionDown())
	{
		_state = &Player::FallState;
	}
	else
	{
		pos_.y = landingPos_.y;
	}
	Jump(input);
}

void Player::Nothing()
{
}

void Player::DamageMissile()
{
	if ((damageCount_++<30.0f) && (CollisionVec(up_)))
	{		
		if (damageCount_<8.0f)
		{
			movePow_.y -= 0.3f;
		}
	}
	else 
	{	//���̈ړ���0�ɂ��ăt�H�[�����Ă�
		_state = &Player::FallState;
		_damage = &Player::Nothing;
		damageCount_ = 0;
	}

}

void Player::JumpState(Input& input)
{

	AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");

	//�W�����v���x���ő�ɒB�����������́A�����Ԃ�����
	 if(!(CollisionVec(up_)))
	{
		//���̈ړ���0�ɂ��ăt�H�[�����Ă�
		movePow_.y = 0.0f;
		_state = &Player::FallState;
	}

	 if((movePow_.y<-5.0f))
	{
		//���̈ړ���0�ɂ��ăt�H�[�����Ă�
		//movePow_.y = 0.0f;
		_state = &Player::FallState;
	}
	//�łȂ����y�̈ړ��ʂ����Z����
	else
	{
		//movePow_.y += -0.2f;
		movePow_.y += -1.0f;
	}
}

void Player::ItemUpdate(void)
{
	if (!(itemList_ == ItemList::NON))
	{
		item_->Update();
	}

}

void Player::FallState(Input& input)
{		
	Jump(input);
	if (CollisionVec({ 0.0f,movePow_.y+0.1f }))
	{
		movePow_.y += 0.2f;
	}
	else
	{
		movePow_.y = 0.0f;
		pos_.y = landingPos_.y;
		doubleJump_ = true;
		_state = &Player::MoveState;
	}

	if (movePow_.y > 12.0f)
	{
		movePow_.y = 12.0f;
	}
	if (!CollisionVec(up_))
	{
		movePow_.y = 0.2f;
	}
	//CollisionDown
	//�������x�����𒴂����猈�܂����l�ɂ���
	AnimeMng::GetInstance().SetAnime(animeStr_, "Fall");
}

void Player::DamageState(Input& input)
{

}

void Player::WallGrabState(Input& input)
{
	diagonallyVec_ = { moveVec_.x,slideY_ };
	Jump(input);	
	Vector2DFloat movecec = { 0.0f,movePow_.y };

	//�n�ʂɑ���������ʏ�ړ��t�F�[�Y�Ɉڍs
	if ( !CollisionVec(movecec))
	{
		pos_.y = landingPos_.y;
		movePow_.y = 0.0f;
		_state = &Player::MoveState;
	}
	else
	{
		AnimeMng::GetInstance().SetAnime(animeStr_, "WallSlide");
		//�ǂɂԂ������������ǂ����
		if (movePow_.y <= 4.0f)
		{
			movePow_.y += 0.1f;
		}
	}
	//�ǂɂ������Ă��Ȃ�������t�H�[����ԂɈڍs����
	if (!(_state == &Player::WallJumpState))
	{
		if (!IsWall())
		{
			moveVec_ = -(moveVec_);
			_state = &Player::FallState;
		}
	}
	//�ǂ��܂蒆�ɓ���ł����炻��ȏ�͏オ��Ȃ�
	if (!CollisionVec(up_))
	{
		movePow_.y = 0.0f;
	}
	//�����n�ʂɑ���������
}

void Player::WallJumpState(Input& input)
{
	AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
	diagonallyVec_ = { moveVec_.x,slideY_ };
	Vector2DFloat movevec = { 0.0f,-40.0f };
	//�W�����v���x���ő�ɒB�����������́A�n�ʂɐڒn������
	if (movePow_.y <= -5.0f)
	{

		_state = &Player::FallState;
	}
	if (!(CollisionVec(movevec)))
	{
		_state = &Player::FallState;
	}
	//�łȂ����y�̈ړ��ʂ����Z����
	else
	{
		movePow_.y += -0.5f;
		movePow_.x = (moveVec_.x / 2.0f);
	}
	if (IsWall())
	{
		movePow_.x = 0.0f;
		_state = &Player::WallGrabState;
	}
}

void Player::SwingState(Input& input)
{
	Vector2DFloat movevec = { 0.0f,1.0f };
	if (!CollisionVec(movevec))
	{
		pos_.y = landingPos_.y;
		movePow_.y = 0.0f;
		_state = &Player::MoveState;
		wire_->ChangeStandby();
		wire_->EndSwing();
	}

	//�ǂɓ�������������x���O�ɂ��� 1:�����̑O�� 2:��΂ߑO 
	diagonallyVec_ = { moveVec_.x,slideY_ };
	Vector2DFloat tt = { movePow_.x,0.0f };
	if (!ColWallGrab(tt) || !ColWallGrab(diagonallyVec_))
	{
		movePow_.y =0.0f;
		movePow_.x = 0.0f;
		_state = &Player::WallGrabState;
		wire_->ChangeStandby();
	}
	if (!CollisionVec(diagonallyVec_))
	{
		movePow_.x = 0.0f;
		movePow_.y= 0.0f;
		_state = &Player::FallState;
		wire_->ChangeStandby();
	}

	Vector2DFloat up = { 0.0f,-60.0f };
	//�n�ʂ������͓V��ɓ���������X�C���O����߂�
	if (!CollisionVec(up))
	{
		wire_->ChangeStandby();
		_state = &Player::MoveState;
		movePow_.y = 0.0f;
	}
	if (CollisionDown())
	{
		if (_state == &Player::SwingState)
		{	
			if (input.IsPrassed("hook"))
			{
				AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
				movePow_.y = 0.0f;
				wire_->Pump();
			}
			else
			{
				wire_->SwingJump();
				StartSwingJump();
			}
		}
	}
}

void Player::SwingJumpState(Input& input)
{
	Jump(input);
	AnimeMng::GetInstance().SetAnime(animeStr_, "Fall");
	//�������x�����𒴂����猈�܂����l�ɂ���
	if (movePow_.y >= 14.0f)
	{
		movePow_.y = 14.0f;
	}	
	if (movePow_.x >0.1f&&movePow_.x >= 7.5f)
	{
		movePow_.x = 7.5f;
	}
	else if (movePow_.x <-0.1f&&movePow_.x <= -7.5f)
	{
		movePow_.x = -7.5f;
	}
	Vector2DFloat movecec = { 0.0f,movePow_.y+0.1f };
	Vector2DFloat up = { 0.0f,-50.0f };
	//���Ɠ������Ă��Ȃ�������
	if (!CollisionVec(up))
	{
		movePow_.y = 0.0f;
		doubleJump_ = true;
		wire_->ChangeStandby();
		_state = &Player::MoveState;
	}
	else if (!CollisionVec(movecec))
	{
		pos_.y = landingPos_.y;
		movePow_.y = 0.0f;
		doubleJump_ = true;
		wire_->ChangeStandby();
		_state = &Player::MoveState;
	}
	else
	{
		movePow_.y += 0.2f;
	}
}


void Player::WinnerState(Input& input)
{
	AnimeMng::GetInstance().SetAnime(animeStr_, "Win");
}

void Player::WinnerFallState(Input& input)
{
	if (!CollisionVec(up_))
	{
		movePow_.y = 0.0f;
	}
	if (CollisionVec({ 0.0f,movePow_.y + 0.1f }))
	{
		movePow_.y += 0.1f;
		AnimeMng::GetInstance().SetAnime(animeStr_, "Fall");
	}
	else
	{
		movePow_ = { 0.0f,0.0f };
		pos_.y = landingPos_.y;
		doubleJump_ = true;
		_state = &Player::WinnerState;
		PlaySoundMem(explosionSounds_[EXP_SOUND_TYPE::EXPLOSION], DX_PLAYTYPE_BACK, true);
		winFlag_ = true;
	}
}

void Player::Conclusion()
{
	if (_state == &Player::MoveState)
	{
		movePow_ = { 0.0f,0.0f };
		_state = &Player::WinnerState;
		PlaySoundMem(explosionSounds_[EXP_SOUND_TYPE::EXPLOSION], DX_PLAYTYPE_BACK, true);
		winFlag_ = true;
	}
	else
	{
		_state = &Player::WinnerFallState;
	}
}

void Player::MoveColision()
{
	diagonallyVec_ = { moveVec_.x,slideY_ };
	//�ǂ��܂��Ԃ̔���
	if (!(_state == &Player::MoveState) && !(_state == &Player::WallGrabState))
	{
		if (IsWall() && CollisionDown())
		{
			//������Ԃł͂Ȃ��Ȃ�
			if (!(_state == &Player::FallState))
			{
				movePow_.y = -abs(movePow_.x / 1.5f);
			}
			movePow_.x = 0.0f;
			_state = &Player::WallGrabState;
		}
	}
	//�ǂɓ�������������x���O�ɂ��� 1:�����̑O�� 2:��΂ߑO 
	diagonallyVec_ = { moveVec_.x,slideY_ };
	if ( !CollisionVec(diagonallyVec_)||!CollisionVec(moveVec_,{0.0f,-16.0f}) )
	//if (!CollisionVec(diagonallyVec_))
	{
		movePow_.x = 0.0f;
	}
	//�w������ǂɓ���������
	Vector2DFloat backVec = { -(moveVec_.x / 2.0f),-16.0f };
	Vector2DFloat backDiagonallyVec_ = { backVec.x,slideY_ };//�w������̎΂߃o�[�W����
	if (!CollisionVec(backVec))
	{
		movePow_.x = -(backVec.x / 11.0f);
	}
	if (!CollisionVec(backDiagonallyVec_))
	{
		movePow_.x = -(backVec.x / 11.0f);
	}
	//�ǃW�����v�̂ł���ǂƔw�����Ƃ̓����蔻��
	if (!ColWallGrab(backVec))
	{
		movePow_.x = -(backVec.x / 11.0f);
	}
	if (!ColWallGrab(backVec))
	{
		movePow_.x = -(backVec.x / 11.0f);
	}
}

bool Player::IsWinner(void)
{
	return ((_state == &Player::WinnerState) || (_state == &Player::WinnerFallState));
}

bool Player::IsSwingState(void)
{
	return (_state == &Player::SwingState);
}

bool Player::CollisionDown()
{
	Vector2DFloat rayCenter = { pos_.x,pos_.y-10.0f};
	Vector2DFloat moveVec = { 0.0f,10.0f };
	for (const auto& col : grndColList_)
	{
		Raycast::Ray ray = { rayCenter,moveVec};
		if (rayCast_.CheckCollision(ray, col,pos_))
		{
			//TRACE("��������\n");
			Landing(col.first.y);
			return false;
		}
	}
	return true;
}

bool Player::CollisionVec(Vector2DFloat movevec)
{
	//���ۂ̓����蔻�背�C�̕`��
	//_dbgDrawLine(
	//	rayCenter.x, rayCenter.y,
	//	rayCenter.x + movevec.x, rayCenter.y + movevec.y,
	//	0x00ff00
	//);
	for (const auto& col : grndColList_)
	{
		Raycast::Ray ray = { pos_,movevec };
		if (rayCast_.CheckCollision(ray, col, pos_ ))
		{
			Landing(col.first.y);
			return false;
		}
	}
	return true;
}

bool Player::CollisionVec(Vector2DFloat movevec, Vector2DFloat center)
{
	Vector2DFloat center_{ pos_ + center };
	for (const auto& col : grndColList_)
	{
		Raycast::Ray ray = { center_,movevec };
		if (rayCast_.CheckCollision(ray, col, center_))
		{
			Landing(col.first.y);
			return false;
		}
	}
	return true;
}

bool Player::ColWallGrab(Vector2DFloat movevec, float y)
{
	float wallX=0.0f;
	Vector2DFloat rayCenter = { pos_.x, pos_.y - y };
	for (const auto& col : wallcolList_)
	{
		Raycast::Ray ray = { rayCenter,movevec };
		if (rayCast_.CheckCollision(ray, col, pos_))
		{		
			return false;
		}
	}	
	return true;
}

bool Player::IsWall()
{
	return (!ColWallGrab(moveVec_,16.0f) );
}

void Player::BlocksCollision()
{
	for (auto& block:blocks_.GetBlockList())
	{
		if (!block.blockFlag_)
		{
			continue;
		}
		if (rayCast_.RectToRectCollision(colRect_.min_, colRect_.max_,
			block.col_.first, block.col_.second))
		{
			block.blockFlag_ = false;
			movePow_.x= 0.0f;
			movePow_.y /= 4.0f;
		}
		
	}

}

void Player::Landing(float y)
{
	landingPos_.y = y;
}

void Player::Dead()
{
	pos_ = { 0.0f,0.0f };
	aliveFlag_ = false;
}

bool Player::IsAlive()
{
	return aliveFlag_;
}

Player:: ItemList Player::IsItem()
{
	return itemList_;
}

void Player::SetItemList(int itemNum)
{
	itemList_ = (ItemList)itemNum;
}

void Player::SetItem(std::shared_ptr <ItemBase> item)
{
	item_ = item;
}

void Player::ItemDraw(Vector2DFloat cameraPos)
{
	if (item_->IsActivate()|| item_->IsExplosion())
	{
		item_->Draw(cameraPos);
	}
}

void Player::SetTarget(Vector2DFloat targetPos)
{
	targetPos_ = targetPos;
}

const std::shared_ptr<ItemBase> Player::GetItem()
{
	return item_;
}

void Player::Damage(ItemBase::ITEM_TYPE type)
{
	switch (type)
	{
	case ItemBase::ITEM_TYPE::MISSILE:
		_damage = &Player::DamageMissile;
		_state = &Player::DamageState;
		movePow_.x = 0.0f;
		AnimeMng::GetInstance().SetAnime(animeStr_, "Dmage");
		break;
	case ItemBase::ITEM_TYPE::LASER:
		_damage = &Player::DamageMissile;
		AnimeMng::GetInstance().SetAnime(animeStr_, "Dmage");
		break;
	}
	PlaySoundMem(explosionSounds_[EXP_SOUND_TYPE::LAUNCHER], DX_PLAYTYPE_BACK, true);
}

const bool Player::IsWin()
{
	return winFlag_;
}

void Player::Move(Input& input)
{
	float speed = 0.2f;
	//�E�Ƃ͍��L�[��������Ă��Ȃ��Ƃ�
	if (!input.IsPrassed("right")&&!input.IsPrassed("left"))
	{
		if (_state == &Player::MoveState)
		{
			//�ړ��ʂ�0.1���傫��������
			if (movePow_.x >= 0.1f)
			{
				movePow_.x -= speed;
			}
			//�ړ��ʂ�-0.1��菬����������
			if (movePow_.x <= -0.1f)
			{
				movePow_.x += speed;
			}
			if (dir_LR_ == DIR_LR::RIGHT)
			{
				if (0.40f >= movePow_.x && movePow_.x >= 0.02f)
				{
					movePow_.x = 0.0f;
				}
			}
			if (dir_LR_ == DIR_LR::LEFT)
			{
				if (-0.40f <= movePow_.x && movePow_.x <= -0.02f)
				{
					movePow_.x = 0.0f;
				}
			}
		}
		//�W�����v�A�j���[�V����������Ȃ�������
		if (_state == &Player::MoveState) { AnimeMng::GetInstance().SetAnime(animeStr_, "Idle"); }
	}
	else 
	{
		//�W�����v�A�j���[�V����������Ȃ�������
		if (_state == &Player::MoveState) { AnimeMng::GetInstance().SetAnime(animeStr_, "Run");}
	}

	//�X���C�f�B���O�{�_����������Ă��Ȃ���
	if (!input.IsPrassed("c"))
	{		

		if (!(_state == &Player::WallJumpState)&& !(_state == &Player::SwingState))
		{
			//�E�L�[
			if (input.IsPrassed("right"))
			{
				dir_LR_ = DIR_LR::RIGHT;
				movePow_.x += 0.2f;
				moveVec_ = { 20.0f,15.0f };
			}
			//���L�[
			if (input.IsPrassed("left"))
			{
				dir_LR_ = DIR_LR::LEFT;
				movePow_.x -= 0.2f;
				moveVec_ = { -20.0f,-15.0f };
			}
		}
		colRect_.min_ = { pos_.x - 10.0f,pos_.y };
		colRect_.max_ = { pos_.x + 15.0f,pos_.y - 40.0f };

		if(_state == &Player::SwingJumpState)
		{
			//�ړ����x�����𒴂���ƍő呬�x�ɌŒ肷��
			if (movePow_.x <= -12.0f) { movePow_.x = -12.0f;}
			else if (movePow_.x >= 12.0f) { movePow_.x = 12.0f;}
		}
		else
		{
			//�ړ����x�����𒴂���ƍő呬�x�ɌŒ肷��
			if (movePow_.x <= -8.0f) { movePow_.x = -8.0f; }
			else if (movePow_.x >= 8.0f) { movePow_.x = 8.0f; }
		}

	}
	//�ǂɓ���������̂ǂ̏������܂Ƃ߂Ă���
	MoveColision();
	//����������Ȃ��Ƃ�
	if (!(_state == &Player::FallState)&&!(_state == &Player::JumpState) &&
		!(_state == &Player::SwingJumpState))
	{
		//�X���C�f�B���O�{�^����������Ă�����
		if (input.IsPrassed("c"))
		{
			colRect_.min_ = { pos_.x - 10.0f,pos_.y };
			colRect_.max_ = { pos_.x + 15.0f,pos_.y-20.0f };
			AnimeMng::GetInstance().SetAnime(animeStr_, "Slide");
			//�X���C�f�B���O���͌�������
			if (movePow_.x > 0.0f) 
			{
				movePow_.x -= 0.1f;
			}
			if (movePow_.x < 0.0f) 
			{
				movePow_.x += 0.1f;
			}			
			slideY_ = -13.0f;

		}
		else{ slideY_ = -35.0f; }
	}
}

void Player::ItemUse()
{
	//�A�C�e���������Ă�����
	if (!(itemList_ == ItemList::NON))
	{
		if (item_->IsEnd())
		{
			itemList_ = ItemList::NON;
		}
		if (input_.IsTriggerd("item") && !item_->IsActivate())
		{
			item_->Activate(Vector2DFloat{ pos_.x,pos_.y - ITEM_OFFSET });
		}
		item_->SetPos(Vector2DFloat{ targetPos_.x,targetPos_.y - ITEM_OFFSET });
	}
}

void Player::Anchoring(Input& input)
{
	if (!(_state == &Player::MoveState))
	{
		if (input.IsTriggerd("hook"))
		{
			slideY_ = -35.0f;
			if (CollisionDown() && CollisionVec(moveVec_) && CollisionVec(diagonallyVec_))
			{
				if (!(_state == &Player::SwingState) && !(_state == &Player::WallGrabState))
				{
					AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
					wire_->SetAnchorPalam();
					AnchoringFlag_ = true;
				}
			}
		}
	}
	//�X�C���O�X�e�[�g�ł͂Ȃ��Ƃ��ɁA�{�^���������ꑱ���Ă����烏�C���[��L�΂�
	if (!(_state == &Player::SwingState)&&AnchoringFlag_)
	{
		if (input.IsPrassed("hook"))
		{
			AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
		}
		else
		{
			AnchoringFlag_ = false;
			wire_->ChangeStandby();
		}
	}
	
}

void Player::StartSwing()
{
	_state = &Player::SwingState;
	AnchoringFlag_ = false;
}

void Player::Jump(Input& input)
{
	//��L�[���������Ƃ�
	if (input.IsTriggerd("jump"))
	{
		//�ǂ����ԂȂ�ǃW�����v
		if ((_state == &Player::WallGrabState))
		{		
			movePow_.y = 0.0f;
			AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");

			moveVec_ = (-moveVec_);
			if (moveVec_.x > 0.0f)
			{
				dir_LR_ = DIR_LR::RIGHT;
			}
			else
			{
				dir_LR_ = DIR_LR::LEFT;
			}
			movePow_.x = 0.0f;
			_state = &Player::WallJumpState;
		}
		else if(!(_state == &Player::FallState))//�Ⴄ�Ȃ�ʏ�W�����v
		{
			AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
			movePow_.y = 0.0f;
			_state = &Player::JumpState;
		}
		if (((_state == &Player::FallState)|| (_state == &Player::SwingJumpState))&&doubleJump_)
		{
			AnimeMng::GetInstance().SetAnime(animeStr_, "Jump");
			movePow_.y = 0.2f;
			doubleJump_ = false;
			_state = &Player::JumpState;
		}
	}
}

