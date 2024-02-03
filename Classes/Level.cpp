#include "MainMenu.h"
#include "cocos2d.h"
#include "common.h"
#include "Level.h"
#include "SoundGame.h"
Level::Level()
{
}

Level::~Level()
{
}

CCScene* Level::scene()
{
	CCScene* scene = CCScene::create();
	Level* layer = Level::create();
	scene->addChild(layer);
	return scene;
}

bool Level::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	levelLayer = Layout::create();
	levelLayer=(Layout*)(GUIReader::getInstance()->widgetFromJsonFile("Level_Canvas.json"));
	Button *btnBack= (Button*)(Helper::seekWidgetByName(levelLayer,"Button_Back"));
	btnBack->setPressedActionEnabled(true);
	btnBack->addTouchEventListener((Ref*)this,toucheventselector(Level::onBack));
	this->addChild(levelLayer);
	this->schedule(schedule_selector(Level::update));
	UserDefault::getInstance()->setIntegerForKey(KEY_LEVEL_OPEN,40);
	/*UserDefault::getInstance()->setIntegerForKey("star4Level1",0);*/
	int levelOpen = UserDefault::getInstance()->getIntegerForKey(KEY_LEVEL_OPEN,1);
	for (int i = 1; i <= levelOpen ; i++)
	{
		char strLevel[20];
		sprintf(strLevel, "Button_Level%d",i);
		Button* m_pBtnLevel = (Button*)(Helper::seekWidgetByName(levelLayer,strLevel));
		m_pBtnLevel->setTag(i);
		m_pBtnLevel->setTouchEnabled(true);
		m_pBtnLevel->setPressedActionEnabled(false);
		m_pBtnLevel->setOpacity(255);
		// add touch

		m_pBtnLevel->addTouchEventListener((Ref*)this, toucheventselector(Level::onStart));
		char strStar[20];
		sprintf(strStar, "star4Level%d", i);
		int star4Level = UserDefault::getInstance()->getIntegerForKey(strStar,0);
		char str[20];
		sprintf(str, "Star_level%d",i);
		ImageView* img = (ImageView*)(Helper::seekWidgetByName(levelLayer,str));
		switch (star4Level)
		{
		case  0:
			img->loadTexture("star1.png",UI_TEX_TYPE_LOCAL);
			break;
		case  1:
			img->loadTexture("star2.png",UI_TEX_TYPE_LOCAL);
			break;
		case  2:
			img->loadTexture("star3.png",UI_TEX_TYPE_LOCAL);
			break;
		case  3:
			img->loadTexture("star4.png",UI_TEX_TYPE_LOCAL);
			break;
		default:
			break;
		}
	}
	for (int i =levelOpen+1; i <=40; i++)
	{
		char strLevel[20];
		sprintf(strLevel, "Button_Level%d",i);
		Button* m_pBtnLevel = (Button*)(Helper::seekWidgetByName(levelLayer,strLevel));
		m_pBtnLevel->setTouchEnabled(false);
		if (i<=10)
		{
			m_pBtnLevel->loadTextureNormal("fac_un.png",UI_TEX_TYPE_LOCAL);
		}
		else if (i>10&&i<=20)
		{
			m_pBtnLevel->loadTextureNormal("war_un.png",UI_TEX_TYPE_LOCAL);
		}
		else if (i>20&&i<=30)
		{
			m_pBtnLevel->loadTextureNormal("cou_un.png",UI_TEX_TYPE_LOCAL);
		}
		else
		{
			m_pBtnLevel->loadTextureNormal("hig_un.png",UI_TEX_TYPE_LOCAL);
		}
		char str[20];
		sprintf(str, "Star_level%d",i);
		ImageView* img = (ImageView*)(Helper::seekWidgetByName(levelLayer,str));
		img->setVisible(false);
	}
	return true;
}

void Level::onStart(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		Button *btn= (Button*)pSender;
		int levelselect =btn->getTag();
		if (levelselect<=10)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,1);
		}
		else if (levelselect>10&&levelselect<=20)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,2);
		}
		else if (levelselect>20&&levelselect<=30)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,3);
		}
		else
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,4);
		}
		// CCLog("chon level:%d",btn->getTag());
		UserDefault::getInstance()->setIntegerForKey(KEY_SELECT_LEVEL,btn->getTag());
		UserDefault::getInstance()->flush();
		//CCScene *pscene =CCTransitionSlideInR::create(0.5, GameScene::scene());
		CCScene *pscene =GameScene::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
	}
}
void Level::onBack(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		//CCScene *pscene =CCTransitionSlideInL::create(0.5, MainMenu::scene());
		CCScene *pscene =MainMenu::scene();
		Director::getInstance()->replaceScene(pscene);
	}
}
void Level::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode==EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//CCScene *pscene =CCTransitionSlideInL::create(0.5, MainMenu::scene());
		CCScene *pscene = MainMenu::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
	}
}
