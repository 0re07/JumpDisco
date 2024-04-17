#pragma once
#include <map>
#include <array>
#include <list>
#include <string>

constexpr int GraphHD = 0;
constexpr int InvLimit = 1;

//当たり判定
constexpr int ColLeft = 2; 
constexpr int ColTop = 3;
constexpr int ColRight = 4;
constexpr int ColBottom = 5;

using AnimData = std::array<int, 6>;
using AnimNode = std::pair<int, std::list<AnimData>>;
using AnimItr = std::list<AnimData>::iterator;

struct AnimeStr	
{
	std::string imgKey_;	//ImgMngに渡すキー値
	std::string objID_;		//オブジェクトの種別
	std::string state_;		//状態（Idleなど）
	AnimItr animID_;		//アニメーションの再生位置
	int animCount_;			//当該アニメーションの経過フレーム数
	int animPlayCount_;		//当該アニメーションの現ループ回数
	bool endFlag_;			//アニメーションの終了判定
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
	std::string LoadAnime(std::string fileName);					//アニメーションを読み込む
	bool UpdateAnime(AnimeStr& animeCache);					//アニメーションを動かす
	void SetAnime(AnimeStr& animData, std::string state);	//アニメーションをセットする

private:
	std::map<std::string, AnimNode> animeTbl_;				//first:再生回数	second:何のやつか
	AnimeMng();
	~AnimeMng();

};

