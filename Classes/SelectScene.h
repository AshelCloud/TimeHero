#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class SelectScene : public Layer
{
private:
	Size winSize;

	int num;
	int _num;

	Vec2 touchPos;
	Sprite * Option_button;
	Sprite * Bgm_button;
	Sprite * uiline;
	Sprite * uiline2;
	Sprite * Sfx_button;
	Sprite * close;
	Sprite * resume;

	Layer* Option;
	LayerColor* Opacity_Layer;
#pragma region Variable
	Sprite* Level_1;
	Sprite* Level_2;
	Sprite* Level_3;
	Sprite* Level_4;
	Sprite* Level_5;
	Vec2 beginningPos;
#pragma endregion
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(SelectScene);
};
