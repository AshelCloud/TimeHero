#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "GameScene.h"
#include "Singleton.h"

#pragma execution_character_set("utf-8")
using namespace CocosDenshion;
using namespace cocos2d;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}
/////////////////////////////////////////////////////////////////////////////////
//
//	�ΰ� ȭ�� �ۼ�
//
//
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	//## ��ġ Ȱ��ȭ
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	Win_Size = Director::getInstance()->getVisibleSize();	//ȭ�� ������


    return true;
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * unused_event)
{
	Director::getInstance()->replaceScene(GameScene::createScene());

	return true;
}

void HelloWorld::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void HelloWorld::onTouchEnded(Touch * touch, Event * unused_event)
{
}
