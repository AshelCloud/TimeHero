#include "Portal.h"

bool Portal::init(const char * FileName)
{
	if (!Obj::init(FileName))
	{
		return false;
	}

	setUpSensor(userData);

	Animation* PortalAnimation = Animation::create();
	PortalAnimation->setDelayPerUnit(0.2f);

	for (int i = 1; i < 9; i++)
	{
		PortalAnimation->addSpriteFrameWithFileName(StringUtils::format("Animate/Clear/%02d.png", i));
	}

	Animate* IdleAnimate = Animate::create(PortalAnimation);

	this->getSprite()->runAction(RepeatForever::create(IdleAnimate));

	return true;
}

Portal::Portal() : userData(11)
{
}

Portal::~Portal()
{
}
