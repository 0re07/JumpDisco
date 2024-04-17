#include <DxLib.h>
#include "Obj.h"

Obj::Obj(TmxObj& tmxObj, ObjList& ownerList) :tmxObj_(tmxObj), ownerList_(ownerList)
{
	deathFlag_ = false;
}

Obj::~Obj()
{
}

void Obj::Draw(void)
{
}
