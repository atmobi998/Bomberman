#include "MainMenu.h"
#include "cocos2d.h"
#include "common.h"
#include "SoundGame.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
CCScene* MainMenu::scene()
{
	CCScene* scene = CCScene::create();
	MainMenu* mainLayer = MainMenu::create();
	scene->addChild(mainLayer);
	return scene;
}

bool MainMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setKeypadEnabled(true);	
	mainMenuLayer = Layout::create();
	mainMenuLayer=(Layout*)(GUIReader::shareReader()->widgetFromJsonFile("MainMenu_Canvas.json"));
	this->addChild(mainMenuLayer);
	Button *btnPlay= (Button*)(Helper::seekWidgetByName(mainMenuLayer,"Button_Play"));
	btnPlay->setPressedActionEnabled(true);
	btnPlay->addTouchEventListener((Ref*)this,toucheventselector(MainMenu::onStart));
	Button *btnSound=(Button*)(Helper::seekWidgetByName(mainMenuLayer,"Button_Sound"));
	btnSound->setPressedActionEnabled(true);
	btnSound->addTouchEventListener((Ref*)this,toucheventselector(MainMenu::turnSound));
	Button *btnmoregame=(Button*)(Helper::seekWidgetByName(mainMenuLayer,"Button_Moregame"));
	btnmoregame->setPressedActionEnabled(true);
	btnmoregame->addTouchEventListener((Ref*)this,toucheventselector(MainMenu::moregame));
	Button *btnsharegame=(Button*)(Helper::seekWidgetByName(mainMenuLayer,"Button_Sharegame"));
	btnsharegame->setPressedActionEnabled(true);
	btnsharegame->addTouchEventListener((Ref*)this,toucheventselector(MainMenu::sharegame));
	sound = UserDefault::getInstance()->getBoolForKey(KEY_SOUND,true);
	if (sound)
	{
		btnSound->loadTextures("musicON.png", "musicON.png","", UI_TEX_TYPE_LOCAL);
	}
	else
	{
		btnSound->loadTextures("musicOFF.png", "musicOFF.png","", UI_TEX_TYPE_LOCAL);
	}
	
	return true;
}

void MainMenu::onStart(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		//CCScene *pscene =CCTransitionSlideInR::create(0.5, Level::scene());
		CCScene *pscene =Level::scene();
		if (pscene != NULL)
		{
			CCDirector::sharedDirector()->replaceScene(pscene);
		}
	}
}

void MainMenu::turnSound(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		if (sound)
		{
			sound=false;
			UserDefault::getInstance()->setBoolForKey(KEY_SOUND,false);
			UserDefault::getInstance()->flush();
			Button *btn= (Button*)pSender;
			btn->loadTextures("musicOFF.png","musicOFF.png","",UI_TEX_TYPE_LOCAL);			
		}
		else
		{
			sound=true;
			UserDefault::getInstance()->setBoolForKey(KEY_SOUND,true);
			UserDefault::getInstance()->flush();
			Button *btn= (Button*)pSender;
			btn->loadTextures("musicON.png","musicON.png","",UI_TEX_TYPE_LOCAL);
		
		}
	}
}

void MainMenu::sharegame(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		
	}
}

void MainMenu::moregame(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		
	}
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode==EventKeyboard::KeyCode::KEY_ESCAPE)
	{

	}
}
