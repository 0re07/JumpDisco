#include "../common/Flame.h"
#include "Controller.h"

Controller::Controller()
{
	memset(inputData_[NowFlame].data(), 0xff, inputData_[NowFlame].size() * sizeof(inputData_[NowFlame][NowFlame]));
	memset(inputData_[OldFlame].data(), 0xff, inputData_[OldFlame].size() * sizeof(inputData_[OldFlame][NowFlame]));
}

Controller::~Controller()
{
}

void Controller::Update(void)
{
}
