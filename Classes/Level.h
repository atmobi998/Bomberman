#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class Level :
	public Layer
{
public:
	Level();
	~Level();

	virtual bool init();

	static Scene* scene();

	CREATE_FUNC(Level);
private:
	CC_SYNTHESIZE(Layout*, levelLayer, LevelLayer);
	void onStart(Ref* pSender, TouchEventType type);
	void onBack(Ref* pSender, TouchEventType type);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};
