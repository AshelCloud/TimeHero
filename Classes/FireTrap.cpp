#include "FireTrap.h"

bool FireTrap::init(const char * fileName)
{
	if (!Obj::init(fileName))
	{
		return false;
	}
	
	setUpSensor(14);

	const Size OneHalfSize = _sprite->getContentSize() * (1.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(OneHalfSize.width, OneHalfSize.height / 3);

	b2FixtureDef UsefixtureDef;
	UsefixtureDef.shape = &shape;
	UsefixtureDef.isSensor = true;
	FireTrapFixture = body->CreateFixture(&UsefixtureDef);
	FireTrapFixture->SetUserData((void*)21);

	Animation* FireAnimation = Animation::create();
	FireAnimation->setDelayPerUnit(0.2f);

	for (int i = 0; i < 3; i++)
	{
		FireAnimation->addSpriteFrameWithFileName(StringUtils::format("Animate/FireTrap/Obj_Fire_%02d.png", i));
	}

	Animate* IdleAnimate = Animate::create(FireAnimation);

	this->getSprite()->runAction(RepeatForever::create(IdleAnimate));

	return true;
}

void FireTrap::setAlive(bool life)
{
	if (life == false)
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->setTexture("Obj/Objects/Obj_Fire_04.png");
		body->SetActive(false);
	}
	else
	{
		Animation* FireAnimation = Animation::create();
		FireAnimation->setDelayPerUnit(0.2f);

		for (int i = 0; i < 3; i++)
		{
			FireAnimation->addSpriteFrameWithFileName(StringUtils::format("Animate/FireTrap/Obj_Fire_%02d.png", i));
		}

		Animate* IdleAnimate = Animate::create(FireAnimation);

		this->getSprite()->runAction(RepeatForever::create(IdleAnimate));

		body->SetActive(true);
	}
}

bool FireTrap::getAlive() const
{
	return Alive;
}
