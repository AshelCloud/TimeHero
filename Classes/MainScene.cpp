#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "Singleton.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/BGM/BGM.wav");
	Win_Size = Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);//터치 활성화
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//터지모드 설정  한번 눌르면

	Opacity_Layer = LayerColor::create(Color4B(0, 0, 0, 135));
	Opacity_Layer->setVisible(false);
	this->addChild(Opacity_Layer, 4);

	credit = LayerColor::create(Color4B(0, 0, 0, 135));
	this->addChild(credit, 3);
	credit->setVisible(false);

	auto Background = Sprite::create("Map/BackGround/BG_Chapter_Select.png");
	Background->setPosition(Win_Size.width * 0.5, Win_Size.height * 0.5);
	this->addChild(Background, 0);

	SelectScene();
	Buttoninit();
	creditinit();
}

void MainScene::SelectScene()
{
	int ClearChapter = Singleton::getInstance()->isWhereChapter();

	Chapter_1 = Sprite::create();
	Chapter_2 = Sprite::create();
	ChapterLight = Sprite::create();

	auto Chapter_Animation = Animation::create();
	Chapter_Animation->setDelayPerUnit(0.5f);
	for (int i = 1; i < 9; ++i)
	{
		Chapter_Animation->addSpriteFrameWithFileName(StringUtils::format("Animate/Chapter/Chapter_Select_Btn_Smoke_%02d.png", i));
	}

	auto Chapter_animate = Animate::create(Chapter_Animation);
	Chapter_animate->retain();

	ChapterLight->runAction(RepeatForever::create(Chapter_animate));

	switch (ClearChapter)
	{
	case 1:
		Chapter_1->setTexture("Select/Chapter/Chapter1_Select_Btn_02.png");
		Chapter_1->setPosition(Vec2(Win_Size.width * 0.3f, Win_Size.height * 0.5f));
		this->addChild(Chapter_1, 1);
		Chapter_2->setTexture("Select/Chapter/Chapter2_Select_Btn.png");
		Chapter_2->setPosition(Vec2(Win_Size.width * 0.7f, Win_Size.height * 0.5f));
		this->addChild(Chapter_2, 1);
		Chapter_1->addChild(ChapterLight, 2);
		ChapterLight->setAnchorPoint(Vec2(0.f, 0.f));
		break;
	case 2:
		Chapter_1->setTexture("Select/Chapter/Chapter1_Select_Btn_03.png");
		Chapter_1->setPosition(Vec2(Win_Size.width * 0.3f, Win_Size.height * 0.5f));
		this->addChild(Chapter_1, 1);
		Chapter_2->setTexture("Select/Chapter/Chapter2_Select_Btn_02.png");
		Chapter_2->setPosition(Vec2(Win_Size.width * 0.7f, Win_Size.height * 0.5f));
		this->addChild(Chapter_2, 1);
		Chapter_2->addChild(ChapterLight, 2);
		ChapterLight->setAnchorPoint(Vec2(0.f, 0.f));
		break;
	}

	auto Chapter_Select = EventListenerTouchOneByOne::create();
	Chapter_Select->setSwallowTouches(true);
	Chapter_Select->onTouchBegan = [&](Touch* touch, Event* event)
	{
		if (Chapter_1->getBoundingBox().containsPoint(touch->getLocation()))
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			Singleton::getInstance()->setChapter(1);
			Director::getInstance()->replaceScene(SelectScene::createScene());

			return true;
		}
		else if (Chapter_2->getBoundingBox().containsPoint(touch->getLocation()) && Singleton::getInstance()->isWhereChapter() >= 2)
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/Screen_Trans.wav");
			Singleton::getInstance()->setChapter(2);
			Director::getInstance()->replaceScene(SelectScene::createScene());
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Chapter_Select, Chapter_1);
}

void MainScene::Buttoninit()
{
	//Sprite initialize
	auto Option_button = Sprite::create("Button/Option/UI_Pause_Btn.png");
	Option_button->setPosition(Win_Size.width * 0.95f, Win_Size.height * 0.93f);
	this->addChild(Option_button, 2);

	auto Online = Sprite::create("Obj/Lines/Line_1.png");
	Online->setPosition(Win_Size.width * 0.5, Win_Size.height*0.7);
	Opacity_Layer->addChild(Online, 5);

	auto Underline = Sprite::create("Obj/Lines/Line_2.png");
	Underline->setPosition(Win_Size.width * 0.5, Win_Size.height*0.3);
	Opacity_Layer->addChild(Underline, 5);

	auto Pauselabel = Label::createWithTTF("Pause", "fonts/SNCB.ttf", 46);
	Pauselabel->setPosition(Win_Size.width * 0.5, Win_Size.height*0.7);
	Opacity_Layer->addChild(Pauselabel, 5);
	
	Bgm_button = Sprite::create();

	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		Bgm_button->setTexture("Button/Option/Sound/UI_BGM_Btn.png");
	else
		Bgm_button->setTexture("Button/Option/Sound/UI_BGM_Click_Btn.png");

	Bgm_button->setPosition(Win_Size.width*0.2f, Win_Size.height*0.5f);
	Opacity_Layer->addChild(Bgm_button, 10);
	auto BGM = Label::createWithTTF("BGM", "fonts/SNCB.ttf", 18);
	BGM->setPosition(Win_Size.width*0.2, Win_Size.height*0.4);
	Opacity_Layer->addChild(BGM, 1);

	auto SFX_button = Sprite::create("Button/Option/Sound/UI_SFX_Btn.png");
	SFX_button->setPosition(Win_Size.width*0.35f, Win_Size.height*0.5f);
	Opacity_Layer->addChild(SFX_button, 5);

	auto SFX = Label::createWithTTF("SFX", "fonts/SNCB.ttf", 18);
	SFX->setPosition(Win_Size.width*0.35, Win_Size.height*0.4);
	Opacity_Layer->addChild(SFX, 1);

	auto credits = Sprite::create("Button/Option/End/UI_Credit_Btn.png");
	credits->setPosition(Win_Size.width * 0.8f, Win_Size.height * 0.5f);
	Opacity_Layer->addChild(credits);
	auto credit_Label = Label::createWithTTF("CREDIT", "fonts/SNCB.ttf", 18);
	credit_Label->setPosition(Win_Size.width*0.8, Win_Size.height*0.4);
	Opacity_Layer->addChild(credit_Label, 1);

	auto CloseButton = Sprite::create("Button/Option/Back/UI_Menu_Btn.png");
	CloseButton->setPosition(Win_Size.width*0.5f, Win_Size.height*0.5f);
	Opacity_Layer->addChild(CloseButton, 5);
	auto MENU = Label::createWithTTF("QUIT", "fonts/SNCB.ttf", 18);
	MENU->setPosition(Win_Size.width*0.5, Win_Size.height*0.4);
	Opacity_Layer->addChild(MENU, 1);

	auto ResumeButton = Sprite::create("Button/Option/Back/UI_Resume_Btn.png");
	ResumeButton->setPosition(Win_Size.width * 0.65f, Win_Size.height * 0.5f);
	Opacity_Layer->addChild(ResumeButton, 5);
	auto STOP = Label::createWithTTF("CLOSE", "fonts/SNCB.ttf", 18);
	STOP->setPosition(Win_Size.width * 0.65, Win_Size.height*0.4);
	Opacity_Layer->addChild(STOP, 1);

	//Listener initialize
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
			Opacity_Layer->setVisible(true);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Option_Listener, Option_button);

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
			return true;
		}
		return false;
	};

	Bgm_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			Singleton::getInstance()->setMusic(false);
			Bgm_button->setTexture("Button/UI_BGM_Click_Btn.png");
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/BGM/BGM.wav", true);
			Singleton::getInstance()->setMusic(true);
			Bgm_button->setTexture("Button/UI_BGM_Btn.png");
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Bgm_Listener, Bgm_button);

	auto SFX_Listener = EventListenerTouchOneByOne::create();
	SFX_Listener->setSwallowTouches(true);
	SFX_Listener->onTouchBegan = [&](Touch* touch, Event* event)
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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(SFX_Listener, SFX_button);

	auto Resume_Listener = EventListenerTouchOneByOne::create();
	Resume_Listener->setSwallowTouches(true);
	Resume_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			Opacity_Layer->setVisible(false);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Resume_Listener, ResumeButton);

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
			return true;
		}
		return false;
	};

	close_Listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		Director::getInstance()->end();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(close_Listener, CloseButton);

	auto credits_Listener = EventListenerTouchOneByOne::create();
	credits_Listener->setSwallowTouches(true);
	credits_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Menu/Bt_Click.wav");
			credit->setVisible(true);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(credits_Listener, credits);
}

void MainScene::creditinit()
{
	auto background = Sprite::create("Map/BackGround/Credit/End.png");
	background->setPosition(Win_Size.width * 0.5f, Win_Size.height * 0.5f);
	credit->addChild(background);

	auto kyeongmin = Sprite::create("Face/KyeongMin.png");
	kyeongmin->setPosition(Win_Size.width * 0.1f, Win_Size.height * 0.88f);
	credit->addChild(kyeongmin);

	auto jaehong = Sprite::create("Face/JaeHong.png");
	jaehong->setPosition(Win_Size.width * 0.1f, Win_Size.height * 0.38f);
	credit->addChild(jaehong);

	auto namgyu = Sprite::create("Face/NamGyu.png");
	namgyu->setPosition(Win_Size.width * 0.1f, Win_Size.height * 0.13f);
	credit->addChild(namgyu);

	auto minseo = Sprite::create("Face/MinSeo.png");
	minseo->setPosition(Win_Size.width * 0.1f, Win_Size.height * 0.63f);
	credit->addChild(minseo);

	auto jiu = Sprite::create("Face/JiU.png");
	jiu->setPosition(Win_Size.width * 0.5f, Win_Size.height * 0.88f);
	credit->addChild(jiu);

	auto soyeong = Sprite::create("Face/kms.png");
	soyeong->setPosition(Win_Size.width * 0.5f, Win_Size.height * 0.6f);
	credit->addChild(soyeong);

	auto c_back_button = Sprite::create("Button/Option/Back/UI_Resume_Btn.png");
	c_back_button->setPosition(Win_Size.width * 0.9f, Win_Size.height * 0.1f);
	credit->addChild(c_back_button);

	auto back_Listener = EventListenerTouchOneByOne::create();
	back_Listener->setSwallowTouches(true);
	back_Listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Menu/Bt_Close.wav");
			credit->setVisible(false);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(back_Listener, c_back_button);

	auto k_m = Label::create("김경민(팀장)", "fonts/SNCB.ttf", 30);
	k_m->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.91f);
	credit->addChild(k_m);

	auto k_m_2 = Label::create("프로그래밍", "fonts/SNCB.ttf", 30);
	k_m_2->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.85f);
	credit->addChild(k_m_2);

	auto n_g = Label::create("허남규", "fonts/SNCB.ttf", 30);
	n_g->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.16f);
	credit->addChild(n_g);

	auto j_h_2 = Label::create("프로그래밍", "fonts/SNCB.ttf", 30);
	j_h_2->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.10f);
	credit->addChild(j_h_2);

	auto j_h = Label::create("정재홍", "fonts/SNCB.ttf", 30);
	j_h->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.41f);
	credit->addChild(j_h);

	auto n_g_2 = Label::create("프로그래밍", "fonts/SNCB.ttf", 30);
	n_g_2->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.35f);
	credit->addChild(n_g_2);

	auto m_s = Label::create("신민서", "fonts/SNCB.ttf", 30);
	m_s->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.66f);
	credit->addChild(m_s);

	auto m_s_2 = Label::create("프로그래밍", "fonts/SNCB.ttf", 30);
	m_s_2->setPosition(Win_Size.width * 0.3f, Win_Size.height * 0.6f);
	credit->addChild(m_s_2);

	auto j_u = Label::create("손지우", "fonts/SNCB.ttf", 30);
	j_u->setPosition(Win_Size.width * 0.7f, Win_Size.height * 0.91f);
	credit->addChild(j_u);

	auto j_u_2 = Label::create("기획", "fonts/SNCB.ttf", 30);
	j_u_2->setPosition(Win_Size.width * 0.7f, Win_Size.height * 0.85f);
	credit->addChild(j_u_2);

	auto s_y = Label::create("이소영", "fonts/SNCB.ttf", 30);
	s_y->setPosition(Win_Size.width * 0.7f, Win_Size.height * 0.63f);
	credit->addChild(s_y);

	auto s_y_2 = Label::create("그래픽", "fonts/SNCB.ttf", 30);
	s_y_2->setPosition(Win_Size.width * 0.7f, Win_Size.height * 0.57f);
	credit->addChild(s_y_2);

	auto e_p = Label::create("Feat.Lim News Teacher", "fonts/SNCB.ttf", 20);
	e_p->setPosition(Win_Size.width * 0.7f, Win_Size.height * 0.1f);
	credit->addChild(e_p);
}
bool MainScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void MainScene::onTouchMoved(Touch * touch, Event * unused_event)
{

}

void MainScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}