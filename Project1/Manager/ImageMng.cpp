#include <DxLib.h>
#include "ImageMng.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugConOut.h"

const VecInt& ImageMng::GetID(std::string key)
{
	if (imageMap_.count(key) == 0)
	{
		GetID(key, key);
	}
	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)			
{
	//	画像を読み込んでいない場合は読み込む
	if (imageMap_.count(key) == 0)
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());
	}
	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2D divSize, Vector2D divCnt)
{
	//	画像を読み込んでいない場合は読み込む
	if (imageMap_.count(key) == 0)
	{
		//	要素数を使用分コンテナ確保する
		imageMap_[key].resize(static_cast<UINT64>(divCnt.x) * static_cast<UINT64>(divCnt.y));		//	UINT64 = size_t

		if(
			LoadDivGraph(f_name.c_str(),
			divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, 
				&imageMap_[key][0], true)
			== -1)
		{
			TRACE("(ImgM)画像の読み込み失敗:%s\n", f_name.c_str());
		}
		//TRACE("(ImgM)画像の読み込み:%s\n", f_name.c_str());
	}
	return imageMap_[key];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
