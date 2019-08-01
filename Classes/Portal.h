#pragma once

#include "cocos2d.h"
#include "Object.h"

class Portal : public Obj
{
private:
	const int userData;
public:
	virtual bool init(const char* FileName = "Obj/Objects/Portal.png");

	Portal();
	~Portal();
};