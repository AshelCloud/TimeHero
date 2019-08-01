#include "Ladder.h"

Ladder::Ladder():
	part(nullptr)
{
}

Ladder::~Ladder()
{
	if (part != nullptr)
	{
		delete[] part;
		part = nullptr;
	}
}

bool Ladder::init(int laddernum)
{
	this->setName("object_ladder");

	Size Win_Size = Director::getInstance()->getVisibleSize();

	ladder = Sprite::create("Obj/Objects/Ladder/Ladder.png",Rect(0,0,32,laddernum*44));
	ladder->setOpacity(0);
	ladder->setPosition(LadderPostion + Vec2(0, 22 * laddernum));

	part = new Sprite*[laddernum];

	for (int i = 0; i < laddernum; i++)
	{
		if (i == laddernum - 1)
		{
			part[i] = Sprite::create("Obj/Objects/Ladder/Ladder_On.png");
			part[i]->setPosition(Win_Size.width*0.01f, (Win_Size.height*0.03f) + Win_Size.height*0.06f*i);
			ladder->addChild(part[i]);
		}
		else
		{
			part[i] = Sprite::create("Obj/Objects/Ladder/Ladder_Mid.png");
			part[i]->setPosition(Win_Size.width*0.01f, (Win_Size.height*0.03f) + Win_Size.height*0.06f*i);
			ladder->addChild(part[i]);
		}
	}
	
	world = Singleton::getInstance()->getWorld();

	const Vec2 physPos = ladder->getPosition() / Singleton::PTM_RATIO;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(physPos.x, physPos.y);
	bodyDef.userData = reinterpret_cast<void*>(ladder);
	body = world->CreateBody(&bodyDef);

	const Size TwiceSize = ladder->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(TwiceSize.width, TwiceSize.height);

	b2FixtureDef UsefixtureDef;
	UsefixtureDef.shape = &shape;
	UsefixtureDef.userData = ((void*)4);
	UsefixtureDef.isSensor = true;
	ladderFixture = body->CreateFixture(&UsefixtureDef);

	shape.SetAsBox((TwiceSize.width / 2), (0.5f / Singleton::PTM_RATIO), b2Vec2(0, +TwiceSize.height), 0);

	UsefixtureDef.isSensor = false;
	LadderSensorFixture = body->CreateFixture(&UsefixtureDef);
	LadderSensorFixture->SetUserData((void*)99);
	
	return true;
}

void Ladder::setLadderPosition(Vec2 Pos)
{
	LadderPostion = Pos;
}

Sprite * Ladder::getSprite() const
{
	return ladder;
}

b2Body* Ladder::getBody() const
{
	return body;
}