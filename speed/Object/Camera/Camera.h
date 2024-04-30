#pragma once
#include<memory>
#include<Dxlib.h>
#include<vector>
#include"../../Vector2D.h"

class Player;

static constexpr float MAXFRAME =60.0f;

class Camera
{
public:

	Camera();
	~Camera();
	void Init(const Vector2D& worldSize);
	void Update();

	//�J�����̏�Ԃ�ς���
	void PhaseChanging(int num);

	bool ReConnect(std::weak_ptr<Player> actor);
	const Vector2DFloat& GetPos(void)const;
	const Vector2DFloat& GetTargetPos(void)const;
private:

	float time = 0;

	int nextNum_=0;
	void (Camera::* _phase)();
	//�Ǐ]�ΏەύX��
	void Switching();
	//�J�����Ǐ]���
	void Follow();
	//�Y�[��
	void Zoom();

	std::weak_ptr<Player> target_;
	Vector2DFloat cameraPos_;
	Vector2DFloat oldPos_;
	RECT moveArea_;

};

