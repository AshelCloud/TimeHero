#include "Singleton.h"

Singleton* Singleton::inst = nullptr;

Singleton::Singleton():
	_ContactListener(nullptr)
{
	Size Win_Size = Director::getInstance()->getVisibleSize();

	//variable initialize
	numFootContacts = 0;
	MusicCheck = true;

	//World Create
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	_world = new b2World(gravity);

	_ContactListener = new ContactListener;
	_world->SetContactListener(_ContactListener);

	b2BodyDef screen_body_def;
	screen_body_def.position.Set(0.0f, 0.0f);
	b2Body* screen_body = _world->CreateBody(&screen_body_def);

	b2EdgeShape screen_edge;
	b2FixtureDef screen_fixture_def;
	screen_fixture_def.shape = &screen_edge;

	screen_edge.Set(b2Vec2(0.0f, 0.0f),
		b2Vec2(0, Win_Size.height / PTM_RATIO));
	screen_body->CreateFixture(&screen_fixture_def);
}

Singleton::~Singleton()
{
	CC_SAFE_DELETE(_world);
}

Singleton* Singleton::getInstance()
{
	if (inst == nullptr)
		inst = new Singleton();

	return inst;
}

void Singleton::ContactListener::BeginContact(b2Contact * contact)
{
	for (const on_contact_t& curBeginContact : OnBeginContacts)
	{
		curBeginContact(contact);
	}
}

void Singleton::ContactListener::EndContact(b2Contact * contact)
{
	for (const on_contact_t& curEndContact : OnEndContacts)
	{
		curEndContact(contact);
	}
}

void Singleton::ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	for (const on_pre_solve_t& curPreSolve : OnPreSolves)
	{
		curPreSolve(contact, oldManifold);
	}
}

void Singleton::setChapter(int ChapterParam)
{
	Chapter = ChapterParam;
}

void Singleton::setLevel(int LevelParam)
{
	Level = LevelParam;
}

void Singleton::setMusic(bool MusicParam)
{
	MusicCheck = MusicParam;
}

int Singleton::IsLevel()
{
	return Level;
}

int Singleton::IsChapter()
{
	return Chapter;
}

bool Singleton::isMusic()
{
	return MusicCheck;
}

void Singleton::setClear(bool ClearParam)
{
	Result = ClearParam;
}

bool Singleton::isClear()
{
	return Result;
}

void Singleton::setWhereClear(int ClearParam)
{
	whereClear = ClearParam;
}

int Singleton::isWhereClear()
{
	return whereClear;
}

void Singleton::setWhereChapter(int ChapterParam)
{
	whereChapter = ChapterParam;
}

int Singleton::isWhereChapter()
{
	return whereChapter;
}

bool Singleton::getInteractor()
{
	return interactor;
}

void Singleton::setInteractor(bool param)
{
	interactor = param;
}

b2World * Singleton::getWorld()
{
	return _world;
}

Help & Singleton::getHelp()
{
	return	_Help;
}