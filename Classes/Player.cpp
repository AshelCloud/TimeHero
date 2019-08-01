#include "Player.h"
#include "Singleton.h"

using namespace cocos2d;

bool Player::init(const char* fileName)
{
	if (!Obj::init(fileName, b2_dynamicBody))
	{
		return false;
	}

	//variable initialize
	jumpTimeout = 0;
	ItemStatus = 0;

	//sprite initialize
	_Light = Sprite::create("Charactor/_Light.png");
	_Light->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);
	_sprite->addChild(_Light, -1);

	const Size halfSize = _sprite->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;

	const size_t numPoints = 6;
	const b2Vec2 points[numPoints] =
	{
		b2Vec2(-halfSize.width, halfSize.height), b2Vec2(halfSize.width, halfSize.height),
		b2Vec2(halfSize.width, -halfSize.height * 0.799f), b2Vec2(halfSize.width * 0.998f, -halfSize.height * 0.8f),
		b2Vec2(-halfSize.width * 0.998f, -halfSize.height * 0.8f), b2Vec2(-halfSize.width, -halfSize.height * 0.799f)
	};

	shape.Set(points, numPoints);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	bodyFixture = body->CreateFixture(&fixtureDef);

	shape.SetAsBox((halfSize.width / 1.5f), (0.5f / Singleton::PTM_RATIO) , b2Vec2(0, -halfSize.height + (50.f / Singleton::PTM_RATIO)), 0);
	fixtureDef.isSensor = true;
	footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)0);
	
	body->SetFixedRotation(true);

	Singleton::getInstance()->getContactListener()->getOnBeginContacts().push_back(
		[this](b2Contact* contact) -> void
	{
		if (contacting == true) { return; }

		b2Fixture* fixtures[2] = { contact->GetFixtureA(), contact->GetFixtureB() };
		for (int i = 0; i < 2; i++)
		{
			if (reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4 && fixtures[1 - i] == bodyFixture)
			{
				fakeContacting = true;
				break;
			}
		}
	});

	Singleton::getInstance()->getContactListener()->getOnEndContacts().push_back(
		[this](b2Contact* contact) -> void
	{
		b2Fixture* fixtures[2] = { contact->GetFixtureA(), contact->GetFixtureB() };
		for (int i = 0; i < 2; i++)
		{
			if (reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4 && fixtures[1 - i] == bodyFixture)
			{
				if (contacting == true)
				{
					_sprite->scheduleOnce([this](float)
					{
						bodyFixture->SetSensor(false);
						body->SetGravityScale(1.f);
						contacting = false;
					}, 0.f, "onEndContact");
				}

				fakeContacting = false;
				return;
			}
		}
	});

	Player::AnimationInit();

	return true;
}

void Player::AnimationInit()
{
	Animation* stopanimate = Animation::create();
	stopanimate->setDelayPerUnit(0.35f);

	for (int i = 1; i < 4; i++)
	{
		stopanimate->addSpriteFrameWithFileName(StringUtils::format("Animate/Idle/%d.png", i));
	}

	idleAnimate = Animate::create(stopanimate);
	idleAnimate->retain();

	_sprite->runAction(RepeatForever::create(idleAnimate->clone()));

	Animation*ladderanimation = Animation::create();
	ladderanimation->setDelayPerUnit(0.25f);
	for (int j = 1; j < 5; j++)
	{
		ladderanimation->addSpriteFrameWithFileName(StringUtils::format("Animate/Ladder/%d.png", j));
	}

	ladderAnimate = Animate::create(ladderanimation);
	ladderAnimate->retain();

	Animation* jumpanimation = Animation::create();
	jumpanimation->setDelayPerUnit(0.2f);
	for (int j = 1; j < 7; j++)
	{
		jumpanimation->addSpriteFrameWithFileName(StringUtils::format("Animate/Jump/%d.png", j));
	}

	jumpAnimate = Animate::create(jumpanimation);
	jumpAnimate->retain();

	Animation* throwanimation = Animation::create();
	throwanimation->setDelayPerUnit(0.25f);
	for (int j = 1; j < 4; j++)
	{
		throwanimation->addSpriteFrameWithFileName(StringUtils::format("Animate/Throw/%d.png", j));
	}

	ThrowAnimate = Animate::create(throwanimation);
	ThrowAnimate->retain();

	Animation* MoveAnimation = Animation::create();
	MoveAnimation->setDelayPerUnit(0.2f);
	for (int j = 1; j < 7; j++)
	{
		MoveAnimation->addSpriteFrameWithFileName(StringUtils::format("Animate/Run/%d.png", j));
	}

	MoveAnimate = Animate::create(MoveAnimation);
	MoveAnimate->retain();
}

void Player::update()
{
	//##사망해라
	if (this->getSprite()->getPosition().y <= 0.f)
		Director::getInstance()->replaceScene(ResultScene::createScene());

	//## Jump Count 감소
	if (jumpTimeout > 0) { jumpTimeout--; }

	//## Move
	b2Vec2 vel = body->GetLinearVelocity();
	float desiredVel = 0;

	if (contacting)
	{
		if (moving)
		{
			if (direction == 2)
			{
				_sprite->setFlippedX(true);
				body->SetLinearVelocity(b2Vec2(0.f, -100.f / Singleton::PTM_RATIO));
			}
			else if (direction == 3)
			{
				_sprite->setFlippedX(false);
				body->SetLinearVelocity(b2Vec2(0.f, 100.f / Singleton::PTM_RATIO));
			}
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0.f, 0.f));
		}
	}
	else
	{
		if (moving)
		{
			if (direction == 0)//왼
			{
				_sprite->setFlippedX(true);
				desiredVel = b2Max(vel.x - 0.1f, -5.0f);
			}
			else if (direction == 1)//우
			{
				_sprite->setFlippedX(false);
				desiredVel = b2Min(vel.x + 0.1f, 5.0f);
			}
		}
	}

	if (moving == false)
	{
		desiredVel = vel.x * 0.98f;
	}

	float velChange = desiredVel - vel.x;
	float impulse = body->GetMass() * velChange;

	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);

	for (b2ContactEdge* fixtureUserdata = body->GetContactList(); fixtureUserdata != nullptr; fixtureUserdata = fixtureUserdata->next)
	{
		b2Fixture* fixture;
		int UserTag;
		b2Fixture* fixtures[] = { fixtureUserdata->contact->GetFixtureA() , fixtureUserdata->contact->GetFixtureB() };

		int i;
		for (i = 0; i < 2; i++)
		{
			if (fixtures[i] == footSensorFixture)
			{
				fixture = fixtures[1 - i];
				break;
			}
		}

		if (i == 2)
		{
			continue;
		}

		UserTag = reinterpret_cast<int>(fixture->GetUserData());

		switch (UserTag)
		{
		case 8:
			log(" (die!) ");
			Director::getInstance()->replaceScene(ResultScene::createScene());
			break;
		case 11:
			Singleton::getInstance()->setClear(true);
			Director::getInstance()->replaceScene(ResultScene::createScene());
			break;
		case 14:
			Director::getInstance()->replaceScene(ResultScene::createScene());
			break;
		}
	}
}

void Player::Idle()
{
	moving = false;

	if (!contacting)
	{
		_sprite->stopAllActions();
	
		_sprite->runAction(RepeatForever::create(idleAnimate));
	}
}

void Player::move(int directionParam)
{
	_sprite->stopAllActions();
	_sprite->runAction(RepeatForever::create(MoveAnimate));

	direction = directionParam;
	moving = true;
}

void Player::Jump()
{
	if (fakeContacting)
	{
		bodyFixture->SetSensor(true);
		body->SetGravityScale(0.f);
		body->SetLinearVelocity(b2Vec2(0.f, 0.f));
		contacting = true;
		fakeContacting = false;
	}
	else
	{
		for (b2ContactEdge * fixtureUserData = body->GetContactList();
			fixtureUserData != nullptr; fixtureUserData = fixtureUserData->next)
		{
			b2Fixture * fixture;
			int UserTag;
			b2Fixture* fixtures[] = { fixtureUserData->contact->GetFixtureA(),
				fixtureUserData->contact->GetFixtureB() };
			int i;
			for (i = 0; i < 2; i++)
			{
				if (fixtures[i]->GetUserData() == 0)
				{
					fixture = fixtures[1 - i];
					if (fixture->IsSensor() || !fixture->GetBody()->IsActive()) { continue; }
					break;
				}
			}

			if (i == 2)
			{
				continue;
			}
			UserTag = 0;

			if ((UserTag == 0 || UserTag == 99) && jumpTimeout == 0)
			{
				float impulse = body->GetMass() * 7.5f;
				_sprite->stopAllActions();
				auto Sequence = Sequence::create(
					Spawn::create(jumpAnimate, CallFunc::create([=]() -> void
				{ body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true); }), nullptr), idleAnimate,
					CallFunc::create([&]() -> void { this->Idle(); }), nullptr);

				_sprite->runAction(Repeat::create(Sequence, 1));
				
				jumpTimeout = 50;
				break;
			}
		}
	}
}

bool Player::Take()
{
	if (ItemStatus != 0)
		return false;

	//## 아이템 흭득 연산
	for (b2ContactEdge* fixtureUserdata = body->GetContactList(); fixtureUserdata != nullptr; fixtureUserdata = fixtureUserdata->next)
	{
		b2Fixture* fixture;
		int UserTag;
		b2Fixture* fixtures[] = { fixtureUserdata->contact->GetFixtureA() , fixtureUserdata->contact->GetFixtureB() };
		
		int i;
		for (i = 0; i < 2; i++)
		{
			if (fixtures[i] == footSensorFixture)
			{
				fixture = fixtures[1 - i];
				break;
			}
		}

		if (i == 2)
		{
			continue;
		}

		UserTag = reinterpret_cast<int>(fixture->GetUserData());

		//	플레이어 = 0
		//	바닥 = 1
		//	식물 = 2
		//	성냥 = 3
		//	사다리 = 4
		switch (UserTag)
		{
		case 3:
			ItemStatus = 3;
			return true;
		case 13:
			ItemStatus = 13;
			return true;
		default:
			continue;
		}
	}
	return false;
}

std::vector<int> Player::Use()
{
	std::vector<int> UserTagset;
	int cnt = 0;

	for (b2ContactEdge* fixtureUserdata = body->GetContactList(); fixtureUserdata != nullptr; fixtureUserdata = fixtureUserdata->next)
	{
		b2Fixture* fixture;
		int UserTag;
		b2Fixture* fixtures[] = { fixtureUserdata->contact->GetFixtureA() , fixtureUserdata->contact->GetFixtureB() };

		int i;
		for (i = 0; i < 2; i++)
		{
			if (fixtures[i] == footSensorFixture)
			{
				fixture = fixtures[1 - i];
				break;
			}
		}

		if (i == 2)
		{
			continue;
		}

		UserTag = reinterpret_cast<int>(fixture->GetUserData());
		if (UserTag >= 20)	cnt++;
		UserTagset.push_back(UserTag);
	}
	return UserTagset;
}

void Player::Throwing() const
{
	_sprite->stopAllActions();
	auto Throwing = Sequence::create(ThrowAnimate, RepeatForever::create(idleAnimate), nullptr);
	_sprite->runAction(Throwing);
}

bool Player::IsFlipX()
{
	return _sprite->isFlippedX();
}

void Player::setFilpX(bool fliedX)
{
	_sprite->setFlippedX(fliedX);
}

void Player::setItemStatus(int Status)
{
	ItemStatus = Status;
}

int Player::getItemStatus()
{
	return ItemStatus;
}

bool Player::getToolState()
{
	//Having Item return true
	if(ItemStatus != 0)	return true;
	else return false;
}

bool Player::getContacting() const
{
	return contacting;
}

bool Player::getHanging()
{
	return hanging;
}

Sprite * Player::get_Light() const
{
	return _Light;
}

Player::Player() :
	jumping(false), moving(false), contacting(false), fakeContacting(false)
{
}

Player::~Player()
{
	CC_SAFE_RELEASE_NULL(idleAnimate);
	CC_SAFE_RELEASE_NULL(ladderAnimate);
}

void Player::HangOn(int directionParam)
{
	direction = directionParam;

	_sprite->stopAllActions();
	_sprite->runAction(RepeatForever::create(ladderAnimate));

	moving = true;
}
