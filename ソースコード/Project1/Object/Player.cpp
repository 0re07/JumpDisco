#include <array>
#include <DxLib.h>
#include "../Scene/SceneMng.h"
#include "../common/Flame.h"
#include "../Input/Controller.h"
#include "../Input/GamePad.h"
#include "../Input/Keybord.h"
#include "../Input/InputID.h"
#include "../Manager/ImageMng.h"
#include "Player.h"

//プレイヤーの当たり判定の大きさ
constexpr float defSize = 20.0f;

//プレイヤーの移動量
constexpr int move = 3;

//プレイヤーのジャンプ量
const int maxJump = 3;

//プレイヤーの通常ライフ
constexpr int maxLife = 10;

const int END_TIME = 120;

Player::Player()
{
	//プレイヤー情報の初期化
	player_.pos = { screenSize_.x / 2, screenSize_.y / 2 };
	player_.radius = defSize;
	color_ = 0xffffff;	//黒
	life_ = maxLife;
	hit_ = false;
	mutekicount_ = 3.0f;	//後で定数化
	isDeath_ = false;
	playerCount_ = 0;
	score_ = 0;

	//状態の初期化
	state_ = STATE::IDLE;
}

Player::Player(int screenSizeX, int screenSizeY)
{
	screenSize_.x = screenSizeX;
	screenSize_.y = screenSizeY;

	//プレイヤー情報の初期化
	player_.pos = { screenSize_.x / 2, screenSize_.y / 2 };
	player_.radius = defSize;
	color_ = 0x00ff00;	//緑
	life_ = maxLife;
	hit_ = false;
	mutekicount_ = 3.0f;//後で定数化
	isDeath_ = false;
	playerCount_ = 0;
	score_ = 0;

	//状態の初期化
	state_ = STATE::IDLE;

}

Player::~Player()
{
}

bool Player::Init(void)
{
	//コントローラー情報取得
	if (GetJoypadNum())		
	{
		//パッドが接続されていた時
		controller_ = std::make_unique<GamePad>();
	}
	else
	{
		controller_ = std::make_unique<Keybord>();
	}

	int ret;

	//画像の読み込み
	ret = LoadDivGraph("Data/Image/Player/Idle.png", 4, 4, 1, 64, 64, idleImg_);
	ret = LoadDivGraph("Data/Image/Player/Run.png", 6, 6, 1, 64, 64, runImg_);
	ret = LoadDivGraph("Data/Image/Player/Jump.png", 4, 4, 1, 64, 64, jumpImg_);
	ret = LoadDivGraph("Data/Image/Player/Fall.png", 4, 4, 1, 64, 64, fallImg_);
	ret = LoadDivGraph("Data/Image/Player/Death.png", 6, 6, 1, 64, 64, deathImg_);

	//プレイヤー情報の初期化
	player_.pos = { screenSize_.x / 2, screenSize_.y / 2 };	
	player_.radius = defSize;	
	color_ = 0x00ff00;	//緑
	life_ = maxLife;
	hit_ = false;
	isDeath_ = false;

	//状態の初期化
	state_ = STATE::IDLE;

	return true;
}

void Player::Update(void)
{
	playerCount_++;

	ChengeState(state_);

	//状態遷移
	switch (state_)
	{
	case Player::STATE::IDLE:
		jump=0;
		mutekicount_ = 0;
		break;
	case Player::STATE::RUN:
		break;
	case Player::STATE::JUMP:
		UpdateJump();
		break;
	case Player::STATE::FALL:
		UpdateFall();
		break;
	case Player::STATE::HURT:
		UpdateHurt();
		break;
	case Player::STATE::DEATH:
		life_ = 0;
		UpdateDeath();
		break;
	}

	posOld_ = player_.pos;

	if (CheckNonMove())
	{
		ChengeState(STATE::IDLE);
	}

	if (CheckState(STATE::JUMP) && 
		!hit_)
	{
		score_++;
	}

}

void Player::Move(BaseScene& scene)
{
	auto contData = controller_->GetInputData();
	controller_->Update(scene);

	auto VecMove = [&]()
	{
		//移動処理
		if (contData[NowFlame][static_cast<int>(InputID::Up)])
		{
			player_.pos.y -= move;
			ChengeState(STATE::RUN);
		}
		if (contData[NowFlame][static_cast<int>(InputID::Down)])
		{
			player_.pos.y += move;
			ChengeState(STATE::RUN);
		}
		if (contData[NowFlame][static_cast<int>(InputID::Left)])
		{
			player_.pos.x -= move;
			ChengeState(STATE::RUN);
		}
		if (contData[NowFlame][static_cast<int>(InputID::Right)])
		{
			player_.pos.x += move;
			ChengeState(STATE::RUN);
		}
	};
	auto JumpMove = [&]()
	{
		//ジャンプ処理
		//押した瞬間のみ小ジャンプ
		//if (contData[NowFlame][static_cast<int>(InputID::Btn2)] &&
		//	!contData[OldFlame][static_cast<int>(InputID::Btn2)])
		if (contData[NowFlame][static_cast<int>(InputID::Btn2)])
		{
			ChengeState(STATE::JUMP);
		}
	};

	VecMove();
	JumpMove();
}

void Player::Draw(void)
{
	//影の描画
	DrawOval(player_.pos.x - player_.radius / 2, 
		player_.pos.y + player_.radius, 
		15, 5, 0x000000, true);

	switch (state_)
	{
	case Player::STATE::NON:
		break;
	case Player::STATE::IDLE:
		DrawGraph(player_.pos.x - 32, player_.pos.y - 40, idleImg_[(playerCount_/10) % 3], true);
		break;
	case Player::STATE::RUN:
		DrawGraph(player_.pos.x - 32, player_.pos.y - 40, runImg_[(playerCount_ / 10) % 5 ], true);
		break;
	case Player::STATE::JUMP:
		DrawGraph(player_.pos.x - 32, player_.pos.y - 40, jumpImg_[(playerCount_/10) % 3], true);
		break;
	case Player::STATE::FALL:
		DrawGraph(player_.pos.x - 32, player_.pos.y - 40, fallImg_[(playerCount_/10) % 3], true);
		break;
	case Player::STATE::DEATH:
		DrawGraph(player_.pos.x - 32, player_.pos.y - 40,deathImg_[(playerCount_/10) % 5], true);
		break;
	default:
		break;
	}
}

bool Player::IsHit(Circle hoop)
{
	if (CheckState(STATE::IDLE) || CheckState(STATE::RUN))
	{
		//行った先から行った元を引く
		auto diffX = player_.pos.x - hoop.pos.x;
		auto diffY = player_.pos.y - hoop.pos.y;

		// 斜辺を求める
		auto  distance = hypotf(diffX, diffY);

		//当たっているか
		float overlapLength = player_.radius + hoop.radius / 2 - distance;
		if (overlapLength >= 0.0f)
		{
			hit_ = true;	//当たり
			life_--;
			ChengeState(STATE::HURT);

			if (life_ <= 0)
			{
				//isDeath_ = true;
			}
		}	
		else 
		{
			hit_ = false;
		}
	}
	else if (
		CheckState(STATE::JUMP) ||
		CheckState(STATE::FALL) ||
		CheckState(STATE::HURT))
	{
		hit_ = false;
	}

	return hit_;
}

void Player::SetColor(unsigned int color)
{
	color_ = color;
}

bool Player::IsDeath(void) const
{
	return isDeath_;
}

bool Player::GetHit(void)
{
	return hit_;
}

void Player::ChengeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case Player::STATE::IDLE:
		break;
	case Player::STATE::RUN:
		break;
	case Player::STATE::JUMP:
		break;
	case Player::STATE::FALL:
		break;
	case Player::STATE::HURT:
		break;
	case Player::STATE::DEATH:
		break;
	}
}

bool Player::CheckState(STATE state)
{
	if (state_ == state)
	{
		return true;
	}
	return false;
}

void Player::UpdateJump(void)
{
	while (jump <= maxJump)
	{
		jump++;
	}
	//player_.pos.y -= jump;

	ChengeState(STATE::FALL);
}

void Player::UpdateFall(void)
{
	while (jump >= 0)
	{
		jump--;
	}
	//player_.pos.y += jump;

	if (jump == 0)
	{
		ChengeState(STATE::IDLE);
	}
}

void Player::UpdateHurt(void)
{
	life_--;

	//ライフが０なら死亡
	if (life_ <= 0)
	{
		ChengeState(STATE::DEATH);
	}
}

void Player::UpdateDeath(void)
{
	isDeath_ = true;
}

bool Player::CheckNonMove(void)
{
	if (posOld_ == player_.pos)
	{
		return true;
	}
	return false;
}

bool Player::IsEndCount(void)
{
	int count = 0;
	if (count >= END_TIME)
	{
		return false;
	}
	count++;

	return true;
}
