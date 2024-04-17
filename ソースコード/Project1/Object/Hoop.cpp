#include <time.h>
#include <DxLib.h>
#include "../Scene/SceneMng.h"
#include "Hoop.h"

//�ʏ펞�̉~�̑傫��
constexpr float outDefSize = 0.0f;   //�O��
constexpr float inDefSize = -7.0f;   //����

//�o���ʒu
constexpr float coreDefSize = 0.0f;
constexpr float coreMaxSize = 10.0f;

//�~�̏����F
constexpr int defColor = 0xff0000;
constexpr int bfrColor = 0xffffff;

//�~�̍L����X�s�[�h
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

	//�O���̉~
	outHoop_.pos = pos;	//���W
	outHoop_.radius = outDefSize;		//���a

	//�����̉~
	inHoop_.pos = outHoop_.pos;			//���W
	inHoop_.radius = inDefSize;			//���a

	//�o���ʒu
	coreRadius_ = coreDefSize;

	isEnd_ = false;

	//�~�̐F
	color_ = bfrColor;

	Init();

}

Hoop::~Hoop()
{
}

bool Hoop::Init(void)
{
	//��ʃT�C�Y���擾
	screenSize_ = lpSceneMng.GetScreenSize();

	//�������
	state_ = STATE::BORN;

	//������������
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
	//������
	coreRadius_ = coreDefSize;

	outHoop_.pos = { rand() % screenSize_.x ,rand() % screenSize_.y };
	outHoop_.radius = outDefSize;

	inHoop_.pos = outHoop_.pos;
	inHoop_.radius = inDefSize;	

	//�~�̐F
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

	//�L���点��
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
	//�����蔻��
	if (isEnd_)
	{
		DrawOval(outHoop_.pos.x, outHoop_.pos.y, coreRadius_, coreRadius_ / 2, color_, true);
	}

	//�L����~
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
