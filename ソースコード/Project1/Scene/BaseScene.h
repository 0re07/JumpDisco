#pragma once
#include<DxLib.h>
#include<memory>
#include"../common/Vector2D.h"

class BaseScene;
class Controller;

using uniquScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene(int screenSizeX, int screenSizeY);
	~BaseScene();
	virtual bool Init(void);
	virtual uniquScene Update(uniquScene ownScene, float deltaTime) = 0;
	virtual void DrawOwnScreen(void) = 0;
	virtual void Draw(void);

protected:
	Vector2D drawOffset_;
	const Vector2D screenSize_;
	int screenID_;

	std::unique_ptr<Controller> controller_;			//コントローラーの管理

	//後から一括管理
	int titleMusic_;   
	int gameMusic_;
};

