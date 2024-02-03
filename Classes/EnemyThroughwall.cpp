#include "EnemyThroughwall.h"
#include "common.h"

EnemyThroughwall* EnemyThroughwall::nodeWithTheGame(GameScene* game, Point location)
{
	EnemyThroughwall *pRet = new EnemyThroughwall();
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

bool EnemyThroughwall::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("enemy3_1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(enemy);
		_mySprite->setPosition(location);
		_mySprite->setAnchorPoint(Vec2(0.5, 0.5));
		_theGame = game;
		_theGame->addChild(this,2);
		
		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("enemy3_",1,3,0.5f / 3.0f);
		_mySprite->runAction(CCRepeatForever::create(actionanimation));
		speed=100;
		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}
void EnemyThroughwall::update(float dt)
{
	if (!_theGame->getIsPlayerDie())
	{
		_mySprite->resumeSchedulerAndActions();
		
		float s = speed * dt;
		float xx = 30;
		float yy = 30;
		Point location = _mySprite->getPosition();
		int x = location.x;
		int y = location.y;
		int temp = creep;

		
		if (x % 60 >=(30 - s) && y % 60 >= (30 - s) && x % 60 <= (30 + s) && y % 60 <= (30 + s))
		{
			if (rand() % 15 == 0)
			{
				creep = abs(temp - rand() % 4);
			}
		}
		if (creep == 0 && _theGame->CheckCollisionThroughwall(Vec2(location.x, location.y + s + yy)))
		{
			_mySprite->setPosition(Vec2(location.x, location.y + s));
		}
		else if (creep == 1 && _theGame->CheckCollisionThroughwall(Vec2(location.x, location.y - s - yy)))
		{
			_mySprite->setPosition(Vec2(location.x, location.y - s));
		}
		else if (creep == 2 && _theGame->CheckCollisionThroughwall(Vec2(location.x + s + xx, location.y)))
		{
			_mySprite->setPosition(Vec2(location.x + s, location.y));
		}
		else if (creep == 3 && _theGame->CheckCollisionThroughwall(Vec2(location.x - s - xx, location.y)))
		{
			_mySprite->setPosition(Vec2(location.x - s, location.y));
		}
		else
		{
			creep = rand() % 4;
		}
		checkcollistionplayer();
		checkfire();
	}
	else
	{
		_mySprite->pauseSchedulerAndActions();
	}
}