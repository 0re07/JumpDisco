#include "../common/Flame.h"
#include "Gamepad.h"

GamePad::GamePad()
{
	keyMap_.try_emplace(InputID::Up, PAD_INPUT_UP);
	keyMap_.try_emplace(InputID::Down, PAD_INPUT_DOWN);
	keyMap_.try_emplace(InputID::Left, PAD_INPUT_LEFT);
	keyMap_.try_emplace(InputID::Right, PAD_INPUT_RIGHT);
	keyMap_.try_emplace(InputID::Btn1, PAD_INPUT_1);
	keyMap_.try_emplace(InputID::Btn2, PAD_INPUT_1);
	keyMap_.try_emplace(InputID::Btn3, PAD_INPUT_1);
}

GamePad::~GamePad()
{
}

void GamePad::Update(void)
{
	//現在のデータを一つ前に保存する
	memcpy(inputData_[OldFlame].data(), inputData_[NowFlame].data(),
		sizeof(inputData_[OldFlame][NowFlame]) * inputData_[OldFlame].size());		

	//パッド情報を取得して格納する
	auto padData_ = GetJoypadInputState(DX_INPUT_PAD1);								

	//データ入力がされていたら1を入れる
	for (auto id : InputID())
	{
		inputData_[NowFlame][static_cast<int>(id)] = (padData_ & keyMap_[id]) > 0;
	}

}

void GamePad::Update(BaseScene& scene)
{
	//現在のデータを一つ前に保存する
	memcpy(inputData_[OldFlame].data(), inputData_[NowFlame].data(),
		sizeof(inputData_[OldFlame][NowFlame]) * inputData_[OldFlame].size());

	//パッド情報を取得して格納する
	auto padData_ = GetJoypadInputState(DX_INPUT_PAD1);								

	//データ入力がされていたら1を入れる
	for (auto id : InputID())
	{
		inputData_[NowFlame][static_cast<int>(id)] = (padData_ & keyMap_[id]) > 0;
	}
}
