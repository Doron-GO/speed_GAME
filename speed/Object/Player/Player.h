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

	//����ɃI�t�Z�b�g�l��n���`������炷�悤�ɂ���
	void Draw(Vector2DFloat cameraPos);

	ColList grndColList_;//���ɃM�~�b�N�̂Ȃ������蔻��
	ColList wallcolList_;//�ǃW�����v���ł��铖���蔻��

	const Vector2DFloat& GetPos();
	const Vector2DFloat GetDiagonallyVecVec();
	const Vector2DFloat GetMoveVec();
	const Vector2DFloat GetMovePow();
	Vector2DFloat pos_;//�L�����̍��W
	Vector2DFloat movePow_;	//�ړ������
	int padNum_;//���������Ԗڂ�PAD���g���Ă��邩
	DIR_LR dir_LR_;//�L�����N�^�[�̌���

	//SwingJump��ԂɕύX
	void StartSwingJump();
	//Swing��ԂɕύX����
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

	//�����摜�̖���
	static constexpr int EXPLOSION_IMG_NUM = 8;

	//�A�C�e�����W���v���C���[�̐^�񒆂ɒ������邽�߂̒l
	static constexpr float ITEM_OFFSET = 20.0f;

	//�������̍ő吔
	static constexpr int EXPLOSION_SOUND_NUM =2;

	//�������^�C�v
	enum class EXP_SOUND_TYPE
	{
		EXPLOSION = 0,
		LAUNCHER 
	};

	//�������Ǘ��z��
	std::map<EXP_SOUND_TYPE, int> explosionSounds_;

	//���݂̃v���C���[�̏��
	STATE state_;

	//���݂̃X�e�[�g��\�����镶����(�f�o�b�O�p)
	std::string nowState_;

	//���݂̏������Ă���A�C�e����\�����镶����(�f�o�b�O�p)
	std::string now_Item_;

	//�ړ�����
	Vector2DFloat moveVec_;
	
	//�i�s�����̎΂ߏ�Ɍ������x�N�g��(�����蔻��)
	Vector2DFloat diagonallyVec_;

	//�v���C���[�̍��W�����Ɍ������x�N�g��(�����蔻��p)
	Vector2DFloat up_;

	//�X�C���O�Ȃǂ̃A�N�V�������s���N���X
	std::unique_ptr<Wire> wire_;

	//���C���[��L�΂��A�N�V���������s�����ǂ����𔻒�
	bool AnchoringFlag_;

	//�v���C���[���������Ă��邩�ǂ����𔻒�
	bool aliveFlag_;

	//��i�W�����v�\���ǂ�������
	bool doubleJump_;

	//���������҂��ǂ����𔻒�
	bool winFlag_ = false;

	//�����摜
	int explosionImg_[EXPLOSION_IMG_NUM];

	//�����摜�v���p
	int expCount_;

	//�������Ă���A�C�e���\���p�摜(�~�T�C��)
	int missileImg_;

	//�X���C�f�B���O��Ԏ��̃v���C���[�̍���
	float slideY_;

	//���g�����ԋ߂����v���C���[�̍��W
	Vector2DFloat targetPos_;

	//�ڒn���Ă���n�ʂ̍��W
	Vector2DFloat landingPos_;

	//��Q���u���b�N�̏����擾
	Blocks& blocks_;

	//�A�j���[�V�������
	AnimStr animeStr_;

	//�R���g���[������
	Input input_;
	
	//�����蔻��p�N���X
	Raycast rayCast_;

	//�A�C�e���̏��
	std::shared_ptr<ItemBase>item_;

	//���ݏ������Ă���A�C�e���������𔻒�
	ItemList itemList_;

	//�_���[�W��Ԃ̌v���p�ϐ�
	float damageCount_;

	//�v���C���[�̏����ʒu
	 const Vector2DFloat START_PLAYER_POSITION {400.0f, 2720.0f };

	//�����������X�e�[�g���Ȃ̂��m�F(�f�o�b�O�p)
	void DebugStateCheck();

	//�X�e�[�g�Ǘ������o�֐��|�C���^
	void (Player::* _state)(Input& input);

	//�v���C���[�̏��
	//���E�ړ��F�W�����v���
	void MoveState(Input& input);

	//�W�����v���
	void JumpState(Input& input);

	//�������
	void FallState(Input& input);

	//�_���[�W���
	void DamageState(Input& input);

	//�ǂ��藎�����
	void WallGrabPhese(Input& input);

	//�ǃW�����v
	void WallJumpPhese(Input& input);

	//�X�C���O���
	void SwingPhese(Input& input);

	//�X�C���O�W�����v���
	void SwingJumpPhese(Input& input);
	
	//�������(�n��)
	void WinnerPhese(Input& input);
	
	//�������(��)
	void WinnerFallPhese(Input& input);
	
	//������Ԃ���Ȃ����ǂ�������
	bool IsWinner(void);

	//�X�E�B���O��ԂłȂ����ǂ�������
	bool IsSwingState(void);

	void (Player::* _damage)();
	//�v���C���[�_���[�W
	//�_���[�W�H����Ă��Ȃ����
	void Nothing();

	//�_���[�W���(�~�T�C��)
	void DamageMissile();

	//�����蔻��n
	void MoveColision();

	//�����̒��S���� true �������ĂȂ�:false �������Ă�
	bool CollisionDown();

	//��������@true �������ĂȂ�:false �������Ă�
	bool CollisionVec(Vector2DFloat movevec);

	//�v���C���[�̒��S����@true �������ĂȂ�:false �������Ă�
	bool CollisionVec(Vector2DFloat movevec, Vector2DFloat center);

	//���܂�\�̕ǂƂ̓����蔻��
	bool ColWallGrab(Vector2DFloat movevec, float y = 0.0f);

	//���܂�\�̕ǂƓ������Ă��邩�ǂ���
	bool IsWall();

	//��Q���u���b�N�Ƃ̓����蔻��
	void BlocksCollision();

	//�ڒn���Ă���n�ʂ�y���W���擾����
	void Landing(float y);

	//�v���C���[�̃A�N�V����
	//���E�ړ�
	void Move(Input& input);

	//�A�C�e�����g�p����֐�
	void ItemUse();

	//�t�b�N���΂�:�i�s�����̎΂ߏ�
	void Anchoring(Input& input);

	//�W�����v������֐�
	void Jump(Input& input);

};

