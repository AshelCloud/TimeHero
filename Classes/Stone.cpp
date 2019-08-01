#include "Stone.h"


bool Stone::init(const char * fileName)
{
	if (!Obj::init(fileName, b2_dynamicBody))
	{
		return false;
	}

	const Size halfSize = _sprite->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height - (15.f / Singleton::PTM_RATIO));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 5.f;
	body->CreateFixture(&fixtureDef);

	body->SetFixedRotation(true);

	return true;
}

Stone::Stone() {}

Stone::~Stone() {}
