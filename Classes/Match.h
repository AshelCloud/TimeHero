#pragma once

#include "cocos2d.h"
#include "Box2d/Box2D.h"
#include "Object.h"

using namespace cocos2d;

class Match : public Obj
{
private:
	b2Fixture* MatchFixture;
	const int UserData;
	Sprite* _Light;
public:
	virtual bool init(const char* fileName = "Obj/Objects/Match/Obj_Match.png");

	Match();
	~Match();
};