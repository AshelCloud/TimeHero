#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Object.h"

using namespace cocos2d;

class user_object_t : public Node
{
private:
	Obj* Owner;

public:
	static user_object_t* create(Obj* owner)
	{
		user_object_t* object = new(std::nothrow) user_object_t(owner);
		if (object != nullptr && object->init())
		{
			object->autorelease();
			return object;
		}

		return nullptr;
	}

	user_object_t(Obj* owner) : Owner(owner) {}

	virtual ~user_object_t()
	{
		delete Owner;
	}
};

class Wall : public Obj
{
private:
	b2Fixture* WallFixture;
	int Userdata;
public:
	virtual bool init(const char* fileName);
	bool init(const char* fileName, int _stage, int _count = 1);

	Wall();
	~Wall();
};