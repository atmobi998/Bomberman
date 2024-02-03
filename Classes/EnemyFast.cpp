#include "EnemyFast.h"
#include "common.h"

EnemyFast* EnemyFast::nodeWithTheGame(GameScene* game, Point location)
{
	EnemyFast *pRet = new EnemyFast();
	if (pRet && pRet->initWithTheGame(game, location))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool EnemyFast::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("enemy2_1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(enemy);
		_mySprite->setPosition(location);
		_mySprite->setAnchorPoint(Vec2(0.5, 0.5));
		_theGame = game;
		_theGame->addChild(this,2);
		
		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("enemy2_",1,3,0.5f / 3.0f);
		_mySprite->runAction(RepeatForever::create(actionanimation));
		speed=200;
		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}