#pragma once
#include"cocos2d.h"
#include"cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio::timeline;

class Game2Scene:public cocos2d::Layer
{
public:
	Game2Scene();
	~Game2Scene();
	static Scene* createScene();
	bool init();
	CREATE_FUNC(Game2Scene);
};

