#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Layer
{
private:
	Sprite* Bgm_button;
	Size Win_Size;
	LayerColor* credit;
	LayerColor* Opacity_Layer;
	Sprite* Chapter_1;
	Sprite* Chapter_2;
	Sprite* ChapterLight;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void SelectScene();
	void Buttoninit();
	void creditinit();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

    CREATE_FUNC(MainScene);
};


