#include "Game2Scene.h"
#include"SimpleAudioEngine.h"
#include"ui\CocosGUI.h"

using namespace CocosDenshion;
using namespace ui;

Game2Scene::Game2Scene()
{
}


Game2Scene::~Game2Scene()
{
}
Scene* Game2Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Game2Scene::create();
	scene->addChild(layer);
	return scene;
}
bool Game2Scene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//使用gamescene.csb加载界面
	auto game2Scene = CSLoader::createNode("Game2Scene.csb");
	addChild(game2Scene);
	//预加载背景音乐
	SimpleAudioEngine::getInstance()->preloadEffect("andy.mp3");
	unsigned int id2 = SimpleAudioEngine::getInstance()->playEffect("andy.mp3");

	return true;
}

