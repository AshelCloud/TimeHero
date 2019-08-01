#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Singleton.h"

using namespace cocos2d;

class Ladder : public Sprite
{
private:
	const Size winSize;
	Vec2 LadderPostion;
	b2Body * body;
	b2World * world;
	b2Fixture* ladderFixture;
	b2Fixture * LadderUseFixture;
	b2Fixture * LadderSensorFixture;
	Sprite* ladder;
	Sprite ** part;
public:
	Ladder();
	virtual ~Ladder();
	
	bool init(int laddernum);
	
	void setLadderPosition(Vec2 Pos);
	Sprite* getSprite() const;
	b2Body * getBody() const;
};