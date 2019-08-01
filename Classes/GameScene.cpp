#pragma execution_character_set("utf-8")

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Singleton.h"
#include "MainScene.h"
#include "DebugDrawBox2D.h"

using namespace cocos2d;
using namespace CocosDenshion;

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//## 변수 초기화
	Win_Size = Director::getInstance()->getVisibleSize();
	Singleton::getInstance()->setClear(false);
	Time_State = false;
	num = 0;
	_num = 0;
	hour = 0;

	//## 터치 활성화
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	this->scheduleUpdate();		//업데이트 활성화

	_world = Singleton::getInstance()->getWorld();

	Game_Init();
	Player_Init();
	ButtonInit();
	createUI();

	return true;
}

void GameScene::Game_Init()
{
	if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/BGM/BGM_In Game.wav");
	}

	Win_Size = Director::getInstance()->getVisibleSize();
	Map_BackGround_Now = Layer::create();
	Map_BackGround_Past = Layer::create();
	UI_Layer = Layer::create();
	Overlap_Layer = Layer::create();
	Game_Layer = Layer::create();
	Back_Layer = Layer::create();
	Game_Layer->addChild(Map_BackGround_Now, 3);
	Game_Layer->addChild(Map_BackGround_Past, 3);
	Game_Layer->addChild(Overlap_Layer, 2);
	Game_Layer->addChild(Back_Layer, 1);
	Help_Layer = Layer::create();
	this->addChild(Help_Layer, 10);
	off = 0;

	//auto debug = DebugDrawBox2D::create();
	//Game_Layer->addChild(debug);
	//debug->setGlobalZOrder(999999);

	this->addChild(Game_Layer);
	Map_BackGround_Past->setVisible(false);
	this->addChild(UI_Layer, 5);

	auto Mc = Label::createWithTTF(Singleton::getInstance()->getHelp().Return(), "fonts/SNCB.ttf", 50.f);
	Mc->setPosition(Win_Size.width*0.5f, Win_Size.height*0.65f);
	Help_Layer->addChild(Mc, 100);

	auto Help_chang = Sprite::create("Button/Popup_Info.png");
	Help_chang->setPosition(Win_Size.width*0.5, Win_Size.height*0.65f);
	Help_Layer->addChild(Help_chang, 10);

	int Chapter = Singleton::getInstance()->IsChapter();
	int Level = Singleton::getInstance()->IsLevel();

	switch (Chapter)
	{
	case 1:
		mapSize = Rect(0, 0, Win_Size.width * 2.f, 847.f);
		CreateGroundWall(2.f);

		switch (Level)
		{
		case 1:
#pragma region Wall
			wallCount = 1;
			wall = new Wall*[wallCount * 2];

			for (int i = 0; i < (wallCount * 2); ++i)
				wall[i] = new Wall();

			wall[0]->setPosition(Vec2(Win_Size.width * 1.75f, Win_Size.height * 0.6f));
			wall[0]->init("Obj/Wall/Stage_01/Obj_Ground_04.png");
			Map_BackGround_Now->addChild(wall[0]->getSprite(), 4);
			wall[1]->setPosition(Vec2(Win_Size.width * 1.75f, Win_Size.height * 0.6f));
			wall[1]->init("Obj/Wall/Stage_01/Obj_Ground_04.png");
			Map_BackGround_Past->addChild(wall[1]->getSprite(), 4);
#pragma endregion
#pragma region Spike
			spikeCnt = 3;
			spike = new Spike*[spikeCnt];

			for (int i = 0; i < spikeCnt; ++i)
				spike[i] = new Spike();
			spike[0]->setPosition(Vec2(Win_Size.width * 0.4f, Win_Size.height *0.2f));
			spike[1]->setPosition(Vec2(Win_Size.width * 0.8f, Win_Size.height *0.2f));
			spike[2]->setPosition(Vec2(Win_Size.width * 1.1f, Win_Size.height *0.2f));
			for (int i = 0; i < spikeCnt; ++i)
			{
				spike[i]->init("Obj/Objects/Thron/Obj_Thron.png");
				spike[i]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
				Map_BackGround_Now->addChild(spike[i]->getSprite(), 4);
			}
#pragma endregion
#pragma region Ladder
			ladder = new Ladder();
			ladder->setLadderPosition(Vec2(Win_Size.width * 1.7f, Win_Size.height * 0.19f));
			ladder->init(8);
			Map_BackGround_Now->addChild(ladder->getSprite(), 4);
#pragma endregion
#pragma region Portal
			portal = new Portal();
			portal->setPosition(Vec2(Win_Size.width * 1.87f, Win_Size.height * 0.75f));
			portal->init();
			Map_BackGround_Now->addChild(portal->getSprite(), 4);
#pragma endregion
			break;
		case 2:
#pragma region Stone
			Rock = new Stone();
			Rock->setPosition(Vec2(Win_Size.width * 0.3f, Win_Size.height * 0.2f));
			Rock->init();
			Overlap_Layer->addChild(Rock->getSprite(), 4);
#pragma endregion
#pragma region Plant
			plantCount = 1;
			plant = new Plant*[plantCount * 2];
			for (int i = 0; i < (plantCount * 2); ++i)
				plant[i] = new Plant();

			plant[0]->setUserData(10);
			plant[0]->setPosition(Vec2(Win_Size.width * 0.6f, Win_Size.height * 0.35f));
			plant[0]->init("Obj/Flowers/Plant/Obj_Present_Tree.png");
			plant[0]->setLight("Obj/Flowers/Light/Obj_Present_Tree_Light.png");
			Map_BackGround_Now->addChild(plant[0]->getSprite(), 4);

			plant[1]->setUserData(2);
			plant[1]->setPosition(Vec2(Win_Size.width * 1.2f, Win_Size.height * 0.25f));
			plant[1]->init("Obj/Flowers/Plant/Obj_Plant.png");
			plant[1]->setLight("Obj/Flowers/Light/Obj_Plant_Light.png");
			Map_BackGround_Now->addChild(plant[1]->getSprite(), 4);
#pragma endregion
#pragma region Match
			match = new Match();
			match->setPosition(Vec2(Win_Size.width * 0.9f, Win_Size.height * 0.2f));
			match->init();
			Map_BackGround_Now->addChild(match->getSprite(), 4);
#pragma endregion
#pragma region Portal
			portal = new Portal();
			portal->setPosition(Vec2(Win_Size.width * 1.8f, Win_Size.height * 0.25f));
			portal->init();
			Map_BackGround_Now->addChild(portal->getSprite(), 4);
#pragma endregion
			break;
		case 3:
#pragma region Wall
			wallCount = 2;
			wall = new Wall*[wallCount * 2];

			for (int i = 0; i < (wallCount * 2); ++i)
				wall[i] = new Wall();

			wall[0]->setPosition(Vec2(Win_Size.width * 0.4f, Win_Size.height * 0.65f));
			wall[0]->init("Obj/Wall/Stage_01/Obj_Ground_04.png");
			Overlap_Layer->addChild(wall[0]->getSprite(), 4);
			wall[1]->setPosition(Vec2(Win_Size.width * 0.9f, Win_Size.height * 0.35f));
			wall[1]->init("Obj/Wall/Stage_01/Obj_Hill.png");
			Overlap_Layer->addChild(wall[1]->getSprite(), 4);
#pragma endregion
#pragma region Plant
			plantCount = 2;
			plant = new Plant*[plantCount];

			for (int i = 0; i < plantCount; i++)
			{
				plant[i] = new Plant();
			}

			plant[0]->setUserData(10);
			plant[0]->setPosition(Vec2(Win_Size.width * 0.45f, Win_Size.height * 0.87f));
			plant[0]->init("Obj/Flowers/Plant/Obj_Present_Tree.png");
			plant[0]->setLight("Obj/Flowers/Light/Obj_Present_Tree_Light.png");
			Map_BackGround_Now->addChild(plant[0]->getSprite(), 4);

			plant[1]->setUserData(2);
			plant[1]->setPosition(Vec2(Win_Size.width * 0.47f, Win_Size.height * 0.79f));
			plant[1]->init("Obj/Flowers/Plant/Obj_Plant.png");
			plant[1]->setLight("Obj/Flowers/Light/Obj_Plant_Light.png");
			Map_BackGround_Past->addChild(plant[1]->getSprite(), 4);
#pragma endregion
#pragma region Match
			match = new Match();
			match->setPosition(Vec2(Win_Size.width * 0.5f, Win_Size.height * 0.2f));
			match->init();
			Map_BackGround_Past->addChild(match->getSprite(), 4);
#pragma endregion
#pragma region Ladder
			ladder = new Ladder();
			ladder->setLadderPosition(Vec2(Win_Size.width * 0.27f, Win_Size.height * 0.17f));
			ladder->init(9);
			Overlap_Layer->addChild(ladder->getSprite(), 4);
#pragma endregion
#pragma region Spike
			spikeCnt = 5;
			spike = new Spike*[spikeCnt];

			for (int i = 0; i < spikeCnt; ++i)
				spike[i] = new Spike();

			spike[0]->setPosition(Vec2(Win_Size.width * 0.5f, Win_Size.height *0.2f));
			spike[0]->init("Obj/Objects/Thron/Obj_Thron.png");
			spike[0]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
			Map_BackGround_Now->addChild(spike[0]->getSprite(), 4);
			spike[1]->setPosition(Vec2(Win_Size.width * 0.4f, Win_Size.height *0.2f));
			spike[1]->init("Obj/Objects/Thron/Obj_Thron.png");
			spike[1]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
			Map_BackGround_Past->addChild(spike[1]->getSprite(), 4);
			spike[2]->setPosition(Vec2(Win_Size.width* 0.85f, Win_Size.height * 0.8f));
			spike[2]->init("Obj/Objects/Thron/Obj_Thron.png");
			spike[2]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
			Map_BackGround_Now->addChild(spike[2]->getSprite(), 4);
			spike[3]->setPosition(Vec2(Win_Size.width * 0.92f, Win_Size.height * 0.8f));
			spike[3]->init("Obj/Objects/Thron/Obj_Thron.png");
			spike[3]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
			Overlap_Layer->addChild(spike[3]->getSprite(), 4);
			spike[4]->setPosition(Vec2(Win_Size.width * 1.f, Win_Size.height * 0.8f));
			spike[4]->init("Obj/Objects/Thron/Obj_Thron.png");
			spike[4]->setLight("Obj/Objects/Thron/Obj_Thron_Light.png");
			Map_BackGround_Now->addChild(spike[4]->getSprite(), 4);
#pragma endregion
#pragma region MovingWalk
			movingwalk = new MovingWalk();
			movingwalk->setPosition(Vec2(Win_Size.width * 0.9f, Win_Size.height * 0.7f));
			movingwalk->setVelocity(b2Vec2(0.f, 100.f / Singleton::PTM_RATIO));
			movingwalk->init("Obj/Wall/Stage_01/Obj_Ground_03.png");

			Overlap_Layer->addChild(movingwalk->getSprite(), 4);
#pragma endregion
#pragma region Plate
			plate = new Plate();
			plate->setPosition(Vec2(Win_Size.width * 1.1f, Win_Size.height * 0.2f));
			plate->init();
			Overlap_Layer->addChild(plate->getSprite(), 4);
#pragma endregion
#pragma region Rock
			Rock = new Stone();
			Rock->setPosition(Vec2(Win_Size.width * 1.3f, Win_Size.height * 0.2f));
			Rock->init();
			Overlap_Layer->addChild(Rock->getSprite(), 4);
#pragma endregion
#pragma region Portal
			portal = new Portal();
			portal->setPosition(Vec2(Win_Size.width * 1.9f, Win_Size.height * 0.25f));
			portal->init();
			Map_BackGround_Now->addChild(portal->getSprite(), 4);
#pragma endregion
#pragma region Joint
			{
				const b2Vec2 relative = spike[2]->getBody()->GetPosition() - movingwalk->getBody()->GetPosition();
				const b2Vec2 relative_2 = spike[3]->getBody()->GetPosition() - movingwalk->getBody()->GetPosition();
				const b2Vec2 relative_3 = spike[4]->getBody()->GetPosition() - movingwalk->getBody()->GetPosition();

				spike[2]->getSprite()->schedule([=](float)
				{
					spike[2]->getBody()->SetTransform(movingwalk->getBody()->GetPosition() + relative, spike[2]->getBody()->GetAngle());
				}, 0.f, "stick_to_the_fucking_ground");

				spike[3]->getSprite()->schedule([=](float)
				{
					spike[3]->getBody()->SetTransform(movingwalk->getBody()->GetPosition() + relative_2, spike[3]->getBody()->GetAngle());
				}, 0.f, "stick_to_the_fucking_ground_2");

				spike[4]->getSprite()->schedule([=](float)
				{
					spike[4]->getBody()->SetTransform(movingwalk->getBody()->GetPosition() + relative_3, spike[4]->getBody()->GetAngle());
				}, 0.f, "stick_to_the_fucking_ground_3");
			}

#pragma endregion
			break;
		case 4:
			break;
		case 5:
			break;
		}
		break;
	case 2:
		mapSize = Rect(0, 0, 3840, 3240);
		CreateGroundWall(23);

		switch (Level)
		{
		case 1:
		{
			auto W = new Wall;
			W->setPosition(Vec2(-10, 2100));
			W->init("", 2, 9);
			Map_BackGround_Now->addChild(W->getSprite(), 4);

			auto M = new Wall;
			M->setPosition(Vec2(-50, 2100));
			M->init("", 2, 5);
			Map_BackGround_Past->addChild(M->getSprite(), 4);

			auto C = new Wall;
			C->setPosition(Vec2(1200, 2100));
			C->init("", 2, 2);
			Map_BackGround_Past->addChild(C->getSprite(), 4);
		}
#pragma region Wall
		wallCount = 10;
		wall = new Wall*[wallCount];

		for (int i = 0; i < 9; ++i)//기둥
		{
			wall[i] = new Wall();
			wall[i]->setPosition(Vec2(2180, 1500 + 120 * i));
			wall[i]->init("Obj/Wall/Stage_02/Obj_Pillar.png");
			Overlap_Layer->addChild(wall[i]->getSprite());
			wall[i]->getSprite()->setGlobalZOrder(5);
		}


		CreateCastleWall(6, Vec2(-50, 100));
		CreateCastleWall(20, Vec2(1250, 100));
		CreateCastleWall(6, Vec2(-50, 1400));
		CreateCastleWall(20, Vec2(1200, 1400));

		for (int i = 0; i<10; i++)
		{
			CreatefilledWall(4, Vec2(-50, 197 + 110 * i));
		}
		CreatefilledWall(4, Vec2(-50, 1283));
		CreatefilledWall(20, Vec2(1200, 1350));
		for (int i = 0; i < 6; i++)
		{
			CreatefilledWall(13, Vec2(2200, 2000 + 120 * i));
		}
#pragma endregion
#pragma region Ladder
		ladder = new Ladder();
		ladder->setLadderPosition(Vec2(2000, 1500));
		ladder->init(13);
		Overlap_Layer->addChild(ladder->getSprite(), 4);

		_ladder = new Ladder();
		_ladder->setLadderPosition(Vec2(3800, 300));
		_ladder->init(26);
		Overlap_Layer->addChild(_ladder->getSprite(), 4);

#pragma endregion
#pragma region SandBag
		sandbag = new SandBag();
		sandbag->setPosition(Vec2(500, 2100));
		sandbag->init();
		Map_BackGround_Now->addChild(sandbag->getSprite(), 4);
#pragma endregion
#pragma region Plate
		plate = new Plate();
		plate->setPosition(Vec2(3300, 1470));
		plate->init();
		Overlap_Layer->addChild(plate->getSprite(), 4);
#pragma endregion
#pragma region MovingWalk
		movingwalk = new MovingWalk();
		movingwalk->setPosition(Vec2(1600, 380));
		movingwalk->setVelocity(b2Vec2(-100.f / Singleton::PTM_RATIO, 0.f));
		movingwalk->init("Obj/Objects/Move_Wall.png");
		Map_BackGround_Now->addChild(movingwalk->getSprite(), 4);
		movingwalk->getSprite()->setGlobalZOrder(200);

		_movingwalk = new MovingWalk();
		_movingwalk->setPosition(Vec2(700, 380));
		_movingwalk->setVelocity(b2Vec2(100.f / Singleton::PTM_RATIO, 0.f));
		_movingwalk->init("Obj/Objects/Move_Wall.png");
		Map_BackGround_Past->addChild(_movingwalk->getSprite(), 4);
		movingwalk->getSprite()->setGlobalZOrder(200);
#pragma endregion
#pragma region Rock
		Rock = new Stone();
		Rock->setPosition(Vec2(3150, 1470));
		Rock->init();
		Overlap_Layer->addChild(Rock->getSprite(), 4);
#pragma endregion
#pragma region Portal
		portal = new Portal();
		portal->setPosition(Vec2(2580, 1515));
		portal->init();
		Map_BackGround_Now->addChild(portal->getSprite(), 4);
#pragma endregion
#pragma region Spike
		spikeCnt = 4;
		spike = new Spike*[spikeCnt];

		for (int i = 0; i < spikeCnt; ++i)
			spike[i] = new Spike();

		spike[0]->setPosition(Vec2(1000, 30));
		spike[1]->setPosition(Vec2(1150, 30));
		spike[2]->setPosition(Vec2(1300, 1470));
		spike[3]->setPosition(Vec2(830, 1470));
		for (int i = 0; i < spikeCnt; ++i)
		{
			if (i >= 2)
			{
				spike[i]->init("Obj/Objects/Thron/Stage_02/Obj_Thron.png");
				spike[i]->setLight("Obj/Objects/Thron/Stage_02/Obj_Thron.png");
				Map_BackGround_Past->addChild(spike[i]->getSprite(), 4);
				spike[i]->getSprite()->setGlobalZOrder(300);
				continue;
			}
			spike[i]->init("Obj/Objects/Thron/Stage_02/Obj_Thron.png");
			spike[i]->setLight("Obj/Objects/Thron/Stage_02/Obj_Thron.png");
			Overlap_Layer->addChild(spike[i]->getSprite(), 4);
		}
#pragma endregion
#pragma region FireTrap
		firetrap = new FireTrap();
		firetrap->setPosition(Vec2(2000, 278));
		firetrap->init();
		Overlap_Layer->addChild(firetrap->getSprite(), 4);
		_firetrap = new FireTrap();
		_firetrap->setPosition(Vec2(2000, 700));
		_firetrap->init();
		_firetrap->getSprite()->setFlippedY(true);
		Overlap_Layer->addChild(_firetrap->getSprite(), 4);
#pragma endregion
			break;
		case 2:
			break;
		}
		break;
	}

	//## 과거 비활성
	auto PastChildSet = Map_BackGround_Past->getChildren();

	for (auto V : PastChildSet)
	{
		Obj* obj = reinterpret_cast<Obj*>(V->getUserData());
		if (obj != nullptr)
		{
			b2Body* objBody = obj->getBody();
			objBody->SetActive(false);
		}
	}
}

void GameScene::Player_Init()
{
	int Chapter = Singleton::getInstance()->IsChapter();
	int Level = Singleton::getInstance()->IsLevel();

	if (Chapter == 1)
	{
		player = new Player();
		player->setPosition(Vec2(Win_Size.width * 0.1f, Win_Size.height * 0.5f));
		player->init();
		Map_BackGround_Now->addChild(player->getSprite(), 3);
		player->getSprite()->setGlobalZOrder(200);
		Game_Layer->runAction(Follow::create(player->getSprite(), mapSize));
	}

	else if (Chapter == 2)
	{
		player = new Player();
		player->setPosition(Vec2(100, 2000));
		player->init();
		Map_BackGround_Now->addChild(player->getSprite(), 3);
		player->getSprite()->setGlobalZOrder(200);
		Game_Layer->runAction(Follow::create(player->getSprite(), mapSize));
	}
}

GameScene::~GameScene()
{
	log("Delete");

	if (ladder != nullptr)
		_world->DestroyBody(ladder->getBody());
	if (_ladder != nullptr)
		_world->DestroyBody(_ladder->getBody());

	for (b2Joint* b = _world->GetJointList(); b != nullptr; b = b->GetNext())
	{
		_world->DestroyJoint(b);
	}

	Singleton::getInstance()->getContactListener()->getOnBeginContacts().clear();
	Singleton::getInstance()->getContactListener()->getOnEndContacts().clear();
}

void GameScene::ButtonInit()
{
	Size Win_Size = Director::getInstance()->getVisibleSize();

	Opacity_Layer = LayerColor::create(Color4B(0, 0, 0, 185));
	UI_Layer->addChild(Opacity_Layer, 10);
	Opacity_Layer->setVisible(false);
	Opacity_Layer->setGlobalZOrder(1099);

	auto Help_Button = Sprite::create("Button/UI_Info_Btn.png");
	Help_Button->setPosition(Win_Size.width * 0.5f, Win_Size.height * 0.9f);
	this->addChild(Help_Button, 10);
	Help_Button->setGlobalZOrder(1098);

	auto Option_Sprite = Sprite::create("Button/Option/UI_Pause_Btn.png");
	Option_Sprite->setPosition(Win_Size.width * 0.92f, Win_Size.height*0.9f);
	UI_Layer->addChild(Option_Sprite, 5);
	Option_Sprite->setGlobalZOrder(1100);

	auto Option_Sprite_Past = Sprite::create("Button/Option/UI_Pause_Btn.png");
	Option_Sprite_Past->setPosition(Win_Size.width * 0.92f, Win_Size.height*0.9f);
	UI_Layer->addChild(Option_Sprite_Past, 5);
	Option_Sprite_Past->setGlobalZOrder(1100);

	auto Option_Listener = EventListenerTouchOneByOne::create();
	Option_Listener->setSwallowTouches(true);
	Option_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			if (Opacity_Layer->isVisible())
			{
				Director::sharedDirector()->resume();
				Opacity_Layer->setVisible(false);
			}
			else
			{
				Director::sharedDirector()->pause();
				Opacity_Layer->setVisible(true);
			}
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Option_Listener, Option_Sprite);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Option_Listener->clone(), Option_Sprite_Past);

	auto Bgm_button = Sprite::create("Button/Option/Sound/UI_BGM_Btn.png");
	Bgm_button->setPosition(Win_Size.width*0.5 - 200, Win_Size.height*0.5);
	Opacity_Layer->addChild(Bgm_button, 10);
	Bgm_button->setGlobalZOrder(1100);

	auto BGM = Label::createWithTTF("BGM", "fonts/SNCB.ttf", 18);
	BGM->setPosition(Win_Size.width*0.5 - 200, Win_Size.height*0.4);
	Opacity_Layer->addChild(BGM, 1);
	BGM->setGlobalZOrder(1100);

	auto Bgm_Listener = EventListenerTouchOneByOne::create();
	Bgm_Listener->setSwallowTouches(true);
	Bgm_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			{
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			}
			else
			{
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic("");
				
			}
			return true;
		}
		return false;
	};

	Bgm_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (num == 0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			num++;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/BGM/BGM_In Game.wav", true);
			Bgm_button->setTexture("Button/Option/Sound/UI_BGM_Btn.png");
			num = 0;
		}

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Bgm_Listener, Bgm_button);

	auto uiline = Sprite::create("Obj/Lines/Line_1.png");
	uiline->setPosition(Win_Size.width * 0.5, Win_Size.height*0.7);
	Opacity_Layer->addChild(uiline, 5);
	uiline->setGlobalZOrder(1100);

	auto uiline2 = Sprite::create("Obj/Lines/Line_2.png");
	uiline2->setPosition(Win_Size.width * 0.5, Win_Size.height*0.3);
	Opacity_Layer->addChild(uiline2, 5);
	uiline2->setGlobalZOrder(1100);

	auto Sfx_button = Sprite::create("Button/Option/Sound/UI_SFX_Btn.png");
	Sfx_button->setPosition(Win_Size.width*0.35 - 200, Win_Size.height*0.5);
	Opacity_Layer->addChild(Sfx_button, 5);
	Sfx_button->setGlobalZOrder(1100);

	auto SFX = Label::createWithTTF("SFX", "fonts/SNCB.ttf", 18);
	SFX->setPosition(Win_Size.width*0.35 - 200, Win_Size.height*0.4);
	Opacity_Layer->addChild(SFX, 1);
	SFX->setGlobalZOrder(1100);

	auto Sfx_Listener = EventListenerTouchOneByOne::create();
	Sfx_Listener->setSwallowTouches(true);
	Sfx_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			log("Touch 1");

			return true;
		}
		return false;
	};

	Sfx_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (_num == 0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			Sfx_button->setTexture("Button/Option/Sound/UI_SFX_Click_Btn.png");
			_num++;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Grandpapa_Eleven_Month.wav", true);
			Sfx_button->setTexture("Button/Option/Sound/UI_SFX_Btn.png");
			_num = 0;
		}

		log("Touch 2");

		return true;

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Sfx_Listener, Sfx_button);

	auto stoplabel = Label::createWithTTF("Pause", "fonts/SNCB.ttf", 46);
	stoplabel->setPosition(Win_Size.width * 0.5, Win_Size.height*0.7);
	Opacity_Layer->addChild(stoplabel, 70);
	stoplabel->setGlobalZOrder(1100);

	auto resume = Sprite::create("Button/Option/UI_Resume_Btn.png");
	resume->setPosition(Win_Size.width * 0.8, Win_Size.height*0.5);
	Opacity_Layer->addChild(resume, 5);
	resume->setGlobalZOrder(1100);

	auto STOP = Label::createWithTTF("RESUME", "fonts/SNCB.ttf", 18);
	STOP->setPosition(Win_Size.width * 0.8, Win_Size.height*0.4);
	Opacity_Layer->addChild(STOP, 1);
	STOP->setGlobalZOrder(1100);

	auto resume_Listener = EventListenerTouchOneByOne::create();
	resume_Listener->setSwallowTouches(true);
	resume_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(resume_Listener, resume);

	auto close = Sprite::create("Button/Option/Back/UI_Menu_Btn.png");
	close->setPosition(Win_Size.width*0.65, Win_Size.height*0.5);
	Opacity_Layer->addChild(close, 5);
	close->setGlobalZOrder(1100);

	auto MENU = Label::createWithTTF("Quit", "fonts/SNCB.ttf", 18);
	MENU->setPosition(Win_Size.width*0.65, Win_Size.height*0.4);
	Opacity_Layer->addChild(MENU, 1);
	MENU->setGlobalZOrder(1100);

	auto close_Listener = EventListenerTouchOneByOne::create();
	close_Listener->setSwallowTouches(true);
	close_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			Director::getInstance()->replaceScene(MainScene::createScene());
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(close_Listener, close);

	auto replay = Sprite::create("Button/Option/Back/UI_Replay_Btn.png");
	replay->setPosition(Win_Size.width*0.5, Win_Size.height*0.5);
	Opacity_Layer->addChild(replay, 5);
	replay->setGlobalZOrder(1100);

	auto Replay = Label::createWithTTF("REPLAY", "fonts/SNCB.ttf", 18);
	Replay->setPosition(Win_Size.width * 0.5, Win_Size.height*0.4);
	Opacity_Layer->addChild(Replay, 1);
	Replay->setGlobalZOrder(1100);

	auto replay_Listener = EventListenerTouchOneByOne::create();
	replay_Listener->setSwallowTouches(true);
	replay_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			Director::getInstance()->replaceScene(GameScene::createScene());
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(replay_Listener, replay);


	Help_Layer->setVisible(false);

	auto Help_Listener = EventListenerTouchOneByOne::create();
	Help_Listener->setSwallowTouches(true);

	Help_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{ 
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			if (off == 0)
			{
				Help_Layer->setVisible(true);
				off++;
			}
			else
			{
				Help_Layer->setVisible(false);
				off--;
			}

			return false;
		};
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Help_Listener, Help_Button);
}

void GameScene::update(float dt)
{
	int velocitylterations = 8;
	int positionlterations = 3;

	_world->Step(dt, velocitylterations, positionlterations);

	if (plate != nullptr)
		plate->update();

	if (movingwalk != nullptr)
		movingwalk->update();

	if (!Time_State)
	{
		player->update();
	}
	else
	{
		player_past->update();
	}

	Singleton::getInstance()->getContactListener()->getOnBeginContacts().push_back(
		[this](b2Contact* contact) -> void
	{
		b2Fixture* fixtures[2] = { contact->GetFixtureA(), contact->GetFixtureB() };
		for (int i = 0; i < 2; i++)
		{
			if (reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4
				&& (fixtures[1 - i] == player->bodyFixture))
			{
				Jump_Button->setTexture("Button/UI_Climb_Btn.png");
				break;
			}
			else if (player_past != nullptr && reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4
				&& fixtures[1 - i] == player_past->bodyFixture)
			{
				Jump_Button->setTexture("Button/UI_Climb_Btn.png");
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
			if (reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4
				&& (fixtures[1 - i] == player->bodyFixture))
			{
				Jump_Button->setTexture("Button/UI_Jump_Btn.png");
				break;
			}
			else if (player_past != nullptr && reinterpret_cast<int>(fixtures[i]->GetUserData()) == 4
				&& fixtures[1 - i] == player_past->bodyFixture)
			{
				Jump_Button->setTexture("Button/UI_Jump_Btn.png");
				break;
			}
		}
	});

	for (b2Body* b = _world->GetBodyList(); b != nullptr; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Point(b->GetPosition().x * Singleton::PTM_RATIO,
				b->GetPosition().y * Singleton::PTM_RATIO));
		}
	}
}

void GameScene::createUI()
{
	Win_Size = Director::getInstance()->getVisibleSize();
	//##빛나는거
	auto _sprite = Sprite::create();
	Bright = Sequence::create(FadeIn::create(0.8f), FadeOut::create(0.8f), nullptr);
	_sprite->runAction(Bright);

	//##왼쪽 화살표
	auto Left_Arrow = Sprite::create("Button/UI_Shifting_Left_Btn.png");
	Left_Arrow->setPosition(Point(Win_Size.width * 0.1f, Win_Size.height * 0.1f));
	UI_Layer->addChild(Left_Arrow, 5);
	Left_Arrow->setGlobalZOrder(999);

	auto Left_Listener = EventListenerTouchOneByOne::create();
	Left_Listener->setSwallowTouches(true);
	Left_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			if (player->contacting && (!Time_State))
			{
				player->HangOn(2);

				return true;
			}

			else if (player->getBody()->GetType() == b2_dynamicBody && (!Time_State))
			{
				player->move(0);

				return true;
			}

			if (player_past != nullptr && player_past->contacting)
			{
				player_past->HangOn(2);

				return true;
			}

			else if (player_past != nullptr && player_past->getBody()->GetType() == b2_dynamicBody)
			{
				player_past->move(0);
				return true;
			}

			return true;
		}
		return false;
	};

	Left_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		if (!Time_State)
			player->Idle();
		else
			player_past->Idle();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Left_Listener, Left_Arrow);

	//##오른쪽 화살표
	auto Right_Arrow = Sprite::create("Button/UI_Shifting_Right_Btn.png");
	Right_Arrow->setPosition(Point(Win_Size.width * 0.2f, Win_Size.height * 0.1f));
	UI_Layer->addChild(Right_Arrow, 5);
	Right_Arrow->setGlobalZOrder(999);

	auto Right_Listener = EventListenerTouchOneByOne::create();
	Right_Listener->setSwallowTouches(true);
	Right_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			if (player->contacting && (!Time_State))
			{
				player->HangOn(3);

				return true;
			}

			else if (player->getBody()->GetType() == b2_dynamicBody && (!Time_State))
			{
				player->move(1);
				return true;
			}

			if (player_past != nullptr && player_past->contacting)
			{
				player_past->HangOn(3);

				return true;
			}

			else if (player_past != nullptr && player_past->getBody()->GetType() == b2_dynamicBody)
			{
				player_past->move(1);
				return true;
			}

			return true;
		}

		return false;
	};

	Right_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		if (!Time_State)
			player->Idle();
		else
			player_past->Idle();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Right_Listener, Right_Arrow);

	//## 점프 버튼
	Jump_Button = Sprite::create("Button/UI_Jump_Btn.png");
	Jump_Button->setPosition(Point(Win_Size.width * 0.9f, Win_Size.height * 0.1f));
	UI_Layer->addChild(Jump_Button, 5);
	Jump_Button->setGlobalZOrder(999);

	JumpBright = Sprite::create("Button/_Light.png");
	Jump_Button->addChild(JumpBright, 10);
	JumpBright->setAnchorPoint(Vec2(0.f, 0.f));
	JumpBright->setVisible(false);
	JumpBright->setOpacity(0);

	auto Jump_Listener = EventListenerTouchOneByOne::create();
	Jump_Listener->setSwallowTouches(true);

	Jump_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			JumpBright->runAction(Repeat::create(Bright->clone(), 999999));
			JumpBright->setVisible(true);

			if (!Time_State)
			{
				SimpleAudioEngine::sharedEngine()->playEffect("sound/Game/Charactor_Jump.wav");
				player->Jump();
			}
			else
			{
				SimpleAudioEngine::sharedEngine()->playEffect("sound/Game/Charactor_Jump.wav");
				player_past->Jump();
			}

			return true;
		}

		return false;
	};
	Jump_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		JumpBright->stopAllActions();
		JumpBright->setVisible(false);
		JumpBright->setOpacity(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Jump_Listener, Jump_Button);

	//## 도구 버튼
	ToolButton = Sprite::create("Button/UI_Tool_Btn.png");
	ToolButton->setPosition(Vec2(Win_Size.width * 0.8f, Win_Size.height * 0.1f));
	UI_Layer->addChild(ToolButton, 5);
	ToolButton->setGlobalZOrder(999);

	ToolBright = Sprite::create("Button/_Light.png");
	ToolButton->addChild(ToolBright, 10);
	ToolBright->setAnchorPoint(Vec2(0.f, 0.f));
	ToolBright->setVisible(false);
	ToolBright->setOpacity(0);

	auto ToolListener = EventListenerTouchOneByOne::create();
	ToolListener->setSwallowTouches(true);
	ToolListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			ToolBright->runAction(Repeat::create(Bright->clone(), 999999));
			ToolBright->setVisible(true);
			if (!Time_State)
			{
				if (player->getToolState())
				{
					int ObjTag = player->getItemStatus();
					std::vector<int> Objset = player->Use();

					for (auto V : Objset)
					{
						switch (V)
						{
						case 20:
							if (Singleton::getInstance()->IsLevel() == 2)
							{
								player->getSprite()->stopAllActions();
								player->Throwing();

								plant[1]->getSprite()->stopAllActions();
								plant[1]->fire();

								Sprite* match = Sprite::create("Obj/Objects/Match/Obj_Match.png");
								player->getSprite()->getParent()->addChild(match, player->getSprite()->getLocalZOrder());
								match->setPosition(player->getSprite()->getPosition());

								match->runAction(Sequence::create(
									JumpTo::create(2, plant[1]->getSprite()->getPosition(), 100, 1),
									CallFunc::create([=]() -> void
								{
									match->removeFromParent();
								}), nullptr));

								UI_Layer->removeChild(mt, true);
							}
							break;
						case 21:
							if (Singleton::getInstance()->IsLevel() == 1)
							{
							}
							break;
						}
					}
					return true;
				}
				else
				{
					if (player->Take())
					{
						int ObjTag = player->getItemStatus();

						switch (ObjTag)
						{
						case 3:
							Map_BackGround_Now->removeChild(match->getSprite(), true); 
							mt = Sprite::create("Obj/Objects/Match/Obj_Match.png");
							mt->setPosition(ToolButton->getPosition());
							UI_Layer->addChild(mt, ToolButton->getZOrder() + 1);
							mt->setGlobalZOrder(1000);
							break;
						case 13:
							Map_BackGround_Now->removeChild(sandbag->getSprite(), true);
							sb = Sprite::create("Obj/Objects/Sandbag/Obj_Sandbag.png");
							sb->setPosition(ToolButton->getPosition());
							UI_Layer->addChild(sb, ToolButton->getZOrder() + 1);
							sb->setGlobalZOrder(1000);
							break;
						}
					}
					else
					{

					}
					return true;
				}
			}

			else
			{
				if (player_past->getToolState())
				{
					int ObjTag = player_past->getItemStatus();
					std::vector<int> Objset = player_past->Use();

					for (auto V : Objset)
					{
						switch (V)
						{
						case 20:
							if (Singleton::getInstance()->IsLevel() == 3)
							{
								player_past->getSprite()->stopAllActions();
								player_past->Throwing();

								plant[1]->getSprite()->stopAllActions();
								plant[1]->fire();
								Map_BackGround_Now->removeChild(plant[0]->getSprite(), true);

								Sprite* match = Sprite::create("Obj/Objects/Match/Obj_Match.png");
								player_past->getSprite()->getParent()->addChild(match, player_past->getSprite()->getLocalZOrder());
								match->setPosition(player_past->getSprite()->getPosition());

								match->runAction(Sequence::create(
									JumpTo::create(2, plant[1]->getSprite()->getPosition(), 100, 1),
									CallFunc::create([=]() -> void
								{
									match->removeFromParent();
								}), nullptr));

								UI_Layer->removeChild(mt, true);
							}
							
						case 21:
							if (Singleton::getInstance()->IsLevel() == 1)
							{
								player_past->getSprite()->stopAllActions();
								player_past->Throwing();
								Sprite* Sand = Sprite::create("Obj/Objects/Sandbag/Obj_Sandbag.png");
								player_past->getSprite()->getParent()->addChild(Sand, player_past->getSprite()->getLocalZOrder());
								Sand->setPosition(player_past->getSprite()->getPosition());

								Sand->runAction(Sequence::create(
									JumpTo::create(2, firetrap->getSprite()->getPosition(), 100, 1),
									CallFunc::create([=]() -> void
								{
									Sand->removeFromParent();
									firetrap->setAlive(false);
								}), nullptr));

								UI_Layer->removeChild(sb, true);
							}
							break;
						}
					}
					return true;
				}
				else
				{
					if (player_past->Take())
					{
						int ObjTag = player_past->getItemStatus();

						switch (ObjTag)
						{
						case 3:
							Map_BackGround_Past->removeChild(match->getSprite(), true);
							mt = Sprite::create("Obj/Objects/Match/Obj_Match.png");
							mt->setPosition(ToolButton->getPosition());
							UI_Layer->addChild(mt, ToolButton->getZOrder() + 1);
							mt->setGlobalZOrder(1000);
							break;
						case 13:
							Map_BackGround_Past->removeChild(sandbag->getSprite(), true);
							sb = Sprite::create("Obj/Objects/Sandbag/Obj_Sandbag.png");
							sb->setPosition(ToolButton->getPosition());
							UI_Layer->addChild(sb, ToolButton->getZOrder() + 1);
							sb->setGlobalZOrder(1000);
							break;
						}
					}
					else
					{

					}
					return true;
				}
			}
		}

		return false;
	};

	ToolListener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		ToolBright->stopAllActions();
		ToolBright->setVisible(false);
		ToolBright->setOpacity(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(ToolListener, ToolButton);

	//## 타임 버튼
	Time_Button = Sprite::create("Button/UI_Sandglass_Red_Btn.png");
	Time_Button->setPosition(Point(Win_Size.width * 0.5f, Win_Size.height * 0.1f));
	UI_Layer->addChild(Time_Button, 5);
	Time_Button->setGlobalZOrder(999);

	TimeBright = Sprite::create("Button/_Light.png");
	Time_Button->addChild(TimeBright, 10);
	TimeBright->setAnchorPoint(Vec2(0.1f, 0.1f));
	TimeBright->setVisible(false);
	TimeBright->setOpacity(0);

	auto Time_Listener = EventListenerTouchOneByOne::create();
	Time_Listener->setSwallowTouches(true);
	Time_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && !Opacity_Layer->isVisible())
		{
			TimeBright->runAction(Repeat::create(Bright->clone(), 999999));
			TimeBright->setVisible(true);
			if (!Time_State)
			{
				//## 현재 맵 끄고
				Map_BackGround_Now->setVisible(false);
				Game_Layer->stopAllActions();

				//## Now body 비활성
				auto NowChildSet = Map_BackGround_Now->getChildren();

				for (auto V : NowChildSet)
				{
					Obj* obj = reinterpret_cast<Obj*>(V->getUserData());
					if (obj != nullptr)
					{
						b2Body* objBody = obj->getBody();
						objBody->SetActive(false);
					}
				}

				//## Past body 활성
				auto PastChildSet = Map_BackGround_Past->getChildren();

				for (auto V : PastChildSet)
				{
					Obj* obj = reinterpret_cast<Obj*>(V->getUserData());
					if (obj != nullptr)
					{
						b2Body* objBody = obj->getBody();
						objBody->SetActive(true);
					}
				}

				//## 과거 플레이어 생성하고
				player_past = new Player();
				player_past->setPosition(player->getPosition());
				player_past->init();
				player_past->setFilpX(player->IsFlipX());
				Map_BackGround_Past->addChild(player_past->getSprite(), 5);
				player_past->setItemStatus(player->getItemStatus());
				player_past->getSprite()->setGlobalZOrder(200);
				Game_Layer->runAction(Follow::create(player_past->getSprite(), mapSize));

				//## variable init하고
				Time_State = true;
				player_past->setItemStatus(player->getItemStatus());
				Time_Button->setTexture("Button/UI_Sandglass_Blue_Btn.png");

				//## 맵 킨다
				Map_BackGround_Past->setVisible(true);
			}
			else
			{
				//## 맵 끄고
				Map_BackGround_Past->setVisible(false);
				Game_Layer->stopAllActions();

				//## variable init 하고
				Time_State = false;
				player->setItemStatus(player_past->getItemStatus());
				Time_Button->setTexture("Button/UI_Sandglass_Red_Btn.png");

				//## 과거 플레이어 삭제하고
				Map_BackGround_Past->removeChild(player_past->getSprite(), true);
				Game_Layer->runAction(Follow::create(player->getSprite(), mapSize));

				//## Now body 활성
				auto NowChildSet = Map_BackGround_Now->getChildren();

				for (auto V : NowChildSet)
				{
					Obj* obj = reinterpret_cast<Obj*>(V->getUserData());
					if (obj != nullptr)
					{
						b2Body* objBody = obj->getBody();
						objBody->SetActive(true);
					}
				}

				//## Past  body 비활성
				auto PastChildSet = Map_BackGround_Past->getChildren();

				for (auto V : PastChildSet)
				{
					Obj* obj = reinterpret_cast<Obj*>(V->getUserData());
					if (obj != nullptr)
					{
						b2Body* objBody = obj->getBody();
						objBody->SetActive(false);
					}
				}
				//## 맵킨다
				Map_BackGround_Now->setVisible(true);
			}

			return true;
		}

		return false;
	};

	Time_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		TimeBright->stopAllActions();
		TimeBright->setVisible(false);
		TimeBright->setOpacity(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Time_Listener, Time_Button);

	//## 키보드
	auto KeyBoard = EventListenerKeyboard::create();
	KeyBoard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			if (!Time_State)
				player->move(0);
			else
				player_past->move(0);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (!Time_State)
				player->move(1);
			else
				player_past->move(1);
			break;
		case EventKeyboard::KeyCode::KEY_W:
			if (!Time_State)
				player->Jump();
			else
				player_past->Jump();
			break;
		default:
			break;
		}
	};

	KeyBoard->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			if (!Time_State)
				player->Idle();
			else
				player_past->Idle();
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (!Time_State)
				player->Idle();
			else
				player_past->Idle();
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			Singleton::getInstance()->setClear(true);
			Director::getInstance()->replaceScene(ResultScene::createScene());
			break;
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyBoard, this);
}

void GameScene::CreateGroundWall(const int groundCnt)
{
	int i;

	std::vector<Sprite*> BackGround;
	std::vector<Sprite*> BackGround_Past;
	std::vector<Sprite*> BackGround_2;
	std::vector<Sprite*> BackGround_2_past;


	GroundWall = new Wall*[groundCnt];

	for (i = 0; i < groundCnt; ++i)
	{

		if (Singleton::getInstance()->IsChapter() == 1)
		{
			GroundWall[i] = new Wall();
			GroundWall[i]->setPosition(Vec2(Win_Size.width * (i + 0.5f), Win_Size.height * 0.1f));
			GroundWall[i]->init("Obj/Wall/Stage_01/BG_Ground.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 2);
			Sprite* _backGround = Sprite::create("Map/BackGround/Stage_01/BG_01.png");
			Sprite* _backGround_Past = Sprite::create("Map/BackGround/Stage_01/BG_01_Past.png");
			Sprite* _backGround_2 = Sprite::create("Map/BackGround/Stage_01/BG_02.png");
			Sprite* _backGround_2_past = Sprite::create("Map/BackGround/Stage_01/BG_02.png");
			_backGround->setPosition(Vec2(Win_Size.width * (i + 0.5f), Win_Size.height * 0.6f));
			_backGround_Past->setPosition(Vec2(Win_Size.width * (i + 0.5f), Win_Size.height * 0.6f));
			_backGround_2->setPosition(Vec2(Win_Size.width * (i + 0.5f), Win_Size.height * 0.6f));
			_backGround_2_past->setPosition(Vec2(Win_Size.width * (i + 0.5f), Win_Size.height * 0.6f));
			BackGround.push_back(_backGround);
			BackGround_Past.push_back(_backGround_Past);
			BackGround_2.push_back(_backGround_2);
			BackGround_2_past.push_back(_backGround_2_past);
		}

		else if (Singleton::getInstance()->IsChapter() == 2)
		{
			if (Singleton::getInstance()->IsLevel() == 1)
			{
				if (i == 7 || i == 6)
					continue;

				////땅
				//GroundWall[i] = new Wall();
				//GroundWall[i]->setPosition(Vec2(173 * i - 50, 72));
				//GroundWall[i]->init("Obj/Wall/Stage_02/Obj_Filled_Wall_02.png");
				//Overlap_Layer->addChild(GroundWall[i]->getSprite(), 2);

				//배경
				for (int a = 0; a < 3; a++)
				{
					Sprite* _backGround = Sprite::create("Map/BackGround/Stage_02/BG_02.png");
					Sprite* _backGround_Past = Sprite::create("Map/BackGround/Stage_02/BG_02_Past.png");
					_backGround->setPosition(Vec2(1280 * i - 640, 1080 + (a * 2100)));
					_backGround_Past->setPosition(Vec2(1280 * i - 640, 1080 + (a * 2100)));
					BackGround.push_back(_backGround);
					BackGround_Past.push_back(_backGround_Past);
				}
			}

			else if (Singleton::getInstance()->IsLevel() == 2)
			{
				if (i == 10 || i == 13 || i == 9 || i == 14)
				{

					for (int a = 0; a < 3; a++)
					{
						Sprite* _backGround = Sprite::create("Map/BackGround/Stage_02/BG_02.png");
						Sprite* _backGround_Past = Sprite::create("Map/BackGround/Stage_02/BG_02_Past.png");
						_backGround->setPosition(Vec2(1280 * i - 640, 3240 + (2160 * i)));
						_backGround_Past->setPosition(Vec2(1280 * i - 640, 3249 + (2160 * i)));
						BackGround.push_back(_backGround);
						BackGround_Past.push_back(_backGround_Past);
					}
					continue;
				}

				////땅
				//GroundWall[i] = new Wall();
				//GroundWall[i]->setPosition(Vec2(173 * i - 50, 72));
				//GroundWall[i]->init("Obj/Wall/Stage_02/Obj_Filled_Wall_02.png");
				//Overlap_Layer->addChild(GroundWall[i]->getSprite(), 2);

				//배경
				Sprite* _backGround = Sprite::create("Map/BackGround/Stage_02/BG_02.png");
				Sprite* _backGround_Past = Sprite::create("Map/BackGround/Stage_02/BG_02_Past.png");
				_backGround->setPosition(Vec2(1280 * i - 640, 1080));
				_backGround_Past->setPosition(Vec2(1280 * i - 640, 1080));
				BackGround.push_back(_backGround);
				BackGround_Past.push_back(_backGround_Past);
			}
		}

	}

	for (auto A : BackGround)
		Back_Layer->addChild(A, 1);
	for (auto B : BackGround_Past)
		Back_Layer->addChild(B, 1);
	for (auto C : BackGround_2)
		Back_Layer->addChild(C, 1);
	for (auto D : BackGround_2_past)
		Back_Layer->addChild(D, 1);
}

void GameScene::CreateCastleWall(const int count, const Vec2 & Pos)
{
	GroundWall = new Wall*[count];

	for (int i = 0; i <= count; i++)
	{
		GroundWall[i] = new Wall();

		if (i == 0)
		{
			log(" (begin) ");
			GroundWall[i]->setPosition(Vec2(40 + Pos.x, Pos.y));
			GroundWall[i]->init("Obj/Wall/Stage_02/BG_Ground_2_01.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);
		}
		else if (i == count)
		{
			log(" (end) ");
			GroundWall[i]->setPosition(GroundWall[count - 1]->getPosition() + Vec2(100, 0));
			GroundWall[i]->init("Obj/Wall/Stage_02/BG_Ground_2_03.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);
		}
		else
		{
			log(" (middle) %d ", i);
			GroundWall[i]->setPosition(Vec2(173 * i + Pos.x - 40, Pos.y));
			GroundWall[i]->init("Obj/Wall/Stage_02/BG_Ground_2_02.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);
		}
	}
}

void GameScene::CreatefilledWall(const int count, const Vec2 & Pos)
{
	GroundWall = new Wall*[count];

	for (int i = 0; i <= count; i++)
	{
		GroundWall[i] = new Wall();

		if (i == 0)
		{
			log(" (begin) ");
			GroundWall[i]->setPosition(Vec2(40 + Pos.x, Pos.y));
			GroundWall[i]->init("Obj/Wall/Stage_02/Obj_Filled_Wall_01.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);

		}
		else if (i == count)
		{
			log(" (end) ");
			GroundWall[i]->setPosition(GroundWall[count - 1]->getPosition() + Vec2(100, 0));
			GroundWall[i]->init("Obj/Wall/Stage_02/Obj_Filled_Wall_03.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);

		}
		else
		{
			log(" (middle) %d ", i);
			GroundWall[i]->setPosition(Vec2(173 * i + Pos.x - 40, Pos.y));
			GroundWall[i]->init("Obj/Wall/Stage_02/Obj_Filled_Wall_02.png");
			Overlap_Layer->addChild(GroundWall[i]->getSprite(), 4);
		}
	}
}

bool GameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void GameScene::onTouchMoved(Touch * touch, Event * unused_event)
{

}

void GameScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}
