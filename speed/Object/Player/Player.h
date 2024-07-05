#pragma once
#include<map>
#include<string>
#include"../../Common/Vector2D.h"
#include"../../Manager/AnimMng.h"
#include"../../Object/Camera/Camera.h"
#include"../../Object/Item/ItemManager.h"
#include"../../Object/Item/ItemBase.h"
#include"../../Object/Item/Missile.h"
#include"../../Object/Stage/Blocks.h"
#include"../../Common/Collision.h"
#include"../../Common/Raycast.h"
#include"../../Input/Input.h"


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
	enum class STATE
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

	const Vector2DFloat& GetPos();
	const Vector2DFloat GetDiagonallyVecVec();
	const Vector2DFloat GetMoveVec();
	const Vector2DFloat GetMovePow();
	Vector2DFloat pos_;//キャラの座標
	Vector2DFloat movePow_;	//移動する力
	int padNum_;//自分が何番目のPADを使っているか
	DIR_LR dir_LR_;//キャラクターの向き

	//SwingJump状態に変更
	void StartSwingJump();
	//Swing状態に変更する
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

	const std::shared_ptr<ItemBase> GetItem();
	void Damage(ItemBase::ITEM_TYPE type);
	const bool IsWin();
	COL col_;
private:

	//爆発画像の枚数
	static constexpr int EXPLOSION_IMG_NUM = 8;

	//アイテム座標をプレイヤーの真ん中に調整するための値
	static constexpr float ITEM_OFFSET = 20.0f;

	//爆発音の最大数
	static constexpr int EXPLOSION_SOUND_NUM =2;

	//爆発音タイプ
	enum class EXP_SOUND_TYPE
	{
		EXPLOSION = 0,
		LAUNCHER 
	};

	//爆発音管理配列
	std::map<EXP_SOUND_TYPE, int> explosionSounds_;

	//現在のプレイヤーの状態
	STATE state_;

	//現在のステートを表示する文字列(デバッグ用)
	std::string nowState_;

	//現在の所持しているアイテムを表示する文字列(デバッグ用)
	std::string now_Item_;

	//移動方向
	Vector2DFloat moveVec_;
	
	//進行方向の斜め上に向いたベクトル(当たり判定)
	Vector2DFloat diagonallyVec_;

	//プレイヤーの座標から上に向いたベクトル(当たり判定用)
	Vector2DFloat up_;

	//スイングなどのアクションを行うクラス
	std::unique_ptr<Wire> wire_;

	//ワイヤーを伸ばすアクションが実行中かどうかを判定
	bool AnchoringFlag_;

	//プレイヤーが生存しているかどうかを判定
	bool aliveFlag_;

	//二段ジャンプ可能かどうか判定
	bool doubleJump_;

	//自分が勝者かどうかを判定
	bool winFlag_ = false;

	//爆発画像
	int explosionImg_[EXPLOSION_IMG_NUM];

	//爆発画像計測用
	int expCount_;

	//所持しているアイテム表示用画像(ミサイル)
	int missileImg_;

	//スライディング状態時のプレイヤーの高さ
	float slideY_;

	//自身から一番近い他プレイヤーの座標
	Vector2DFloat targetPos_;

	//接地している地面の座標
	Vector2DFloat landingPos_;

	//障害物ブロックの情報を取得
	Blocks& blocks_;

	//アニメーション情報
	AnimStr animeStr_;

	//コントローラ入力
	Input input_;
	
	//当たり判定用クラス
	Raycast rayCast_;

	//アイテムの情報
	std::shared_ptr<ItemBase>item_;

	//現在所持しているアイテムが何かを判定
	ItemList itemList_;

	//ダメージ状態の計測用変数
	float damageCount_;

	//プレイヤーの初期位置
	 const Vector2DFloat START_PLAYER_POSITION {400.0f, 2720.0f };

	//自分が今何ステート中なのか確認(デバッグ用)
	void DebugStateCheck();

	//ステート管理メンバ関数ポインタ
	void (Player::* _state)(Input& input);

	//プレイヤーの状態
	//左右移動：ジャンプ状態
	void MoveState(Input& input);

	//ジャンプ状態
	void JumpState(Input& input);

	//落下状態
	void FallState(Input& input);

	//ダメージ状態
	void DamageState(Input& input);

	//壁ずり落ち状態
	void WallGrabPhese(Input& input);

	//壁ジャンプ
	void WallJumpPhese(Input& input);

	//スイング状態
	void SwingPhese(Input& input);

	//スイングジャンプ状態
	void SwingJumpPhese(Input& input);
	
	//勝利状態(地上)
	void WinnerPhese(Input& input);
	
	//勝利状態(空中)
	void WinnerFallPhese(Input& input);
	
	//勝利状態じゃないかどうか判定
	bool IsWinner(void);

	//スウィング状態でないかどうか判定
	bool IsSwingState(void);

	void (Player::* _damage)();
	//プレイヤーダメージ
	//ダメージ食らっていない状態
	void Nothing();

	//ダメージ状態(ミサイル)
	void DamageMissile();

	//当たり判定系
	void MoveColision();

	//自分の中心から true 当たってない:false 当たってる
	bool CollisionDown();

	//足元から　true 当たってない:false 当たってる
	bool CollisionVec(Vector2DFloat movevec);

	//プレイヤーの中心から　true 当たってない:false 当たってる
	bool CollisionVec(Vector2DFloat movevec, Vector2DFloat center);

	//つかまり可能の壁との当たり判定
	bool ColWallGrab(Vector2DFloat movevec, float y = 0.0f);

	//つかまり可能の壁と当たっているかどうか
	bool IsWall();

	//障害物ブロックとの当たり判定
	void BlocksCollision();

	//接地している地面のy座標を取得する
	void Landing(float y);

	//プレイヤーのアクション
	//左右移動
	void Move(Input& input);

	//アイテムを使用する関数
	void ItemUse();

	//フックを飛ばす:進行方向の斜め上
	void Anchoring(Input& input);

	//ジャンプをする関数
	void Jump(Input& input);

};

