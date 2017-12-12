#pragma once
#include"cocos2d.h"
#include"cocostudio\CocoStudio.h"
#include"ui\CocosGUI.h"
using namespace ui;
USING_NS_CC;
using namespace cocostudio::timeline;

class GameScene:public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* createScene();
	bool init();
	CREATE_FUNC(GameScene);
	Size winSize;
	Vector<Sprite*>firstnode;
	Vector<Sprite*>secondnode;
	Vector<Sprite*>thirdnode;
	Vector<Sprite*>fournode;
	LoadingBar * lad;
	Label*Score;
	int score1=0;
	float score=100.f;
	
	void start(float dt);
	void removeStart(Node* Sender);
	void removeBtn(Ref* sender);
};

