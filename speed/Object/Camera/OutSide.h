#pragma once
#include"../../Vector2D.h"
#include"../../Common/Collision.h"
#include<vector>
#include<list>
#include<memory>

class Camera;
class DangerZoneSmaller;
class Player;


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



	
	OutSide(Camera& camera, int playerCount);
	~OutSide();
	void (OutSide::* _phase)();

	void Update(std::vector< std::shared_ptr<Player >> players);
	void PhaseChanging();

	//�J�����Ǐ]���
	void Follow();
	void Switching();
	void Draw(Vector2DFloat offset);

	//��ʊO���ǂ����𔻒�
	void IsDead(std::vector< std::shared_ptr<Player >> players);
	bool IsOutSide(Vector2DFloat pos);
	void SinglePlay();
	//��ʂ���͂ݏo�������A�㉺����o���̂����E����o���̂�
	//true:�㉺�@false: ���E
	void UpDownORLeftRight(Vector2DFloat pos);
	void UpORDown(Vector2DFloat pos);
	void LeftOrRight(Vector2DFloat pos);
	void TestSmaller(); 
	const int NumberOfSurvivors();
	bool conclusion_;

	void SideChange(Vector2DFloat& pos,SIDE side_);


private:
	SIDE upperSide_;
	SIDE lowerSide_;
	SIDE upperOldSide_;
	SIDE lowerOldSide_;

	Camera& camera_;

	std::unique_ptr<DangerZoneSmaller> dangerZone_;
	const std::vector<std::shared_ptr<Player>> players_;
	Vector2DFloat minPos_;
	Vector2DFloat maxPos_;

	Vector2DFloat minScale_;
	Vector2DFloat maxScale_;

	Vector2DFloat outsidePos_;//���J�����Ǐ]�Ώ�
	Vector2DFloat outsideOldPos_;//

	Vector2DFloat upperPos_;
	Vector2DFloat upperVec_;

	Vector2DFloat lowerPos_;
	Vector2DFloat lowerVec_;
	std::list<Bomb> upBombs_;
	std::list<Bomb> downBombs_;

	bool isExploding_ = false;
	bool bigExploding_ = false;
	bool singlePlayFlag_ = false;

	int ExplosionSound_;
	int padNum_;
	int bombImg_[11];
	int bigBombImg_[8];
	int frame_;
	int bigFrame_;

	int playerCount_;
	float time = 0;

};

