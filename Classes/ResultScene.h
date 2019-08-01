#pragma once

#include "cocos2d.h"
#include "Singleton.h"
#include "MainScene.h"

using namespace cocos2d;

class ResultScene : public cocos2d::Layer
{
private:
	Size winSize;
	LayerColor* Opacity;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(ResultScene);
};
