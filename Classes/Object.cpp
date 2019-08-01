#include "Object.h"

b2Body * Obj::getBody() const
{
	return body;
}

Sprite * Obj::getSprite() const
{
	return _sprite;
}

b2Fixture* Obj::setUpSensor(int userData)
{
	const Size halfSize = _sprite->getContentSize() * (0.3f / Singleton::PTM_RATIO);

	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	if(userData != 9 && userData != 10)	fixtureDef.isSensor = true;
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);
	fixture->SetUserData(reinterpret_cast<void*>(userData));
	return fixture;
}

bool Obj::init(const char* FileName, b2BodyType bodyType)
{
	const Size viewSize = Director::getInstance()->getVisibleSize();
	world = Singleton::getInstance()->getWorld();

	_sprite = Sprite::create(FileName);
	_sprite->setPosition(Position);
	_sprite->setUserData(reinterpret_cast<void*>(this));  

	class user_object_t : public Node
	{
	private:
		Obj* Owner;

	public:
		static user_object_t* create(Obj* owner)
		{
			user_object_t* object = new(std::nothrow) user_object_t(owner);
			if (object != nullptr && object->init())
			{
				object->autorelease();
				return object;
			}

			return nullptr;
		}

		user_object_t(Obj* owner) : Owner(owner) {}

		virtual ~user_object_t()
		{
			delete Owner;
		}
	};

	_sprite->setUserObject(user_object_t::create(this));
	
	const Vec2 physPos = _sprite->getPosition() / Singleton::PTM_RATIO;
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(physPos.x, physPos.y);
	bodyDef.userData = reinterpret_cast<void*>(_sprite);
	body = world->CreateBody(&bodyDef);

	return true;
}

const Vec2 & Obj::getPosition()
{
	return _sprite->getPosition();
}

void Obj::setPosition(const Vec2 & Pos)
{
	Position = Pos;
}

void Obj::setPosition(const Vec2& Pos, Node* parent)
{
	Position = parent->convertToNodeSpaceAR(Pos);
}

Obj::Obj(): body(nullptr) {}

Obj::~Obj()
{
	if (body != nullptr)
	{
		world->DestroyBody(body);
		body = nullptr;
	}
}
