#include <DxLib.h>
#include "KeyInput.h"

KeyInput::KeyInput()
{
	inputTbl_ = {
		{InputID::UP,KEY_INPUT_UP},
		{InputID::DOWN,KEY_INPUT_DOWN},
		{InputID::LEFT,KEY_INPUT_LEFT},
		{InputID::RIGHT,KEY_INPUT_RIGHT},
		{InputID::BTN1,KEY_INPUT_Z},
		{InputID::BTN2,KEY_INPUT_X},
		{InputID::BTN3,KEY_INPUT_SPACE}
	};

	//InputIDごとにinputTbl_をつくる
	for (auto tblData : inputTbl_)
	{
		cntData_.emplace(tblData.first, TrgBool{ 0,0 });
	}

	ringBuf_ = RingBuf::Create(20);
}

KeyInput::~KeyInput()
{
	RingBuf::Destroy(ringBuf_);
}

void KeyInput::Update(void)
{
	GetHitKeyStateAll(keyData_.data());		//arrayなので.dataでアクセス
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[inputTbl_[id]];		//データの格納
	}

	//WriteCmd();
}
