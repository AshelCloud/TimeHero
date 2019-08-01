#include "MovingWalk.h"

bool MovingWalk::init(const char * fileName)
{
	if (!Obj::init(fileName, b2_kinematicBody))
	{
		return false;
	}

	Size halfSize = _sprite->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height - (15.f / Singleton::PTM_RATIO));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	MovingWalkfixture = body->CreateFixture(&fixtureDef);
	MovingWalkfixture->SetUserData(reinterpret_cast<void*>(UserData));

	EarlyPosition = this->getSprite()->getPosition();

	return true;
}

void MovingWalk::setVelocity(const b2Vec2& Linear)
{
	LinearVelocity = Linear;
}

void MovingWalk::setUserData(int data)
{
	UserData = data;
}

void* MovingWalk::getUserData()
{
	return MovingWalkfixture->GetUserData();
}

void MovingWalk::update()
{
	if (Singleton::getInstance()->getInteractor())
	{
		body->SetLinearVelocity(LinearVelocity);
	}
	else
	{
		if (this->getSprite()->getPosition().y > EarlyPosition.y)
			body->SetLinearVelocity(b2Vec2(-LinearVelocity));
		else
			body->SetLinearVelocity(b2Vec2(0.f, 0.f));
	}
}