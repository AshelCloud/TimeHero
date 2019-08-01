#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Plant.h"
#include "Match.h"
#include "Object.h"
#include "ResultScene.h"

using namespace cocos2d;

class Player : public Obj
{
public:
	Sprite* get_Light() const;

private:
	int direction;
	int jumpTimeout;
	int ItemStatus;
	bool moving;
	bool fakeContacting;
	bool jumping;
	bool hanging;
	Sprite* _Light;
	Animate* idleAnimate;
	Animate* ladderAnimate;
	Animate* jumpAnimate;
	Animate* ThrowAnimate;
	Animate* MoveAnimate;

public:
	bool contacting;
	virtual bool init(const char* fileName = "Charactor/Character.png");
	void AnimationInit();
	void update();
	void Idle();
	void move(int directionParam);
	void Jump();
	bool Take();
	void HangOn(int directionParam);
	std::vector<int> Use();
	bool IsFlipX();
	void setFilpX(bool fliedX);
	void setItemStatus(int Status);
	int getItemStatus();
	bool getToolState();
	bool getContacting() const;
	bool getHanging();
	void Throwing() const;
	b2Fixture* bodyFixture;
	b2Fixture* footSensorFixture;

	Player();
	~Player();
};