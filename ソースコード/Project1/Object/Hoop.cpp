#include <time.h>
#include <DxLib.h>
#include "../Scene/SceneMng.h"
#include "Hoop.h"

//通常時の円の大きさ
constexpr float outDefSize = 0.0f;   //外側
constexpr float inDefSize = -7.0f;   //内側

//出現位置
constexpr float coreDefSize = 0.0f;
constexpr float coreMaxSize = 10.0f;

//円の初期色
constexpr int defColor = 0xff0000;
constexpr int bfrColor = 0xffffff;

//円の広がるスピード
constexpr float spread = 3.0f;

Hoop::Hoop()
{
	for (int j = 0; j < 2; j++)
	{
		outHoop_.pos[j] = j;
	}
}

Hoop::Hoop(Vector2D pos)
{

	//外側の円
	outHoop_.pos = pos;	//座標
	outHoop_.radius = outDefSize;		//半径

	//内側の円
	inHoop_.pos = outHoop_.pos;			//座標
	inHoop_.radius = inDefSize;			//半径

	//出現位置
	coreRadius_ = coreDefSize;

	isEnd_ = false;

	//円の色
	color_ = bfrColor;

	Init();

}

Hoop::~Hoop()
{
}

bool Hoop::Init(void)
{
	//画面サイズを取得
	screenSize_ = lpSceneMng.GetScreenSize();

	//初期状態
	state_ = STATE::BORN;

	//乱数を初期化
	srand((unsigned int)time(NULL));

	return true;
}

void Hoop::Update(void)
{

	switch (state_)
	{
	case Hoop::STATE::BORN:
		UpdateBorn();
		break;
	case Hoop::STATE::BEFORE:
		UpdateBefore();
		break;
	case Hoop::STATE::START:
		coreRadius_ = coreMaxSize;
		color_ = defColor;
		UpdateStart();
		break;
	case Hoop::STATE::END:
		UpdateEnd();
		break;
	default:
		break;
	}
}

void Hoop::UpdateBorn(void)
{
	//初期化
	coreRadius_ = coreDefSize;

	outHoop_.pos = { rand() % screenSize_.x ,rand() % screenSize_.y };
	outHoop_.radius = outDefSize;

	inHoop_.pos = outHoop_.pos;
	inHoop_.radius = inDefSize;	

	//円の色
	color_ = bfrColor;

	if (!isEnd_)
	{
		isEnd_ = true;

		ChengeState(STATE::BEFORE);
	}

}

void Hoop::UpdateBefore(void)
{
	coreRadius_++;
	
	if (coreRadius_ >= coreMaxSize)
	{
		ChengeState(STATE::START);
	}

}

void Hoop::UpdateStart(void)
{

	//広がらせる
	outHoop_.radius += spread;
	inHoop_.radius += spread;

	if (inHoop_.radius >= screenSize_.x + 30.0f)
	{
		ChengeState(STATE::END);
	}

}

void Hoop::UpdateEnd(void)
{
	coreRadius_--;

	if (coreRadius_ <= coreDefSize)
	{
		isEnd_ = false;

		ChengeState(STATE::BORN);
	}
}

void Hoop::Draw(void)
{
	//当たり判定
	if (isEnd_)
	{
		DrawOval(outHoop_.pos.x, outHoop_.pos.y, coreRadius_, coreRadius_ / 2, color_, true);
	}

	//広がる円
	DrawOval(outHoop_.pos.x, outHoop_.pos.y, outHoop_.radius, outHoop_.radius / 2, color_, false);
	DrawOval(inHoop_.pos.x, inHoop_.pos.y, inHoop_.radius, inHoop_.radius / 2, color_, false);
}

void Hoop::Create(void)
{
}

Circle Hoop::GetInHoop(void)const
{
	return inHoop_;
}

Circle Hoop::GetOutHoop(void)const
{
	return outHoop_;
}

void Hoop::Release(void)
{
}

void Hoop::ChengeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case Hoop::STATE::BORN:
		break;
	case Hoop::STATE::BEFORE:
		break;
	case Hoop::STATE::START:
		break;
	case Hoop::STATE::END:
		break;
	default:
		break;
	}
}
