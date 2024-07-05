#pragma once
#include<memory>
#include<vector>
#include<algorithm>
#include"../../Common/Vector2D.h"
#include"../../Common/Collision.h"
#include"../../Input/Input.h"

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

	//���̃`�F�b�N�|�C���g�Ɉ�ԋ߂��v���C���[����������(�wb�����v���C���[)
	void SearchFirstPlayer(std::pair< bool,Vector2DFloat> checkPoint );

	//���g�����ԋ߂��v���C���[���������邵�A���̏���z��Ɋi�[����
	void SearchHormingPlayer();

	//�o�g���̏��s�����肷��
	void BattleConclusion();

	//�V���O�����[�h�p�̃S�[������
	void SetGoalSingleMode();

	//�A�C�e���Ƃ̓����蔻����v���C���[�̔���
	void CollisionItem();

	//�P�t���[���O�̐擪�v���C���[�ԍ��̎擾
	const PLAYER_NUM GetOldFirstPlayerNum();

	//���t���[���̐擪�v���C���[�ԍ��̎擾
	const PLAYER_NUM GetNewFirstPlayerNum();

	//�擪�v���C���[�ԍ��̍X�V
	void UpdateFirstPlayerNum();

	//��`���m�̏Փ˔���
	bool IsRectCollision(Vec pMin, Vec pMax, Vec iMin, Vec iMax);

	//��`���m�̏Փ˔���
	bool IsCollisionTopSide(Vec Max,Vec Min);
	bool IsCollisionDownSide(Vec Max,Vec Min);
	bool IsCollisionLeftSide(Vec Max,Vec Min);
	bool IsCollisionRightSide(Vec Max,Vec Min);

	//�V���O���v���C���[�h�ɂ���
	void SetSinglePlayMode();

private:

	//�v���C���[�z��
	Players players_;

	//�`�F�b�N�|�C���g�ƃv���C���[�Ԃ̋���
	std::vector< std::pair<int, float>> checkPointToPlayerDistance_;//first�̓p�b�h�i���o�[:second��distance

	//1�t���[���O�̐擪�v���C���[�ԍ�
	PLAYER_NUM oldFirstPlayerNum_;
	//���t���[���̐擪�v���C���[�ԍ�
	PLAYER_NUM newFirstPlayerNum_;

	//�v���C���[���Ō�̈�l�ɂȂ������ǂ����̔���(OutSide�N���X�Ŕ���)
	bool &conclusion_;

	//��������̉摜
	int winImg_;

	//�Đ�̉摜
	int restertImg_;

	//���������v���C���[�̔ԍ�
	int winner_;
	//�V���O���v���C���̃S�[���ɓ��B�������ǂ����̔���
	bool goalFlag_;

	//�v���C���[�̐������Ɉ����œn��
	Blocks& blocks_;

	//�V���O���v���C���[�h���ǂ����𔻒肷��
	bool singlePlay_;

};

