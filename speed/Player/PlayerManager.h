#pragma once
#include<memory>
#include<vector>
#include<algorithm>
#include"../Vector2D.h"
#include"../Common/Collision.h"
#include"../Input/Input.h"

class Player;
class Blocks;

using Players = std::vector<std::shared_ptr<Player>>;
using Vec = Vector2DFloat;
class PlayerManager
{
public:

	enum class PLAYER_NUM
	{
		P_1,
		P_2,
		P_3,
		P_4
	};

	PlayerManager(bool& conclusion, Blocks& blocks);
	~PlayerManager();

	void Update(Input& input);
	void Init(int playerNum, ColList gruound, ColList Wall, ColList wire);
	void Draw(Vector2DFloat cameraPos);
	const Vector2DFloat& GetPlayerPos(int playerNum);
	const Players GetPlayers();
	//�擪��T����
	void DecideOnTheBeginning2(std::pair<bool,Vector2DFloat>checkPoint);
	void HormingTargrt();
	void Conclusion();
	void Goal();

	//�A�C�e���Ƃ̓����蔻����v���C���[�l���Ԃ�񂷊֐�
	void ItemCol();

	const PLAYER_NUM GetOldLeadNum();
	const PLAYER_NUM GetNewLeadNum();
	const PLAYER_NUM GetLastLeadNum();
	void SetOld();

	//�����蔻�������֐�
	bool IsItemCollision(Vec pMin, Vec pMax, Vec iMin, Vec iMax);
	//�A�C�e���Ƃ̓����蔻��ォ��̏���
	bool TopSide(Vec Max,Vec Min);
	bool DownSide(Vec Max,Vec Min);
	bool LeftSide(Vec Max,Vec Min);
	bool RightSide(Vec Max,Vec Min);

	void SinglePlay();
private:
	Players players_;
	std::vector< std::pair<int, float>> leadDistance_;//first�̓p�b�h�i���o�[:second��distance
	std::vector< std::pair<float, int>> TTleadDistance_;//first�̓p�b�h�i���o�[:second��distance
	std::vector<float> Distance_;
	std::pair<int, float> iD_;

	PLAYER_NUM old_LeadNum_;//1�t���[���O�̍őO��̃v���C���[
	PLAYER_NUM new_LeadNum_;//�ŐV�̍őO��̃v���C���[
	PLAYER_NUM last_Num_;//�Ō���̃v���C���[


	bool &conclusion_;
	int winImg_;
	int restertImg_;
	int winner_;

	bool goalFlag_;
	Blocks& blocks_;
	bool singlePlay_=false;
	int count_;

	//int &playerCounts_;//������
};

