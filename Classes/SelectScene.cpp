#include "SelectScene.h"
#include "Singleton.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto Background = Sprite::create("Map/BackGround/BG_Chapter_Select.png");
	Background->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	this->addChild(Background, 0);

	Sprite** Levels[] = { &Level_1, &Level_2, &Level_3, &Level_4, &Level_5 };

	for (int i = 0; i < 5; ++i)
	{
		Sprite* &Level = *Levels[i];
		int ClearStage = Singleton::getInstance()->isWhereClear();
		int ClearChapter = Singleton::getInstance()->isWhereChapter();
		int setChapter = Singleton::getInstance()->IsChapter();
		log("(%d)", ClearStage);
		int j;

		if (ClearChapter > setChapter)
		{
			Level = Sprite::create("Select/Level/01.png");
			Level->setTag(1);
		}
		else if (ClearStage > i)
		{
			Level = Sprite::create("Select/Level/01.png");
			Level->setTag(1);
		}
		else if (ClearStage == i)
		{
			Level = Sprite::create("Select/Level/02.png");
			Level->setTag(1);
		}
		else
		{
			Level = Sprite::create("Select/Level/03.png");
			Level->setTag(2);
		}
		Level->setPosition(winSize.width * (0.1f + 0.25f * i), winSize.height * 0.5f);
		this->addChild(Level, 1);
	}

	Option = Layer::create();
	this->addChild(Option, 1);
	Option->setVisible(false);

	Opacity_Layer = LayerColor::create(Color4B(0, 0, 0, 210));
	Opacity_Layer->setVisible(false);
	Option->addChild(Opacity_Layer, 0);

	winSize = Director::getInstance()->getVisibleSize();

	Option_button = Sprite::create("Button/Option/UI_Pause_Btn.png");
	Option_button->setPosition(winSize.width * 0.95f, getContentSize().height*0.93f);

	this->addChild(Option_button, 1);

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
			log("Touch 1");
			Option->setVisible(true);
			Opacity_Layer->setVisible(true);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Option_Listener, Option_button);


	Bgm_button = Sprite::create("Button/Option/Sound/UI_BGM_Btn.png");
	Bgm_button->setPosition(winSize.width*0.5 - 100, winSize.height*0.5);
	auto BGM = Label::createWithTTF("BGM", "fonts/SNCB.ttf", 18);
	BGM->setPosition(winSize.width*0.5 - 100, winSize.height*0.4);
	Option->addChild(BGM, 1);
	Option->addChild(Bgm_button, 10);

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
			log("Touch 1");

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
			Bgm_button->setTexture("Button/Option/Sound/UI_BGM_Click_Btn.png");
			num++;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Grandpapa_Eleven_Month.wav", true);
			Bgm_button->setTexture("Button/Option/Sound/UI_BGM_Btn.png");
			num = 0;
		}

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Bgm_Listener, Bgm_button);

	uiline = Sprite::create("Obj/Lines/Line_1.png");
	uiline->setPosition(winSize.width * 0.5, winSize.height * 0.7);
	Option->addChild(uiline, 5);

	uiline2 = Sprite::create("Obj/Lines/Line_2.png");
	uiline2->setPosition(winSize.width * 0.5, winSize.height*0.3);
	Option->addChild(uiline2, 5);

	Sfx_button = Sprite::create("Button/Option/Sound/UI_SFX_Btn.png");
	Sfx_button->setPosition(winSize.width*0.35 - 100, winSize.height*0.5);
	auto SFX = Label::createWithTTF("SFX", "fonts/SNCB.ttf", 18);
	SFX->setPosition(winSize.width*0.35 - 100, winSize.height*0.4);
	Option->addChild(SFX, 1);
	Option->addChild(Sfx_button, 5);

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
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Sfx_Listener, Sfx_button);

	auto stoplabel = Label::createWithTTF("Pause", "fonts/SNCB.ttf", 46);
	stoplabel->setPosition(winSize.width * 0.5, winSize.height*0.7);
	Option->addChild(stoplabel, 70);

	resume = Sprite::create("Button/Option/Back/UI_Resume_Btn.png");
	resume->setPosition(winSize.width * 0.8 - 100, winSize.height*0.5);
	auto STOP = Label::createWithTTF("MENU", "fonts/SNCB.ttf", 18);
	STOP->setPosition(winSize.width * 0.8 - 100, winSize.height*0.4);
	Option->addChild(STOP, 1);
	Option->addChild(resume, 5);

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
			log("Touch 1");

			resume->setScale(0.7f);
			return true;
		}
		return false;
	};

	resume_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		resume->setScale(1);

		Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene(), Color3B(0, 0, 0)));
		log("Touch 2");

		return true;

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(resume_Listener, resume);

	close = Sprite::create("Button/Option/Back/UI_Menu_Btn.png");
	close->setPosition(winSize.width*0.65 - 100, winSize.height*0.5);
	auto MENU = Label::createWithTTF("Quit", "fonts/SNCB.ttf", 18);
	MENU->setPosition(winSize.width*0.65 - 100, winSize.height*0.4);
	Option->addChild(MENU, 1);
	Option->addChild(close, 5);

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
			log("Touch 1");
			close->setScale(0.7f);

			return true;
		}
		return false;
	};

	close_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		close->setScale(1.0f);
		Option->setVisible(false);


		log("Touch 2");

		return true;

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(close_Listener, close);

	int cnt = 0;
	auto level_Listener = EventListenerTouchOneByOne::create();
	level_Listener->setSwallowTouches(true);
	level_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		const Vec2 locationInNode = touch->getLocation();

		if (Level_1->boundingBox().containsPoint(locationInNode) && Level_1->getTag() != 2)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Singleton::getInstance()->setLevel(1);
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(0, 0, 0)));
		}

		else if (Level_2->boundingBox().containsPoint(locationInNode) && Level_2->getTag() != 2)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

			Singleton::getInstance()->setLevel(2);
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(0, 0, 0)));
		}
		else if (Level_3->boundingBox().containsPoint(locationInNode) && Level_3->getTag() != 2)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

			Singleton::getInstance()->setLevel(3);
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(0, 0, 0)));
		}
		else if (Level_4->boundingBox().containsPoint(locationInNode) && Level_4->getTag() != 2)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

			Singleton::getInstance()->setLevel(4);
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(0, 0, 0)));
		}
		else if (Level_5->boundingBox().containsPoint(locationInNode) && Level_5->getTag() != 2)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

			Singleton::getInstance()->setLevel(5);
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(0, 0, 0)));
		}

		return true;
	};


	level_Listener->onTouchMoved = [this](Touch* touch, Event*)
	{
		const Vec2 delta = touch->getDelta();
		Sprite* levels[] = { Level_1, Level_2, Level_3, Level_4, Level_5 };

		for (int i = 0; i < 5; i++)
		{
			Sprite* curSprite = levels[i];
			const Vec2 position = curSprite->getPosition() + Vec2(delta.x, 0.f);
			curSprite->setPosition(Vec2(MIN(MAX(position.x, winSize.width * (0.1f + 0.25f * (i - 1))), winSize.width * (0.1f + 0.25f * i)), position.y));
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(level_Listener->clone(), Level_1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(level_Listener->clone(), Level_2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(level_Listener->clone(), Level_3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(level_Listener->clone(), Level_4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(level_Listener, Level_5);

	return true;
}

bool SelectScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void SelectScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void SelectScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}
