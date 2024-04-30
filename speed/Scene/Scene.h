#pragma once
#include"../Vector2D.h"
class Input;
class SceneMng;
class Transitor;
/// <summary>
/// �V�[���̋K��N���X(����1�N���X
/// </summary>

class Scene
{
public:
	Scene(SceneMng& scene,int n ,Transitor& transit);
	virtual ~Scene() {};
	virtual void Update(Input& input) = 0;
	virtual void Draw() ;
protected:
	SceneMng& sceneManager_;
	Transitor& sceneTransitor_;
	int screenID_;
	Vector2DFloat drawOffset_;
	Vector2DFloat screenSize_={1600.0f,1000.0f};
};

