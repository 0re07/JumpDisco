#include <DxLib.h>
#include "PadInput.h"

PadInput::PadInput()
{
	inputTbl_ = {
	{InputID::NON,0},
	{InputID::UP,PAD_INPUT_UP},
	{InputID::DOWN,PAD_INPUT_DOWN},
	{InputID::LEFT,PAD_INPUT_LEFT},
	{InputID::RIGHT,PAD_INPUT_RIGHT},
	{InputID::BTN1,PAD_INPUT_1},
	{InputID::BTN2,PAD_INPUT_2},
	{InputID::BTN3,PAD_INPUT_START},
	};

	for (auto tblData : inputTbl_)
	{
		cntData_.emplace(tblData.first, TrgBool{ 0,0 });
	}
	ringBuf_ = RingBuf::Create(20);
}

PadInput::~PadInput()
{
}

void PadInput::Update(void)
{
	auto inputDat = GetJoypadInputState(DX_INPUT_PAD1);
	for (auto id : inputTbl_)
	{
		cntData_[id.first][static_cast<int>(Trg::Old)] = cntData_[id.first][static_cast<int>(Trg::Now)];
		cntData_[id.first][static_cast<int>(Trg::Now)] = ((inputDat & id.second) > 0);
	}
	//WriteCmd();
}

bool PadInput::Init(void)
{
	return false;
}
