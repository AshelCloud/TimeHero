#include "Plant.h"
#include "Singleton.h"

bool Plant::init(const char* FileName)
{
	if (!Obj::init(FileName))
	{
		return false;
	}

	setUpSensor(UserData);

	if (UserData == 2 || UserData == 10)
	{
		const Size OneHalfSize = _sprite->getContentSize() * (1.5f / Singleton::PTM_RATIO);
		b2PolygonShape shape;
		shape.SetAsBox(OneHalfSize.width, OneHalfSize.height/3);

		b2FixtureDef UsefixtureDef;
		UsefixtureDef.shape = &shape;
		UsefixtureDef.isSensor = true;
		PlantUseFixture = body->CreateFixture(&UsefixtureDef);
		PlantUseFixture->SetUserData((void*)20);
	}

	return true;
}

void Plant::setUserData(int Data)
{
	UserData = Data;
}

void * Plant::getUserData()
{
	return PlantUseFixture->GetUserData();
}

void Plant::setLight(const char* fileName)
{
	Sequence* blink = Sequence::create(FadeOut::create(1.f), FadeIn::create(1.f), nullptr);
	_Light = Sprite::create(fileName);
	_Light->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);
	this->getSprite()->addChild(_Light, -1);
	_Light->runAction(Repeat::create(blink,999999));
}

void Plant::fire() const
{
	Animation*fire = Animation::create();
	fire->setDelayPerUnit(0.2f);
	for (int n = 1; n < 5; n++)
	{
		fire->addSpriteFrameWithFileName(StringUtils::format("Animate/Obj_Tree/%d.png", n));
	}
	auto fireanimation = Animate::create(fire);

	DelayTime*action_1 = DelayTime::create(2.0f);

	Sequence*fireburn = Sequence::create(action_1, fireanimation, nullptr);

	_Light->stopAllActions();
	_Light->setVisible(false);
	_sprite->runAction(Repeat::create(fireburn, 1));
}
Plant::Plant() {}

Plant::~Plant() {}
