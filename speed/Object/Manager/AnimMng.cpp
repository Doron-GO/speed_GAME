#include "AnimMng.h"
#include<sstream>
#include"../../rapidxml/rapidxml.hpp"
#include"../../rapidxml/rapidxml_utils.hpp"
#include"../GetAtr.h"
#include"ImageMng.h"
#include"../../Vector2D.h"

std::string AnimeMng::LoadAnime(std::string fileName)
{
    rapidxml::xml_document <> actDoc;
    rapidxml::file<> xmlFile = fileName.c_str();
    actDoc.parse<0>(xmlFile.data());
    auto actionLiat = actDoc.first_node("actionList");
    auto getAtr = GetAtr();
    std::string CharName;
    if (actionLiat == nullptr)
    {
        return std::string();
        //TRACE("actionLiat�擾�G���[\n");
    }
    getAtr(actionLiat, "name", CharName);

    std::string source;
    std::string KeyName;
    Vector2D divSize;
    Vector2D divCnt;

    //����Ԃ�actionNode���Ƃ�I���܂ŉ�郋�[�v
    for (auto actionNode = actionLiat->first_node("action");
        actionNode != nullptr;
        actionNode = actionNode->next_sibling()) {

        getAtr(actionNode, "source", source);
        getAtr(actionNode, "name", KeyName);
        getAtr(actionNode, "divSizeX", divSize.x);
        getAtr(actionNode, "divSizeY", divSize.y);
        getAtr(actionNode, "divCntX", divCnt.x);
        getAtr(actionNode, "divCntY", divCnt.y);
        ImageMng::GetInstsnce().GetID(source, CharName + KeyName, divSize, divCnt);

        //�������̃L�[�̖��O�����Ԃ�₷���̂ɂ��Ȃ�����
        auto result = animeTbl_.try_emplace(CharName + KeyName);

        if (!result.second)
        {
            return CharName;
        }
        auto animeNode = actionNode->first_node("anime");
        if (animeNode == nullptr)
        {
           // TRACE("animeNode�擾�G���[\n");
            return std::string();
        }
        int loop;
        getAtr(animeNode, "loop", loop);
        //�A�j���[�V�����̃��[�v�񐔂����Ă�
        animeTbl_[CharName + KeyName].first = loop;
        auto animeData = animeNode->first_node();

        std::stringstream dataStream;
        dataStream << animeData->value();
        std::string numStr;

        while (getline(dataStream, numStr, ','))
        {
            auto id = atoi(numStr.c_str());
            getline(dataStream, numStr, ',');
            auto freme = atoi(numStr.c_str());
            int csv[4];

            for (int j = 0; j < 4; j++)
            {
                getline(dataStream, numStr, ',');
                csv[j] = atoi(numStr.c_str());
            }
            animeTbl_[CharName + KeyName].second.emplace_back(AnimeData{ id,freme,csv[1],csv[1],csv[2],csv[3] });
        }

    }
    return CharName;
}

bool AnimeMng::UpdateAnime(AnimStr& animCacha)
{
    //�Đ����I���܂ōs������bigin�ɖ߂�
    //�L�����N�^�[�̃A�j���o�߃t���[�����ő�܂ōs������
    if (animCacha.animCount_++ >= (*animCacha.animID_)[InvLimit])
    {
        //�o�߃t���[�����O�ɖ߂�
        animCacha.animCount_ = 0;
        //�A�j���[�V�����̍Đ��ʒu�����ɂ���
          // ++animCache.animID_;

           //�A�j���[�V�����̍Đ��ʒu���Ō�܂ōs������
        if (++animCacha.animID_ == animeTbl_[animCacha.objID_ + animCacha.state_].second.end())
        {
            //�A�j���[�V�����̌����[�v���𑝂₷
             // animCache.animPlayCount_++;

            if (++animCacha.animPlayCount_ == animeTbl_[animCacha.objID_ + animCacha.state_].first || animeTbl_[animCacha.objID_ + animCacha.state_].first == -1) {


                animCacha.animID_ = animeTbl_[animCacha.objID_ + animCacha.state_].second.begin();

            }
            else
            {
                animCacha.animID_ = --(animeTbl_[animCacha.objID_ + animCacha.state_].second.end());
                animCacha.endFlag = true;
            }
        }
    }
    return false;
}

void AnimeMng::SetAnime(AnimStr& animDate, std::string state)
{
    //��ԃ`�F�b�N
    if (state == animDate.state_)
    {
        return;
    }

    animDate = AnimStr{
        animDate.objID_ + state,
        animDate.objID_,
        state,                            //���Z�J���h�̓��X�g
        animeTbl_[animDate.objID_ + state].second.begin(),
        0,
        0,
        false
    };

}

AnimeMng::AnimeMng()
{
}

AnimeMng::~AnimeMng()
{
}
