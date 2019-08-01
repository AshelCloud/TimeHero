#pragma once

#include "cocos2d.h"
#include "Object.h"

class Stone : public Obj
{
private:

public:
	virtual bool init(const char* fileName = "Obj/Objects/Obj_Rock.png");

	Stone();
	~Stone();
};