#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Singleton.h"

using namespace cocos2d;

class Obj
{
public:
	b2Body* getBody() const;
	Sprite* getSprite() const;

protected:
	const Size winSize;
	b2Body* body;
	b2World* world;
	Sprite* _sprite;
	Vec2 Position;

	b2Fixture* setUpSensor(int userData);

public:
	virtual bool init(const char* FileName = nullptr, b2BodyType bodyType = b2_staticBody);
	const Vec2& getPosition();
	void setPosition(const Vec2& Pos);
	void setPosition(const Vec2 & Pos, Node * parent);

	Obj();
	~Obj();
};