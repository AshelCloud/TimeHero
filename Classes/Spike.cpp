#include "Spike.h"

bool Spike::init(const char * fileName,b2BodyType bodyType)
{
	if (!Obj::init(fileName, bodyType))
	{
		return false;
	}

	Sequence* blink = Sequence::create(FadeOut::create(1.f), FadeIn::create(1.f), nullptr);

	_Light = Sprite::create("Obj/Objects/Thron/Obj_Thron_Light.png");
	_Light->setPosition(_sprite->getContentSize().width / 2.f, _sprite->getContentSize().height / 2.f);
	_sprite->addChild(_Light, -1);
	_Light->runAction(Repeat::create(blink, 999999));

	setUpSensor(userData);

	return true;
}

void Spike::setLight(const char* fileName)
{
	Sequence* blink = Sequence::create(FadeOut::create(1.f), FadeIn::create(1.f), nullptr);
	_Light = Sprite::create(fileName);
	_Light->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);
	this->getSprite()->addChild(_Light, -1);
	_Light->runAction(Repeat::create(blink, 999999));
}

Spike::Spike() : userData(8)
{
}

Spike::~Spike()
{
}
