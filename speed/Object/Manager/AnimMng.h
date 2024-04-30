#pragma once
#include<map>
#include<list>
#include<string>
#include<array>


constexpr int GraphHD = 0;
constexpr int InvLimit = 1;
constexpr int ColLeft = 2;
constexpr int ColTop = 3;
constexpr int ColRight = 4;
constexpr int ColBottom = 5;


using AnimeData = std::array<int, 6>;
using AnimNode = std::pair<int, std::list<AnimeData>>;

//�Đ�����Ƃ�
using AnimItr = std::list<AnimeData>::iterator;

struct AnimStr
{
	std::string imgKey_; //ImageMng�ɓn���L�[�l
	std::string objID_; //�I�u�W�F�N�g�̎��
	std::string state_; //��ԁiIdle���j
	AnimItr animID_;	//�A�j���[�V�����̍Đ��ʒu
	int animCount_=0;		//���Y�A�j���[�V�����̌o�߃t���[��
	int animPlayCount_=0;//���Y�A�j���[�V�����̌����[�v��
	bool endFlag;

};

#define lpAnimMng AnimeMng::GetInstance()


class AnimeMng
{
public:

	static AnimeMng& GetInstance()
	{
		static AnimeMng s_Instance;
		return s_Instance;
	}
	std::string LoadAnime(std::string fileName);
	bool UpdateAnime(AnimStr& animCacha);
	void SetAnime(AnimStr& animDate, std::string state);




private:
	std::map<std::string, AnimNode> animeTbl_;

	AnimeMng();
	~AnimeMng();


};


