#include "Wall.h"

bool Wall::init(const char* fileName)
{
	if (!Obj::init(fileName))
	{
		return false;
	}

	const Size halfSize = _sprite->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height - (15.f / Singleton::PTM_RATIO));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	return true;
}

bool Wall::init(const char* fileName, int _stage, int _count)
{
	world = Singleton::getInstance()->getWorld();

	_sprite = Sprite::create();
	_sprite->setPosition(Position);
	_sprite->setUserData(reinterpret_cast<void*>(this));
	_sprite->setUserObject(user_object_t::create(this));

	switch (_stage)
	{
	case 2:
		{
			Sprite* spr = nullptr;
			spr = Sprite::create("Obj/Wall/Stage_02/BG_Ground_2_01.png");
			spr->setAnchorPoint(Vec2(0, 0));
			spr->setPosition(Vec2(_sprite->getContentSize().width, 0));
			_sprite->addChild(spr);
			_sprite->setContentSize(Size(_sprite->getContentSize().width + spr->getContentSize().width, spr->getContentSize().height));
			for (int i = 0; i < _count; i++)
			{
				spr = Sprite::create("Obj/Wall/Stage_02/BG_Ground_2_02.png");
				spr->setAnchorPoint(Vec2(0, 0));
				spr->setPosition(Vec2(_sprite->getContentSize().width, 0));
				_sprite->addChild(spr);
				_sprite->setContentSize(Size(_sprite->getContentSize().width + spr->getContentSize().width, spr->getContentSize().height));
			}
			spr = Sprite::create("Obj/Wall/Stage_02/BG_Ground_2_03.png");
			spr->setAnchorPoint(Vec2(0, 0));
			spr->setPosition(Vec2(_sprite->getContentSize().width, 0));
			_sprite->addChild(spr);
			_sprite->setContentSize(Size(_sprite->getContentSize().width + spr->getContentSize().width, spr->getContentSize().height));
		}
		break;
	}

	const Vec2 physPos = ( _sprite->getPosition() + Vec2(_sprite->getContentSize().width * 0.5, _sprite->getContentSize().height * -0.5) ) / Singleton::PTM_RATIO;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(physPos.x, physPos.y);
	bodyDef.userData = reinterpret_cast<void*>(_sprite);
	body = world->CreateBody(&bodyDef);

	const Size halfSize = (_sprite->getContentSize() - Size(0, 30)) * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	return true;
}

Wall::Wall() : Userdata(5) {}

Wall::~Wall() {}
