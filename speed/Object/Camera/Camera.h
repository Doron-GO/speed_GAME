#pragma once
#include<memory>
#include<Dxlib.h>
#include<vector>
#include"../../Common/Vector2D.h"

class Player;

static constexpr float MAXFRAME =60.0f;

class Camera
{

public:

	Camera();
	~Camera();
	void Update();

	//�J�����̏�Ԃ�ς���
	void StateChanging(int num);
	//�Ǐ]�ΏەύX����
	bool ReConnect(std::weak_ptr<Player> actor);

	//�J�������W
	const Vector2DFloat& GetPos(void)const;

	//�Ǐ]�Ώۍ��W
	const Vector2DFloat& GetTargetPos(void)const;

private:

	//�Ǐ]�ΏەύX�̎���
	float switchTime_ ;

	//�Ǐ]�Ώ�
	std::weak_ptr<Player> target_;

	//���t���[���̃J�������W
	Vector2DFloat cameraPos_;

	//�O�t���[���̃J�������W
	Vector2DFloat oldPos_;

	void (Camera::* _state)();

	//�Ǐ]�ΏەύX��
	void Switching();

	//�J�����Ǐ]���
	void Follow();

};

