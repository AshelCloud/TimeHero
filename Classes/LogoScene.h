#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class LogoScene : public cocos2d::Layer
{
private:
	Size winSize;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void turnscene(float dt);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(LogoScene);
};