#include "EnemySmart.h"
#include "common.h"
EnemySmart* EnemySmart::nodeWithTheGame(GameScene* game, Point location)
{
	EnemySmart *pRet = new EnemySmart();
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

bool EnemySmart::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("enemy4_1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(enemysmart);
		_mySprite->setPosition(location);
		_mySprite->setAnchorPoint(Vec2(0.5, 0.5));
		_theGame = game;
		_theGame->addChild(this,2);
		pointList = PointList::create(_theGame->_tileMap->getMapSize().width,_theGame->_tileMap->getMapSize().height);
		pointList->retain();
		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("enemy4_",1,3,0.9f / 3.0f);
		_mySprite->runAction(RepeatForever::create(actionanimation));
		checkfindpath=true;
		speed=200;
		this->schedule(schedule_selector(EnemySmart::update));
		bRet = true;
	} while (0);

	return bRet;
}
void EnemySmart::update(float dt)
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

		if (x % 60 >= (30 - s) && y % 60 >= (30 - s) && x % 60 <= (30 + s) && y % 60 <= (30 + s))
		{
			if (rand() % 15 == 0)
			{
				creep = abs(temp - rand() % 4);
			}
			if (_theGame->getIsPlayerDieDone())
			{
				findplayer();
			}
		}

		if (creep == 0 && _theGame->CheckCollision(Vec2(location.x, location.y + s + yy)))
		{
			Point location = _mySprite->getPosition();
			_mySprite->setPosition(Vec2(location.x, location.y + s));
		}
		else if (creep == 1 && _theGame->CheckCollision(Vec2(location.x, location.y - s - yy)))
		{
			Point location = _mySprite->getPosition();
			_mySprite->setPosition(Vec2(location.x, location.y - s));
		}
		else if (creep == 2 && _theGame->CheckCollision(Vec2(location.x + s + xx, location.y)))
		{
			Point location = _mySprite->getPosition();
			_mySprite->setPosition(Vec2(location.x + s, location.y));
		}
		else if (creep == 3 && _theGame->CheckCollision(Vec2(location.x - s - xx, location.y)))
		{
			Point location = _mySprite->getPosition();
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
void EnemySmart::findplayer()
{
	Point location = _mySprite->getPosition();
	Point location2 = _theGame->getChildByTag(player)->getPosition();
	Point point1 = _theGame->tileCoordForPosition(location);
	Point point2 = _theGame->tileCoordForPosition(location2);
	if ((point1.x != point2.x) || (point1.y != point2.y))
	{
		pointList->findPath(_theGame->MapMatrix, point1.x, point1.y, point2.x, point2.y);
		int temp2 = pointList->len;
		if (temp2>1)
		{
			Point target;
			target.x = pointList->point[1].x;
			target.y = pointList->point[1].y;
			Point pointdi = _theGame->PositionFortileCoord(target);
			Point diff = ccpSub(Vec2(pointdi.x+30,pointdi.y-30), _mySprite->getPosition());
			int x = location.x;
			int y = location.y;
			if ( abs(diff.x) > abs(diff.y) ) {
				if (diff.x > 0) {
					creep=2;
				} else {
					creep=3;
				}
			} else {
				if (diff.y > 0) {
					creep=0;
				} else {
					creep=1;
				}
			}
		}
	}
}