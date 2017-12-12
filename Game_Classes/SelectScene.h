#pragma once
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;
class SelectScene:public cocos2d::Layer
{
public:
	SelectScene();
	~SelectScene();
	static Scene*createScene();
	bool init();
	CREATE_FUNC(SelectScene);
};

