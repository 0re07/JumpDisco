#pragma once
#include <list>
#include <memory>
#include "../common/Vector2D.h"
#include "../Input/Controller.h"
#include "../Scene/TmxObj.h"
#include "State/DirLR.h"

class Obj;
using UniqueObj = std::unique_ptr<Obj>;
using ObjList = std::list<UniqueObj>;

struct SetAnime;
struct CheckNonState;
struct CheckState;
struct SetFall;
struct SetJump;
struct SetBigJump;
struct UpdateFall;
struct UpdateJump;
struct UpdateBigJump;
struct CheckKey;
struct CheckDir;
struct SetDir;
struct CheckNonMove;
struct Move;

class Obj
{
public:
	Obj(TmxObj& tmxObj, ObjList& ownerList);
	virtual ~Obj();
	virtual void Update(void) = 0;
	virtual void Draw(void);
	const DIR_LR GetDir(void) const { return dirLR_; }
	const bool isDeth(void) const { return deathFlag_; }

protected:
	std::unique_ptr<Controller> controller_;

	DIR_LR dirLR_;

	TmxObj& tmxObj_;
	ObjList& ownerList_;

	//プレイヤー関連
	Vector2D pos_;
	Vector2D posOld_;
	//float radius_;      
	//Vector2D center_;
	double jump_;

	//unsigned int color_;//プレイヤーの色
	//DIR_LR dirLR_;      //左右方向
	//int life_;          //ライフ
	//bool hit_;          //当たり判定
	bool deathFlag_;	//生死状況

	friend SetAnime;
	friend CheckNonState;
	friend CheckState;
	friend SetFall;
	friend SetJump;
	friend SetBigJump;
	friend UpdateFall;
	friend UpdateJump;
	friend UpdateBigJump;
	friend CheckKey;
	friend CheckDir;
	friend SetDir;
	friend CheckNonMove;
	friend Move;
};

