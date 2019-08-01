#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "LogoScene.h"
#include "StartScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LogoScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LogoScene::create();

	scene->addChild(layer);

	return scene;
}

bool LogoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);//터치 활성화
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//터지모드 설정  한번 눌르면

	auto sprite = Sprite::create("Map/BackGround/Logo.png");
	sprite->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(sprite, 1);
	sprite->setOpacity(0);

	auto blinkSequence = Sequence::create(FadeIn::create(1.0f), nullptr);
	sprite->runAction(blinkSequence);

	schedule(schedule_selector(LogoScene::turnscene), 2, 100000000, 0);

	return true;
}

void LogoScene::turnscene(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
	Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::createScene(), Color3B(0, 0, 0)));
}

bool LogoScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void LogoScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void LogoScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}