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

	//����ɃI�t�Z�b�g�l��n���`������炷�悤�ɂ���
	void Draw(Vector2DFloat cameraPos);

	ColList grndColList_;//���ɃM�~�b�N�̂Ȃ������蔻��
	ColList wallcolList_;//�ǃW�����v���ł��铖���蔻��

	const Vector2DFloat GetPos();
	const Vector2DFloat GetDiagonallyVecVec();
	const Vector2DFloat GetMoveVec();
	const Vector2DFloat GetMovePow();
	Vector2DFloat pos_;//�L�����̍��W
	Vector2DFloat movePow_;	//�ړ������
	int padNum_;//���������Ԗڂ�PAD���g���Ă��邩
	DIR_LR dir_LR_;//�L�����N�^�[�̌���

	//SwingJump��ԂɕύX
	void StartSwingJump();
	//Swing��ԂɕύX
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

	void DebugPhaseCheck();//�����������t�F�[�Y���Ȃ̂��m�F�f�o�b�O�p

	void (Player::* _phase)(Input& input);

	//�v���C���[�̏��
	void MovePhase(Input& input);//���E�ړ��F�W�����v
	void JumpPhese(Input& input);//�W�����v
	void FallPhase(Input& input);//������
	void DamagePhase(Input& input);//������
	void WallGrabPhese(Input& input);//�ǂ��藎��
	void WallJumpPhese(Input& input);//�ǃW�����v
	void SwingPhese(Input& input);//�X�C���O���
	void SwingJumpPhese(Input& input);//�X�C���O�W�����v���
	void WinnerPhese(Input& input);//���ҏ��
	void WinnerFallPhese(Input& input);//���ҏ��



	void (Player::* _damage)();
	//�v���C���[�_���[�W
	void Nothing();
	void DamageMissile();


	//�����蔻��n
	void MoveColision();
	//�����̒��S���� true �������ĂȂ�:false �������Ă�
	bool CollisionDown();
	//��������@true �������ĂȂ�:false �������Ă�
	bool CollisionVec(Vector2DFloat movevec);
	bool CollisionVec(Vector2DFloat movevec, Vector2DFloat center);
	bool ColWallGrab(Vector2DFloat movevec, float y DEFAULTPARAM(= 0.0f));
	bool IsWall();
	void BlocksCollision();
	void Landing(float y);

	//�v���C���[�̃A�N�V����
	void Move(Input& input);	//���E�ړ�
	void ItemUse();
	void Anchoring(Input& input);//�t�b�N���΂�:�i�s�����̎΂ߏ�
	void Jump(Input& input);

	AnimStr animeStr_;
	Input input_;
	Raycast rayCast_;

	Vector2DFloat cameraPos_;//�J�����̍��W
	Vector2DFloat moveVec_;	//�����Ă������
	Vector2DFloat diagonallyVec_;//�����Ă�������̎΂ߏ�
	Vector2DFloat up_;	//�����Ă������

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

