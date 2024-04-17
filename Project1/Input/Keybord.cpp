#include "../common/Flame.h"
#include "InputID.h"
#include "Keybord.h"

Keybord::Keybord()
{
	memset(keyData_, 0, sizeof(keyData_));

	//InPutID���i�[����		
	keyMap_.try_emplace(InputID::Up, KEY_INPUT_UP);
	keyMap_.try_emplace(InputID::Down, KEY_INPUT_DOWN);
	keyMap_.try_emplace(InputID::Left, KEY_INPUT_LEFT);
	keyMap_.try_emplace(InputID::Right, KEY_INPUT_RIGHT);
	keyMap_.try_emplace(InputID::Btn1, KEY_INPUT_Z);
	keyMap_.try_emplace(InputID::Btn2, KEY_INPUT_SPACE);
	keyMap_.try_emplace(InputID::Btn3, KEY_INPUT_SPACE);

}

Keybord::~Keybord()
{
}

void Keybord::Update(void)
{
	//���݂̃f�[�^����O�ɕۑ�����
	memcpy(inputData_[OldFlame].data(), inputData_[NowFlame].data(),
		sizeof(inputData_[OldFlame][NowFlame]) * inputData_[OldFlame].size());		

	//�L�[�����擾���Ċi�[����
	GetHitKeyStateAll(keyData_);		
	for (auto id : InputID())
	{
		inputData_[0][static_cast<int>(id)] = keyData_[keyMap_[id]];
	}

}

void Keybord::Update(BaseScene& scene)
{
	//���݂̃f�[�^����O�ɕۑ�����
	memcpy(inputData_[OldFlame].data(), inputData_[NowFlame].data(),
		sizeof(inputData_[OldFlame][NowFlame]) * inputData_[OldFlame].size());

	//�L�[�����擾���Ċi�[����
	GetHitKeyStateAll(keyData_);		
	for (auto id : InputID())
	{
		inputData_[0][static_cast<int>(id)] = keyData_[keyMap_[id]];
	}
}
