#pragma once
#include<memory>
#include<map>
#include<vector>
#include"../Object/Camera/OutSide.h"
#include"../Object/Camera/Camera.h"
#include"../Object/Stage/Stage.h"
#include"../Object/Player/Player.h"
#include"../Object/Stage/CheckPoint.h"
#include"../Object/Shader/PostEfffect.h"
#include"../Object/Player/PlayerManager.h"
#include"../Input/Input.h"
#include "Scene.h"

class TimeCount;

class GameScene :
    public Scene
{

public:

    GameScene(SceneMng& manager, int number_of_Players, Transitor& transit);
    ~GameScene();

    virtual void Update(Input& input) override;
    virtual void Draw() override;

private:

    //�������^�C�v
    enum class SOUND_TYPE
    {
        PUSH,
        CURSOR,
        GO,
        READY
    };

    //�摜�^�C�v
    enum class IMG_TYPE
    {
        GO,
        READY
    };

    static constexpr int IMG_SELECT_NUM =2;

    //���ʉ��Ǘ��z��
    std::map<SOUND_TYPE, int> sounds_;

    //�摜�z��
    std::map<IMG_TYPE, int> img_;

    //�X�e�[�W
    std::unique_ptr<Stage> stage_;
    //�J����
    std::unique_ptr<Camera> camera_;
    //���S�͈�
    std::unique_ptr<OutSide> outSide_;
    //�`�F�b�N�|�C���g
    std::unique_ptr<CheckPoint> checkPoint_;
    //�v���C���[�̊Ǘ�
    std::unique_ptr<PlayerManager>playerManager_;
    //���Ԍv��
    std::unique_ptr<TimeCount>timeCount_;

    void (GameScene::* _update)(Input& input,float elapsedTime);

    //�Q���v���C���[�̐�
    int playerNum_;

    //�X�^�[�g���o�̌v���p
    float startTime_;

    //�^�C�g���ɖ߂邩������킷�邩�̑I��p�摜
    int selectImg_[IMG_SELECT_NUM];

    //�^�C�g���ɖ߂邩������킷�邩�̑I��p�i���o�[
    int selectModeNum_;

    //���ʉ��̏�����
    void SoundInit(void);

    //�摜�̏�����
    void ImageInit(void);

    //��Ԑ擪�̃v���C���[�ɒǏ]������
    //�Q�[���V�[���Ő擪�����߂āA�J�����N���X�ɓn��
    void DecideOnTheBeginning();

    //�N���A��̃��[�h�I��(�^�C�g���ɖ߂��A�������Ȃ�)
    void Select(Input& input);

    //�N���A��̃��[�h�I��`��(�^�C�g���ɖ߂��A�������Ȃ�)
    void SelectDraw(void);

    //�����l�ΐ탂�[�h�A�b�v�f�[�g
    void MultiPlayUpdate(Input& input, float elapsedTime);

    //��l�p���[�h�A�b�v�f�[�g
    void SinglePlayUpdate(Input& input, float elapsedTime);

    //��l�p���[�h�ɕύX����
    void SinglePlayModeChange(void);

    //�ΐ�A��l�p�A�֌W�Ȃ��K�v�ȏ�����
    void StandardInit(void);

    //�X�^�[�g���o��\������
    void ReadyGoDraw(void);

};
