#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Help.h"

using namespace cocos2d;

class Singleton
{
public:
	static const int PTM_RATIO = 72;

	class ContactListener : public b2ContactListener
	{
	public:
		typedef std::function<void(b2Contact* contact)> on_contact_t;
		typedef std::function<void(b2Contact* contact, const b2Manifold* oldManifold)> on_pre_solve_t;
		typedef std::vector<on_contact_t> on_contacts_t;
		typedef std::vector<on_pre_solve_t> on_pre_solves_t;

	private:
		on_contacts_t OnBeginContacts;
		on_contacts_t OnEndContacts;
		on_pre_solves_t OnPreSolves;

	public:
		on_contacts_t& getOnBeginContacts() { return OnBeginContacts; }
		const on_contacts_t& getOnBeginContacts() const { return OnBeginContacts; }
		on_contacts_t& getOnEndContacts() { return OnEndContacts; }
		const on_contacts_t& getOnEndContacts() const { return OnEndContacts; }
		on_pre_solves_t& getOnPreSolves() { return OnPreSolves; }
		const on_pre_solves_t& getOnPreSolves() const { return OnPreSolves; }

		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	};
private:
	Singleton();
	~Singleton();
	static Singleton* inst;
	ContactListener* _ContactListener;
	int numFootContacts;
	int Chapter;
	int Level;
	int whereClear = 0;
	int whereChapter = 1;
	bool interactor = false;
	bool MusicCheck;
	bool Result = false;
	b2World* _world;
	Help _Help;

public:
	static Singleton* getInstance();
	void setChapter(int ChapterParam);
	void setLevel(int LevelParam);
	void setMusic(bool MusicParam);
	int IsLevel();
	int IsChapter();
	bool isMusic();
	void setClear(bool ClearParam);
	bool isClear();
	void setWhereClear(int ClearParam);
	int isWhereClear();
	void setWhereChapter(int ChapterParam);
	int isWhereChapter();
	bool getInteractor();
	void setInteractor(bool param);
	b2World* getWorld();
	ContactListener* getContactListener() { return _ContactListener; }
	Help& getHelp();

};

