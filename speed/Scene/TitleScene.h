#pragma once
#include "Scene.h"
#include<memory>
#include<map>
#include"Transition/TileTransitor.h"


class TitleScene :
    public Scene
{
public:
    TitleScene(SceneMng& manager, int number_of_Players, Transitor& transit);
    ~TitleScene();
    virtual void Update(Input& input) override;
    virtual void Draw() override;

private:

    //���ʉ��^�C�v
    enum class SOUND_TYPE
    {
        PUSH,
        CURSOR
    };

    //�摜�^�C�v
    enum class IMG_TYPE
    {
        GO,
        READY
    };

    //���ʉ��Ǘ��z��
    std::map<SOUND_TYPE, int> sounds_;
    //�摜�z��
    std::map<IMG_TYPE, int> img_;

    bool startFlag_;
    int titleImg_;
    int startImg_;
    int selectImg_[4];
    //�v���C�l��
    int playModeNum_;
};

