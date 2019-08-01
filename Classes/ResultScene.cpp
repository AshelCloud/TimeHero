#include "ResultScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene * ResultScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ResultScene::create();

	scene->addChild(layer);

	return scene;
}

bool ResultScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getVisibleSize();
	Opacity = LayerColor::create(Color4B(0, 0, 0, 185));
	this->addChild(Opacity, 255);

	auto label = Label::createWithTTF(StringUtils::format("Chapter - %d\nSatge - %d", Singleton::getInstance()->IsChapter(), Singleton::getInstance()->IsLevel()),
		"fonts/SNCB.ttf", 40.f);
	label->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.7f));

	if (Singleton::getInstance()->isClear())
	{
		if (Singleton::getInstance()->IsLevel() == 3)
		{
			Singleton::getInstance()->setWhereChapter(Singleton::getInstance()->isWhereChapter() + 1);
			Singleton::getInstance()->setWhereClear(0);
			Singleton::getInstance()->setLevel(1);
		}
		else
		{
			Singleton::getInstance()->setWhereClear(Singleton::getInstance()->IsLevel());
			Singleton::getInstance()->setLevel(Singleton::getInstance()->IsLevel() + 1);
		}

		if (Singleton::getInstance()->IsChapter() == 1)
		{
			auto background = Sprite::create("Map/BackGround/Stage_01/BG_01.png");
			background->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background, 1);

			auto background_2 = Sprite::create("Map/BackGround/Stage_01/BG_02.png");
			background_2->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background_2, 2);
		}

		else if (Singleton::getInstance()->IsChapter() == 2)
		{
			auto background = Sprite::create("Map/BackGround/Credit/End.png");
			background->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background, 1);
		}

		Opacity->addChild(label, 5);

		auto explain = Sprite::create("Clear/01.png");
		explain->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.6f));
		Opacity->addChild(explain, 4);

		auto stage_Clear = Sprite::create("Clear/Stage Clear.png");
		stage_Clear->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		Opacity->addChild(stage_Clear, 4);

		auto clearlabel = Label::createWithTTF("Stage Clear", "fonts/SNCB.ttf", 40.f);
		clearlabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		Opacity->addChild(clearlabel, 5);

		Sprite* back = Sprite::create("Clear/Resume.png");
		back->setPosition(Vec2(winSize.width * 0.2f, winSize.height * 0.2f));
		Opacity->addChild(back, 4);

		auto back_listener = EventListenerTouchOneByOne::create();
		back_listener->setSwallowTouches(true);
		back_listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
				Director::getInstance()->replaceScene(MainScene::createScene());
				return true;
			}
			return false;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(back_listener, back);

		Sprite* next = Sprite::create("Clear/Next_Stage.png");
		next->setPosition(Vec2(winSize.width * 0.8f, winSize.height * 0.2f));
		Opacity->addChild(next, 4);

		auto next_listener = EventListenerTouchOneByOne::create();
		next_listener->setSwallowTouches(true);
		next_listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
				Director::getInstance()->replaceScene(GameScene::createScene());
				return true;
			}
			return false;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(next_listener, next);

		Sprite* _template = Sprite::create("Clear/Menu.png");
		_template->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.2f));
		Opacity->addChild(_template, 4);

		auto _template_listener = EventListenerTouchOneByOne::create();
		_template_listener->setSwallowTouches(true);
		_template_listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
				Director::getInstance()->replaceScene(MainScene::createScene());
				return true;
			}
			return false;
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(_template_listener, _template);
	}

	else
	{
		if (Singleton::getInstance()->IsChapter() == 1)
		{
			auto background = Sprite::create("Map/BackGround/Stage_01/BG_01.png");
			background->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background, 1);

			auto background_2 = Sprite::create("Map/BackGround/Stage_01/BG_02.png");
			background_2->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background_2, 2);
		}

		else if (Singleton::getInstance()->IsChapter() == 2)
		{
			auto background = Sprite::create("Map/BackGround/Credit/End.png");
			background->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
			this->addChild(background, 1);
		}

		auto explain = Sprite::create("Clear/01.png");
		explain->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.6f));
		Opacity->addChild(explain, 4);

		Opacity->addChild(label, 5);

		auto stage_Failed = Sprite::create("Clear/Stage Failed.png");
		stage_Failed->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		Opacity->addChild(stage_Failed, 4);

		auto faildelabel = Label::createWithTTF("Stage Failed", "fonts/SNCB.ttf", 40.f);
		faildelabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		Opacity->addChild(faildelabel,5);

		Sprite* _template = Sprite::create("Clear/Restart.png");
		_template->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.2f));
		Opacity->addChild(_template, 4);

		auto _template_listener = EventListenerTouchOneByOne::create();
		_template_listener->setSwallowTouches(true);
		_template_listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
				Director::getInstance()->replaceScene(GameScene::createScene());
				return true;
			}
			return false;
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(_template_listener, _template);
	}

	return true;
}

bool ResultScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void ResultScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void ResultScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}
