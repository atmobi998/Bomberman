#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Level.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class MainMenu :
	public Layer
{
public:
	virtual bool init();

	static Scene* scene();

	CREATE_FUNC(MainMenu);
private:
	CC_SYNTHESIZE(Layout*, mainMenuLayer,MainLayer);
	void onStart(Ref* pSender, TouchEventType type);
	void sharegame(Ref* pSender, TouchEventType type);
	void moregame(Ref* pSender, TouchEventType type);
	void turnSound(Ref* pSender, TouchEventType type);
	bool sound;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};
