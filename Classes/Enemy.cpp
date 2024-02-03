#include "Enemy.h"
#include "common.h"
#include"MyAnimate.h"

Enemy* Enemy::nodeWithTheGame(GameScene* game, Point location)
{
	Enemy *pRet = new Enemy();
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

bool Enemy::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("enemy1_1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(enemy);
		_mySprite->setPosition(location);
		_mySprite->setAnchorPoint(Vec2(0.5, 0.5));
		_theGame = game;
		_theGame->addChild(this,2);		

		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("enemy1_",1,2,0.5f / 2.0f);
		_mySprite->runAction(RepeatForever::create(actionanimation));

		speed=100;
		creep=rand()%4;

		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}
void Enemy::update(float dt)
{
	if (!_theGame->getIsPlayerDie())
	{
		_mySprite->resumeSchedulerAndActions();		
		float s = speed * dt;
		float xx = 30;
		float yy = 30;
		Point location = _mySprite->getPosition();
		int x = location.x;
		int y= location.y;
		int temp = creep;		
		if (x%60>=(30-s)&&y%60>=(30-s)&&x%60<=(30+s)&&y%60<=(30+s))
		{
			if (rand()%15==0)
			{
				creep = abs(temp - rand() % 4);
			}
		}
		if (creep== 0 && _theGame->CheckCollision(Vec2(location.x, location.y + s+yy)))
		{
			_mySprite->setPosition(Vec2(location.x, location.y + s));
		}
		else if (creep == 1 && _theGame->CheckCollision(Vec2(location.x, location.y - s-yy)))
		{
			_mySprite->setPosition(Vec2(location.x, location.y - s));
		}
		else if (creep == 2 && _theGame->CheckCollision(Vec2(location.x+s+xx, location.y)))
		{
			_mySprite->setPosition(Vec2(location.x + s, location.y));
		}
		else if (creep == 3 && _theGame->CheckCollision(Vec2(location.x - s - xx, location.y)))
		{
			_mySprite->setPosition(Vec2(location.x - s, location.y));
		}
		else
		{
			creep=rand() % 4;
		}
		checkcollistionplayer();
		checkfire();
	}
	else
	{
		_mySprite->pauseSchedulerAndActions();
	}
}
void Enemy::checkfire()
{
	Point location = _mySprite->getPosition();
	Point point = _theGame->tileCoordForPosition(location);
	int x = point.x;
	int y = point.y;
	if (_theGame-> MapMatrix[x][y]==fire)
	{
		int temp= _theGame->getNumEnemy();
		_theGame->setNumEnemy(temp-1);
		_theGame->removeChild(this);
	}
}
void Enemy::checkcollistionplayer()
{
	if (_theGame->getIsPlayerDieDone())
	{
		CCRect Rect = CCRectMake(
			_mySprite->getPosition().x - (_mySprite->getContentSize().width / 8),
			_mySprite->getPosition().y - (_mySprite->getContentSize().height / 8),
			_mySprite->getContentSize().width / 4,
			_mySprite->getContentSize().height / 4);

		CCRect Rect1 = CCRectMake(
			_theGame->getChildByTag(player)->getPosition().x - (_theGame->getChildByTag(player)->getContentSize().width / 2),
			_theGame->getChildByTag(player)->getPosition().y - (_theGame->getChildByTag(player)->getContentSize().height / 2),
			_theGame->getChildByTag(player)->getContentSize().width,
			_theGame->getChildByTag(player)->getContentSize().height);
		if (Rect.intersectsRect(Rect1)&&!_theGame->getIsPlayerDie())
		{
			_theGame->setIsPlayerDie(true);
		}
	}
}