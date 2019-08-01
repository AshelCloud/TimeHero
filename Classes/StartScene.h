#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class StartScene : public cocos2d::Layer
{
private:
	Size winSize;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event*unused_event);
    CREATE_FUNC(StartScene);
};