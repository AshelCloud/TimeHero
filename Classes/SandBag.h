#pragma once

#include "cocos2d.h"
#include "Object.h"

using namespace cocos2d;

class SandBag : public Obj
{
private:
	Sprite* _Light;

public:
	virtual bool init(const char* fileName = "Obj/Objects/Sandbag/Obj_Sandbag.png");

	SandBag() {}
	~SandBag() {}
};