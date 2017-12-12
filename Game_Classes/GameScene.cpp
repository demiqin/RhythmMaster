#include "GameScene.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	//使用gamescene.csb加载界面
	auto gameScene = CSLoader::createNode("GameScene.csb");
	addChild(gameScene);
	//预加载背景音乐
	SimpleAudioEngine::getInstance()->preloadEffect("andy.mp3");

	auto rootNode = CSLoader::createNode("GameScene.csb");
	addChild(rootNode);
	lad = (LoadingBar*)rootNode->getChildByName("LoadingBar1");
	lad->setPercent(score);
	//分数显示
	Score = Label::createWithTTF("Score 0", "fonts/Marker Felt.ttf", 36);
	Score->setPosition(winSize.width*.75f, winSize.height*.94f);
	Score->setColor(Color3B::ORANGE);
	this->addChild(Score);
	//按钮
	Button* KeyBtn1 = (Button*)rootNode->getChildByName("Key1Btn");
	KeyBtn1->addClickEventListener(CC_CALLBACK_1(GameScene::removeBtn, this));
	Button* KeyBtn2 = (Button*)rootNode->getChildByName("Key2Btn");
	KeyBtn2->addClickEventListener(CC_CALLBACK_1(GameScene::removeBtn, this));
	Button* KeyBtn3= (Button*)rootNode->getChildByName("Key3Btn");
	KeyBtn3->addClickEventListener(CC_CALLBACK_1(GameScene::removeBtn, this));
	Button* KeyBtn4 = (Button*)rootNode->getChildByName("Key4Btn");
	KeyBtn4->addClickEventListener(CC_CALLBACK_1(GameScene::removeBtn, this));
	KeyBtn1->setTag(1001);
	KeyBtn2->setTag(1002);
	KeyBtn3->setTag(1003);
	KeyBtn4->setTag(1004);

	//开始动画(3,2,1)
	auto startSp=Sprite::create("d3.png");
	startSp->setPosition(winSize.width / 2, winSize.height*.6f);
	startSp->setScale(2.5f);
	addChild(startSp);

	Animation* ani = Animation::create();
	ani->setDelayPerUnit(.1f);
	ani->addSpriteFrameWithFileName("d3.png");
	ani->addSpriteFrameWithFileName("d2.png");
	ani->addSpriteFrameWithFileName("d1.png");
	Animate*animate = Animate::create(ani);
	//回调
	CallFuncN* call = CallFuncN::create(this,callfuncN_selector(GameScene::removeStart));
	//顺序动作
	Sequence* seq = Sequence::create(animate,call,NULL);
	startSp->runAction(seq);

	return true;
}
void GameScene::start(float dt)
{
	int rand = random(1, 4);
	//创建音符
	auto musicnoteSp = Sprite::create(StringUtils::format("button_4key_3_%d.png", rand));

	Vec2 rawPos;//初始值
	Vec2 endPos;//末值
	switch (rand)
	{
	case 1:
		rawPos.x = 400;
		rawPos.y = 584;

		endPos.x = 105;
		endPos.y = -musicnoteSp->getContentSize().height;
		firstnode.pushBack(musicnoteSp);
		break;	
	case 2:
		rawPos.x = 450;
		rawPos.y = 584;

		endPos.x =355;
		endPos.y = -musicnoteSp->getContentSize().height;;
		secondnode.pushBack(musicnoteSp);
		break;
	case 3:
		rawPos.x = 520;
		rawPos.y = 584;

		endPos.x = 599;
		endPos.y = -musicnoteSp->getContentSize().height;;
		thirdnode.pushBack(musicnoteSp);
		break;
	case 4:
		rawPos.x = 562;
		rawPos.y = 584;

		endPos.x = 850;
		endPos.y = -musicnoteSp->getContentSize().height;;
		fournode.pushBack(musicnoteSp);
		break;
	default:
		break;
	}
//初始位置
	musicnoteSp->setPosition(rawPos);
//初始大小
	musicnoteSp->setScale(.5f);
	this->addChild(musicnoteSp);
//移动位置
	MoveTo* moveto = MoveTo::create(2.f,endPos);
//缩放大小
	ScaleBy *scale = ScaleBy::create(2.f,4.5f);
//一起动作
	Spawn* spawn = Spawn::create(moveto, scale, NULL);
	musicnoteSp->runAction(spawn);
}
void GameScene::removeStart(Node* Sender)
{
	this->removeChild(Sender);
	//开启定时器（音符）
	this->schedule(schedule_selector(GameScene::start), .5f);

	unsigned int id2 = SimpleAudioEngine::getInstance()->playEffect("andy.mp3");
}
void GameScene::removeBtn(Ref* sender)
{
	Button* btn = (Button*)sender;
	int tag = btn->getTag();
	CCLOG("tag :: %d", tag);
	switch (tag)
	{
	case 1001:
		if (firstnode.size() > 0)
		{
			if (abs(btn->getPositionY() - firstnode.at(0)->getPositionY()) <= 30)
			{
				auto p = Sprite::create("s_perfect.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(firstnode.at(0));
				firstnode.erase(firstnode.begin());
				score1 += 500;
			}
			else if (abs(btn->getPositionY() - firstnode.at(0)->getPositionY()) <= 60)
			{
				auto p = Sprite::create("s_great.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(firstnode.at(0));
				firstnode.erase(firstnode.begin());
				score1 += 300;
			}
			else if (abs(btn->getPositionY() - firstnode.at(0)->getPositionY()) > 60)
			{
				auto p = Sprite::create("s_miss.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(firstnode.at(0));
				firstnode.erase(firstnode.begin());
				lad->setPercent(score -= 2);
			}
			Score->setString(StringUtils::format("Score%d", score1));
		}
		break;
	case 1002:
		if (secondnode.size() > 0)
		{

			if ( abs(btn->getPositionY() - secondnode.at(0)->getPositionY()) <= 30)
			{
				auto p = Sprite::create("s_perfect.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(secondnode.at(0));
				secondnode.erase(secondnode.begin());
				score1 += 500;
			}
			else if ( abs(btn->getPositionY() - secondnode.at(0)->getPositionY()) <= 60)
			{
				auto p = Sprite::create("s_great.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(secondnode.at(0));
				secondnode.erase(secondnode.begin());
				score1 += 300;
			}
			else if (abs(btn->getPositionY() - secondnode.at(0)->getPositionY()) > 60)
			{
				auto p = Sprite::create("s_miss.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(secondnode.at(0));
				secondnode.erase(secondnode.begin());
				lad->setPercent(score -= 2);
			}
			Score->setString(StringUtils::format("Score%d", score1));
		}
		break;
	case 1003:
		if (thirdnode.size() > 0)
		{
			if (abs(btn->getPositionY() - thirdnode.at(0)->getPositionY()) <= 30)
			{
				auto p = Sprite::create("s_perfect.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(thirdnode.at(0));
				thirdnode.erase(thirdnode.begin());
				score1 += 500;
			}
			else if (abs(btn->getPositionY() - thirdnode.at(0)->getPositionY()) <= 60)
			{
				auto p = Sprite::create("s_great.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(thirdnode.at(0));
				thirdnode.erase(thirdnode.begin());
				score1 += 300;
			}
			else if (abs(btn->getPositionY() - thirdnode.at(0)->getPositionY()) > 60)
			{
				auto p = Sprite::create("s_miss.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(thirdnode.at(0));
				thirdnode.erase(thirdnode.begin());
				lad->setPercent(score -= 2);
			Score->setString(StringUtils::format("Score%d", score1));
			}
			Score->setString(StringUtils::format("Score%d", score1));
		}
		break;
	case 1004:
		if (fournode.size() > 0)
		{
			if (abs(btn->getPositionY() - fournode.at(0)->getPositionY()) <= 30)
			{
				auto p = Sprite::create("s_perfect.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(fournode.at(0));
				fournode.erase(fournode.begin());
				score1 += 500;
			}
			else if (abs(btn->getPositionY() - fournode.at(0)->getPositionY()) <= 60)
			{
				auto p = Sprite::create("s_great.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(fournode.at(0));
				fournode.erase(fournode.begin());
				score1 += 300;
			}
			else if (abs(btn->getPositionY() - fournode.at(0)->getPositionY()) > 60)
			{
				auto p = Sprite::create("s_miss.png");
				p->setPosition(winSize.width*.8f, winSize.height / 2);
				p->setScale(2.5f);
				this->addChild(p);

				MoveTo* move1 = MoveTo::create(.3f, winSize / 2);
				MoveTo* move2 = MoveTo::create(.1f, Vec2(winSize.width / 2, winSize.height*.55f));
				FadeOut* fade = FadeOut::create(.1f);
				Spawn* span = Spawn::create(move2, fade, NULL);
				Sequence* seq = Sequence::create(move1, span, NULL);
				p->runAction(seq);

				this->removeChild(fournode.at(0));
				fournode.erase(fournode.begin());
				lad->setPercent(score -= 2);
			}
			Score->setString(StringUtils::format("Score%d", score1));
		}
		break;
	default:
		break;
	}
}