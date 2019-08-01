#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Object.h"

class Plate : public Obj
{
public:
	bool Interaction;

private:
	b2Fixture* PlateFixture;

public:

	virtual bool init(const char* fileName = "Obj/Objects/Obj_Foot_hold.png");
	void Press();
	void update();

	Plate(): Interaction(false) {}
	~Plate() {}
};