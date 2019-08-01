#include "Match.h"
#include "Singleton.h"

bool Match::init(const char* fileName)
{
	if (!Obj::init(fileName))
	{
		return false;
	}

	Sequence* blink = Sequence::create(FadeOut::create(1.f), FadeIn::create(1.f), nullptr);
	_Light = Sprite::create("Obj/Objects/Match/Obj_Match_Light.png");
	_Light->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);
	this->getSprite()->addChild(_Light, -1);
	_Light->runAction(RepeatForever::create(blink));

	setUpSensor(UserData);

	return true;
}

Match::Match():UserData(3) {}

Match::~Match() {}