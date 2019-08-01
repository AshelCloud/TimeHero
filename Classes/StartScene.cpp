#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "MainScene.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getVisibleSize();
	this->setTouchEnabled(true);//터치 활성화
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//터지모드 설정  한번 눌르면

	auto sprite = Sprite::create("Logo/Start.png");
	sprite->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(sprite, 10);

	auto title = Sprite::create("Logo/Logo_Game.png");
	title->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
	this->addChild(title, 20);

	auto opacity = FadeTo::create(2.0f, 50);
	auto scale_small = ScaleBy::create(2.0f, 0.7f);

	auto fade_seq = Sequence::create(opacity, nullptr);
	sprite->runAction(fade_seq);

	auto scale_seq = Sequence::create(scale_small, nullptr);
	title->runAction(scale_seq);

	auto start_label = Sprite::create("Logo/Logo_Game_02.png");
	start_label->setPosition(winSize.width * 0.5f, winSize.height * 0.2f);
	FadeIn * _fadein = FadeIn::create(1.f);    // 시간       
	FadeOut * _fadeout = FadeOut::create(1.f);    // 시간
	auto Blink_Sequence = Sequence::create(_fadein, _fadeout, nullptr);

	auto delay2 = DelayTime::create(3.0f);
	auto hide = Hide::create();
	auto show = Show::create();
	auto hs_seq = Sequence::create(hide, delay2, show, nullptr);
	start_label->runAction(hs_seq);

	start_label->runAction(RepeatForever::create(Blink_Sequence));
	this->addChild(start_label, 1);

	return true;
}

bool StartScene::onTouchBegan(Touch *touch, Event*unused_event)//닿은 시점 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene(), Color3B(0, 0, 0)));
	return true;
}