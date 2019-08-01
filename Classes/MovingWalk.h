#pragma once

#include "cocos2d.h"
#include "Object.h"
#include "Plate.h"

using namespace cocos2d;

class MovingWalk : public Obj
{
private:
	int UserData;
	b2Vec2 LinearVelocity;
	Vec2 EarlyPosition;
	b2Fixture* MovingWalkfixture;
public:
	virtual bool init(const char* fileName);
	void setVelocity(const b2Vec2& Linear);
	void setUserData(int data);
	void* getUserData();

	void update();
	
	MovingWalk(): UserData(12) {}
	~MovingWalk() {}
};