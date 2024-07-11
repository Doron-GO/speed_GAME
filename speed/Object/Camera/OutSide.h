#pragma once
#include<vector>
#include<list>
#include<memory>
#include"../../Common/Vector2D.h"
#include"../../Common/Collision.h"


class Camera;
class DangerZoneSmaller;
class Player;

//�㉺���E
enum class SIDE
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


//��ʒ[�̔�������邽�߂̍\����
struct Bomb
{
	Vector2DFloat pos_ = {};
	int frame_ = 0;
	bool isDead = false;
	SIDE side_ ;
	Bomb(const Vector2DFloat& p, SIDE side) :pos_(p),side_(side) {}
};

class OutSide
{

public:


	bool conclusion_;

	OutSide(Camera& camera, int playerCount);
	~OutSide();

	void Update(std::vector< std::shared_ptr<Player >> players);

	//�A�b�v�f�[�g��Ԃ�ύX
	void StateChanging();

	//�J�����Ǐ]���
	void FollowStateUpdate();
	
	//�Ǐ]�ΏەύX���
	void SwitchingStateUpdate();
	
	//�`��
	void Draw(Vector2DFloat offset);

	//��ʊO���ǂ����𔻒�
	void IsDead(std::vector< std::shared_ptr<Player >> players);
	bool IsOutSide(Vector2DFloat pos);

	//�V���O���v���C���[�h�ɕύX
	void SinglePlay();

	//��ʂ���͂ݏo�������A�㉺����o���̂����E����o���̂�
	//true:�㉺�@false: ���E
	void UpDownORLeftRight(Vector2DFloat pos);

	//��ʒ[�ɂ����v���C���[����[�Ȃ̂����[�Ȃ̂��𔻒�
	void UpORDown(Vector2DFloat pos);

	//��ʒ[�ɂ����v���C���[���E�[�Ȃ̂����[�Ȃ̂��𔻒�
	void LeftOrRight(Vector2DFloat pos);

	//const int NumberOfSurvivors();

	//��ʒ[�҂�����ɑ���悤�ɍ��W����ʒ[�ɍ��킹��֐�
	void SideChange(Vector2DFloat& pos,SIDE side_);

private:

	void (OutSide::* _update)();

	//�E���ɑ��锚��������ʒ[�̂ǂ̕ӂɂ���̂�
	SIDE upperSide_;

	//�����ɑ��锚��������ʒ[�̂ǂ̕ӂɂ���̂�
	SIDE lowerSide_;

	//�J�����N���X
	Camera& camera_;

	//���S�͈͂��k��������N���X
	std::unique_ptr<DangerZoneSmaller> dangerZone_;

	//��ʒ[������W
	Vector2DFloat minPos_;
	
	//��ʒ[�E�����W
	Vector2DFloat maxPos_;

	//�l�p�̍���
	const Vector2DFloat OUTSIDE_SCALE = { 800.0f,500.0f };

	//�����摜�̖���
	static constexpr int EXPLOSION_IMG_NUM = 8;

	//�����摜�̖���
	static constexpr int BIG_EXPLOSION_IMG_NUM = 11;

	//���S�G���A�̍��W�̍ő�l(�l�p�̉E��)
	Vector2DFloat outSideMax_;

	//���S�G���A�̍��W�̍ŏ��l(�l�p�̍���)
	Vector2DFloat outSideMin_;

	//���t���[���̃J�����Ǐ]�Ώ�
	Vector2DFloat outsidePos_;

	//�O�t���[���̃J����
	Vector2DFloat outsideOldPos_;

	//��ʏ�𑖂�E���̔����̍��W
	Vector2DFloat upperPos_;

	//�i�ޕ����Ɨ�
	Vector2DFloat upperVec_;

	//��ʒ[���𑖂鍶���̔����̍��W
	Vector2DFloat lowerPos_;

	//�i�ޕ����Ɨ�
	Vector2DFloat lowerVec_;

	//��ʒ[�𑖂锚��(��Ɍ�����)
	std::list<Bomb> upBombs_;

	//��ʒ[�𑖂锚��(���Ɍ�����)
	std::list<Bomb> downBombs_;

	//�����������ǂ���
	bool isExploding_ ;

	//�唚�������ǂ���
	bool bigExploding_ ;

	//���݂̃��[�h���V���O�����[�h���ǂ���
	bool singlePlayFlag_ ;

	//������
	int ExplosionSound_;

	//�U��������R���g���[���̃i���o�[
	int padNum_;

	//�������摜�n���h��
	int bombImg_[EXPLOSION_IMG_NUM];
	
	//�唚���摜�n���h��
	int bigBombImg_[BIG_EXPLOSION_IMG_NUM];

	//���������J�E���g
	int count_;

	//�����摜�J�E���g
	int expCount_  ;

	//�唚���J�E���g
	int bigExpCount_;

	//�v���C���[�l���J�E���g�p
	int playerCount_;
	
	//�ǔ��Ώۂ�ύX����
	float switchingTime_ ;

	//��ʒ[�𑖂�悤�ɔ����ꏊ��ς��Ă���
	void MoveChainExplosion(void);
	
	//�����摜�̕\�����I������炻����폜����
	void ClearExplosion(void);

	//�������摜�\��
	void ExplosionDraw(void);
	
	//�唚���摜�\��
	void BigExplosionDraw(void);

	//��ʒ[�̍��g�̕\��
	void OutSideDraw(void);
};

