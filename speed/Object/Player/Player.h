#pragma once
#include<map>
#include<string>
#include"../../Object/Camera/Camera.h"
#include"../../Object/Item/ItemBase.h"
#include"../../Object/Item/Missile.h"
#include"../../Object/Stage/Blocks.h"
#include"../../Common/Collision.h"
#include"../../Common/Vector2D.h"
#include"../../Manager/AnimMng.h"
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

	//��`�����蔻����
	struct COL_RECT
	{
		Vector2DFloat min_;
		Vector2DFloat max_;
	};

	Player(int playerNum, Blocks& blocks);
	~Player();

	//������
	void Init(ColList colList, ColList wallColList, ColList wireColList);

	//�X�V
	void Update(Input& input);

	//����ɃI�t�Z�b�g�l��n���`������炷�悤�ɂ���
	void Draw(Vector2DFloat cameraPos);

	//���ɃM�~�b�N�̂Ȃ������蔻�胊�X�g
	ColList grndColList_;

	//�ǃW�����v���ł��铖���蔻�胊�X�g
	ColList wallcolList_;

	//�v���C���[���W���擾����
	const Vector2DFloat& GetPos();

	//�v���C���[�̑�������΂ߏ�ɏo��x�N�g��
	const Vector2DFloat GetDiagonallyVecVec();

	//�v���C���[�̈ړ�����
	const Vector2DFloat GetMoveVec();

	//�v���C���[�̍��W
	Vector2DFloat pos_;

	//�ړ���
	Vector2DFloat movePow_;	

	//���������Ԗڂ�PAD���g���Ă��邩
	int padNum_;

	//�L�����N�^�[�̌���
	DIR_LR dir_LR_;

	//��`���
	COL_RECT colRect_;

	//���ݎ����Ă���A�C�e��
	ItemList IsItem();

	//SwingJump��ԂɕύX
	void StartSwingJump();

	//Swing��ԂɕύX����
	void StartSwing();

	//�v���C���[�����S��Ԃɂ���
	void Dead();

	//�v���C���[��������Ԃ�����
	bool IsAlive();

	void SetItemList(int itemNum);

	//�A�C�e����������Ԃɂ���
	void SetItem(std::shared_ptr <ItemBase> item);

	//�A�C�e���̕`��
	void ItemDraw(Vector2DFloat cameraPos);

	//�v���C���[�Ɉ�ԋ߂����v���C���[���W��ݒ肷��
	void SetTarget(Vector2DFloat targetPos);
	
	//������ԂɈڍs������
	void Conclusion();

	//�v���C���[�̏������Ă���A�C�e���̏����擾����
	const std::shared_ptr<ItemBase> GetItem();

	//�v���C���[���_���[�W���炢��Ԃɂ���
	void Damage(ItemBase::ITEM_TYPE type);

	//������Ԃ��ǂ�����Ԃ�
	const bool IsWin();

private:

	//�v���C���[�̏����ʒu
	 const Vector2DFloat START_PLAYER_POSITION {400.0f, 2720.0f };

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
	bool winFlag_ ;

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


	//�X�e�[�g�Ǘ������o�֐��|�C���^
	void (Player::* _state)(Input& input);

	//�A�C�e���̍X�V
	void ItemUpdate(void);

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
	void WallGrabState(Input& input);
	//�ǃW�����v
	void WallJumpState(Input& input);
	//�X�C���O���
	void SwingState(Input& input);
	//�X�C���O�W�����v���
	void SwingJumpState(Input& input);	
	//�������(�n��)
	void WinnerState(Input& input);
	//�������(��)
	void WinnerFallState(Input& input);
	
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

