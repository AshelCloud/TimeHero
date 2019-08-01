#pragma once

#include "cocos2d.h"
#include "Object.h"

class Spike : public Obj
{
private:
	const int userData;
	Sprite* _Light;

public:
	virtual bool init(const char* fileName, b2BodyType bodyType = b2_kinematicBody);
	void setLight(const char* fileName);
	Spike();
	~Spike();
};