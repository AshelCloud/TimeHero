#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Object.h"

using namespace cocos2d;

class Plant : public Obj
{
private:
	int UserData;
	b2Fixture* PlantUseFixture;
	Sprite* _Light;
public:
	virtual bool init(const char* FileName);
	void setUserData(int Data);
	void* getUserData();
	void setLight(const char* fileName);
	void fire() const;
	Plant();
	~Plant();
};