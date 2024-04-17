#pragma once
#include <chrono>
#include <memory>
#include "../common/Vector2D.h"
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	void Run(void);

	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}

	//��ʃT�C�Y�̎擾
	Vector2D GetScreenSize(void) const;

private:
	SceneMng();
	~SceneMng();
	bool Update(void);
	void Draw(void);
	bool SysInit(void);

	bool initFlag_;

	uniquScene scene_;

	//�f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
};