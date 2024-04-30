#pragma once
#include "Scene.h"
#include<memory>
#include<vector>
#include"../Object/Camera/OutSide.h"
#include"../Object/Camera/Camera.h"
#include"../Object/Stage/Stage.h"
#include"../Player/Player.h"
#include"../Input/Input.h"
#include"../Object/Stage/CheckPoint.h"
#include"../Object/Shader/PostEfffect.h"
#include"../Player/PlayerManager.h"

class TimeCount;

class GameScene :
    public Scene
{
public:

    enum class PLAYER_NUM
    {
        P_1,
        P_2,
        P_3,
        P_4
    };

    GameScene(SceneMng& manager, int n, Transitor& transit);
    ~GameScene();

    virtual void Update(Input& input) override;
    virtual void Draw() override;
private:

    //��Ԑ擪�̃v���C���[�ɒǏ]������
    //�Q�[���V�[���Ő擪�����߂āA�J�����N���X�ɓn��
    void DecideOnTheBeginning();

    std::shared_ptr<Player> player_;
    std::vector<std::shared_ptr<Player>> players_;
    std::unique_ptr<Stage> stage_;
    std::unique_ptr<Camera> camera_;
    std::unique_ptr<OutSide> outSide_;
    std::unique_ptr<CheckPoint> checkPoint_;
    std::unique_ptr<PlayerManager>playerManager_;
    std::unique_ptr<TimeCount>timeCount_;

    void (GameScene::* _update)(Input& input,float elapsedTime);
    void MultiPlayUpdate(Input& input, float elapsedTime);
    void SinglePlayUpdate(Input& input, float elapsedTime);

    PLAYER_NUM old_LeadNum_;//1�t���[���O�̍őO��̃v���C���[
    PLAYER_NUM new_LeadNum_;//�ŐV�̍őO��̃v���C���[
    PLAYER_NUM last_Num_;//�Ō���̃v���C���[

    std::vector<float> distance_;
    std::vector< std::pair<int, float>> testDistance_;//first�̓p�b�h�i���o�[:second��distance
    std::pair<int, float> iD_;
    int playerNum_;

    float startTime_;
    int GoImg_;
    int ReadyImg_;
    int sound_[4];
    int selectImg_[2];

    int num_;

};
