#include "Plate.h"

bool Plate::init(const char * fileName)
{
	if (!Obj::init(fileName))
	{
		return false;
	}

	const Size halfSize = _sprite->getContentSize() * (0.5f / Singleton::PTM_RATIO);
	b2PolygonShape shape;
	shape.SetAsBox(halfSize.width, halfSize.height);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	PlateFixture = body->CreateFixture(&fixtureDef);
	PlateFixture->SetUserData(reinterpret_cast<void*>(7));

	return true;
}

void Plate::Press()
{
	//Running Animation
}

void Plate::update()
{
	Singleton::getInstance()->setInteractor(false);

	for (b2ContactEdge* fixtureUserdata = body->GetContactList(); fixtureUserdata != nullptr; fixtureUserdata = fixtureUserdata->next)
	{
		b2Fixture* fixture;
		b2BodyType Sensor;
		b2Fixture* fixtures[] = { fixtureUserdata->contact->GetFixtureA() , fixtureUserdata->contact->GetFixtureB() };

		int i;
		for (i = 0; i < 2; i++)
		{
			if (fixtures[i] == PlateFixture)
			{
				fixture = fixtures[1 - i];
				break;
			}
		}

		if (i == 2)
		{
			continue;
		}

		Sensor = reinterpret_cast<b2BodyType>(fixture->GetBody()->GetType());

		if (Sensor == b2_dynamicBody)
		{
			Singleton::getInstance()->setInteractor(true);
		}
	}
}