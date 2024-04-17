#pragma once
#include <map>
#include <array>
#include <list>
#include <string>

constexpr int GraphHD = 0;
constexpr int InvLimit = 1;

//�����蔻��
constexpr int ColLeft = 2; 
constexpr int ColTop = 3;
constexpr int ColRight = 4;
constexpr int ColBottom = 5;

using AnimData = std::array<int, 6>;
using AnimNode = std::pair<int, std::list<AnimData>>;
using AnimItr = std::list<AnimData>::iterator;

struct AnimeStr	
{
	std::string imgKey_;	//ImgMng�ɓn���L�[�l
	std::string objID_;		//�I�u�W�F�N�g�̎��
	std::string state_;		//��ԁiIdle�Ȃǁj
	AnimItr animID_;		//�A�j���[�V�����̍Đ��ʒu
	int animCount_;			//���Y�A�j���[�V�����̌o�߃t���[����
	int animPlayCount_;		//���Y�A�j���[�V�����̌����[�v��
	bool endFlag_;			//�A�j���[�V�����̏I������
};


#define lpAnimeMng AnimeMng::GetInstance()

class AnimeMng
{
public:
	static AnimeMng& GetInstance()
	{
		static AnimeMng s_Instance;
		return s_Instance;
	}
	std::string LoadAnime(std::string fileName);					//�A�j���[�V������ǂݍ���
	bool UpdateAnime(AnimeStr& animeCache);					//�A�j���[�V�����𓮂���
	void SetAnime(AnimeStr& animData, std::string state);	//�A�j���[�V�������Z�b�g����

private:
	std::map<std::string, AnimNode> animeTbl_;				//first:�Đ���	second:���̂��
	AnimeMng();
	~AnimeMng();

};

