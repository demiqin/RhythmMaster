#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"SelectScene.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	Button* starGameBtn = (Button*)rootNode->getChildByName("StarGameBtn");
	//预加载背景音乐
	SimpleAudioEngine::getInstance()->preloadEffect("mode_select_02.wav");
	unsigned int id = SimpleAudioEngine::getInstance()->playEffect("mode_select_02.wav");
	starGameBtn->addClickEventListener([=](Ref*)//=为调用本界面&为调用.h界面
	{
		SimpleAudioEngine::getInstance()->stopEffect(id);//停止背景音乐
		Director::getInstance()->replaceScene(SelectScene::createScene());
	});
    return true;
}
