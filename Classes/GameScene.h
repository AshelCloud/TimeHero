#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Match.h"
#include "Plant.h"
#include "Wall.h"
#include "Stone.h"
#include "Portal.h"
#include "Spike.h"
#include "Plate.h"
#include "Ladder.h"
#include "MovingWalk.h"
#include "FireTrap.h"
#include "SandBag.h"
#include "Box2d/Box2D.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
private:
	Size Win_Size;
#pragma region Object
	Player* player;
	Player* player_past;
	Match* match;
	Plant** plant;
	Wall** GroundWall;
	Wall** wall;
	Stone* Rock;
	Portal* portal;
	Spike** spike;
	Plate* plate;
	Ladder* ladder;
	Ladder* _ladder;
	MovingWalk* movingwalk;
	MovingWalk* _movingwalk;
	FireTrap* firetrap;
	FireTrap* _firetrap;
	SandBag* sandbag;
#pragma endregion
#pragma region Layer
	Layer* Map_BackGround_Now;
	Layer* Map_BackGround_Past;
	Layer* UI_Layer;
	Layer* Overlap_Layer;
	Layer* Game_Layer;
	LayerColor* Opacity_Layer;
	Layer* Help_Layer;
	Layer* Back_Layer;
#pragma endregion
#pragma region Variable
	Sequence* Bright;
	Sprite* Time_Button;
	Sprite* Jump_Button;
	Sprite* JumpBright;
	Sprite* ToolBright;
	Sprite* TimeBright;
	Sprite* ToolButton;
	int spikeCnt;
	int wallCount;
	int ladderCount;
	int plantCount;
	int fireCount;
	int off;
	int num;
	int _num;
	int hour;
#pragma endregion
	Camera* camera;
	Rect mapSize;
	b2World* _world;
	bool Time_State;
	b2WeldJointDef weldjoint;
	Sprite* mt;
	Sprite* sb;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void Game_Init();
	void Player_Init();
	~GameScene();
	void ButtonInit();
	void update(float dt);
	void createUI();
	void CreateGroundWall(const int count);
	void CreateCastleWall(const int count, const Vec2 &Pos);
	void CreatefilledWall(const int count, const Vec2 &Pos);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(GameScene);
};

