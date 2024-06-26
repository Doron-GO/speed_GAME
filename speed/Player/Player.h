#pragma once
#include<map>
#include<string>
#include"../Vector2D.h"
#include"../Object/Manager/AnimMng.h"
#include"../Common/Collision.h"
#include"../Common/Raycast.h"
#include"../Input/Input.h"
#include"../Object/Camera/Camera.h"
#include"../Object/Item/ItemManager.h"
#include"../Object/Item/ItemBase.h"
#include"../Object/Item/Missile.h"
#include"../Object/Stage/Blocks.h"


class Wire;
class Blocks;


class Player
{
public:
	enum class ItemList
	{
		NON,
		MISSILE,
		LASER
	};

	enum class DIR_LR
	{
		RIGHT,
		LEFT
	};
	enum class PHASE
	{
		FALL,
		JUMP,
		MOVE,
		WALLGRAB,
		WALLJUMP,
		SWING,
		SWINGJUMP
	};

	struct COL
	{
		Vector2DFloat min_;
		Vector2DFloat max_;

	};

	Player(int playerNum, Blocks& blocks);
	~Player();
	void Init(ColList colList, ColList wallColList, ColList wireColList);
	void Update(Input& input);

	//これにオフセット値を渡し描画をずらすようにする
	void Draw(Vector2DFloat cameraPos);

	ColList grndColList_;//特にギミックのない当たり判定
	ColList wallcolList_;//壁ジャンプができる当たり判定

	const Vector2DFloat GetPos();
	const Vector2DFloat GetDiagonallyVecVec();
	const Vector2DFloat GetMoveVec();
	const Vector2DFloat GetMovePow();
	Vector2DFloat pos_;//キャラの座標
	Vector2DFloat movePow_;	//移動する力
	int padNum_;//自分が何番目のPADを使っているか
	DIR_LR dir_LR_;//キャラクターの向き

	//SwingJump状態に変更
	void StartSwingJump();
	//Swing状態に変更
	void StartSwing();
	void Dead();
	void Alive();
	bool IsAlive();
	ItemList IsItem();
	void SetItemList(int itemNum);
	void SetItem(std::shared_ptr <ItemBase> item);

	void TesItemDraw(Vector2DFloat cameraPos);
	void SetTarget(Vector2DFloat targetPos);
	void Conclusion();

	bool TestItem();
	const std::shared_ptr<ItemBase> GetItem();
	void Damage(ItemBase::ITEM_TYPE type);
	const bool IsWin();
	COL col_;
private:

	PHASE phase_;
	std::string now_;
	std::string now_Item_;

	void DebugPhaseCheck();//自分が今何フェーズ中なのか確認デバッグ用

	void (Player::* _phase)(Input& input);

	//プレイヤーの状態
	void MovePhase(Input& input);//左右移動：ジャンプ
	void JumpPhese(Input& input);//ジャンプ
	void FallPhase(Input& input);//落下中
	void DamagePhase(Input& input);//落下中
	void WallGrabPhese(Input& input);//壁ずり落ち
	void WallJumpPhese(Input& input);//壁ジャンプ
	void SwingPhese(Input& input);//スイング状態
	void SwingJumpPhese(Input& input);//スイングジャンプ状態
	void WinnerPhese(Input& input);//勝者状態
	void WinnerFallPhese(Input& input);//勝者状態



	void (Player::* _damage)();
	//プレイヤーダメージ
	void Nothing();
	void DamageMissile();


	//当たり判定系
	void MoveColision();
	//自分の中心から true 当たってない:false 当たってる
	bool CollisionDown();
	//足元から　true 当たってない:false 当たってる
	bool CollisionVec(Vector2DFloat movevec);
	bool CollisionVec(Vector2DFloat movevec, Vector2DFloat center);
	bool ColWallGrab(Vector2DFloat movevec, float y DEFAULTPARAM(= 0.0f));
	bool IsWall();
	void BlocksCollision();
	void Landing(float y);

	//プレイヤーのアクション
	void Move(Input& input);	//左右移動
	void ItemUse();
	void Anchoring(Input& input);//フックを飛ばす:進行方向の斜め上
	void Jump(Input& input);

	AnimStr animeStr_;
	Input input_;
	Raycast rayCast_;

	Vector2DFloat cameraPos_;//カメラの座標
	Vector2DFloat moveVec_;	//向いている方向
	Vector2DFloat diagonallyVec_;//向いている方向の斜め上
	Vector2DFloat up_;	//向いている方向

	std::unique_ptr<Wire> wire_;

	bool AnchoringFlag_;
	bool aliveFlag_;
	bool testItemFlag = true;
	bool doubleJump_;
	bool winFlag_ = false;
	int explosionImg_[8];
	int expCount_;
	int missileImg_;

	float slideY_ = -35.0f;
	Vector2DFloat targetPos_;
	Vector2DFloat landingPos_;
	Blocks& blocks_;
	int ExplosionSound_[2];
	std::shared_ptr<ItemBase>item_;
	ItemList itemList_;
	float damageCount_;

	const  Vector2DFloat START_PLAYER_POSITION {400.0f, 2720.0f };
	const int MAX_MISSILE_DAMEGE = 30;
};

