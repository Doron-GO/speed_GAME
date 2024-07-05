#pragma once
#include<DxLib.h>

class Transitor
{
protected:

	int sizeX ;
	int sizeY ;

	const int interval_;//�؂�ւ��ɂ����鎞��
	int frame_ = 0;//�J�n���猻�݂܂ł̃t���[����
	int oldRT_ = 0;//�؂�ւ��O�̉��
	int newRT_ = 0;//�؂�ւ���̉��
public:
	Transitor(int interval = 60) : interval_(interval), sizeX(1600), sizeY(1000) {}
	virtual ~Transitor();
	void Start();//���o�J�n
	virtual void Update() = 0;//Scene::Update�̍Ō�ɌĂ�ł�
	virtual void Draw() = 0;//Scene::Draw�̍Ō�ɌĂ�ł�
	virtual bool IsEnd()const;//���o���I������

};

