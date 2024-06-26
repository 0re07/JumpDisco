#pragma once		
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2D.h"

#define lpImageMng ImageMng::GetInstanse()

using VecInt = std::vector<int>;

class ImageMng
{
public:
	static ImageMng& GetInstanse()
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	const VecInt& GetID(std::string key);			//実際に使用するときはここで呼び出す
	const VecInt& GetID(std::string f_name, std::string key);										//LoadGraph版
	const VecInt& GetID(std::string f_name, std::string key, Vector2D divSize, Vector2D divCnt);	//LoadDivGraph版

private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VecInt> imageMap_;

};

