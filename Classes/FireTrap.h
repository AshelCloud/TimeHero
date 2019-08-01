#pragma once

#include "cocos2d.h"
#include "Object.h"

using namespace cocos2d;

class FireTrap : public Obj
{
private:
	bool Alive = true;
	b2Fixture* FireTrapFixture;

public:
	virtual bool init(const char* fileName = "Obj/Objects/Obj_Fire.png");
	void setAlive(bool life);
	bool getAlive() const;

	FireTrap() {}
	~FireTrap() {}
};