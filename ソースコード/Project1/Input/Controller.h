#pragma once
#include <DxLib.h>
#include <map>
#include <array>
#include "InputID.h"

class BaseScene;

using InputData = std::array<int, static_cast<int>(InputID::Max)>;
using InputDatas = std::array<InputData, 2>;

class Controller
{
public:
	Controller();
	~Controller();
	virtual void Update(BaseScene& scene) = 0;
	virtual void Update(void);
	const InputDatas& GetInputData(void) { return inputData_; }

protected:
	InputDatas inputData_;
	std::map<InputID, int> keyMap_;		//InputIDÇÃäiî[êÊ

};

