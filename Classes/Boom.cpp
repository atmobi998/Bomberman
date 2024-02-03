#include "Boom.h"
#include "GameScene.h"
#include "common.h"
#include "SoundGame.h"
#include "MyAnimate.h"
Boom* Boom::nodeWithTheGame(GameScene* game, Point location)
{
	Boom *pRet = new Boom();
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

bool Boom::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("bom1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(2);
		_mySprite->setPosition(location);
		time = 5;
		_theGame = game;
		range=_theGame->getRange();
		Point point = game->tileCoordForPosition(location);
		int x = point.x;
		int y = point.y;
		_theGame-> MapMatrix[x][y] = boom;
		_theGame->addChild(this,2);

		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("bom",1,4,0.5f / 4.0f);
		_mySprite->runAction(RepeatForever::create(actionanimation));

		time_lb = LabelTTF::create("", "arial", 20);
		time_lb->setString(String::createWithFormat("%d", time)->getCString());
		time_lb->setPosition(location);
		time_lb->setAnchorPoint(Vec2(0.5,0.8));

		this->addChild(time_lb,2);
		this->schedule(schedule_selector(Boom::update));
		this->schedule(schedule_selector(Boom::updatetime), 1);

		bRet = true;
	} while (0);

	return bRet;
}
void Boom::updatetime(float dt)
{
	time += -1;
	time_lb->setString(String::createWithFormat("%d", time)->getCString());
}
void Boom::update(float dt)
{
	if (_theGame->getIsPlayerDie())
	{
		this->unschedule(schedule_selector(Boom::updatetime));
	}
	else
	{
		this->schedule(schedule_selector(Boom::updatetime),1);
	}
	Point location = _mySprite->getPosition();
	Point point = _theGame->tileCoordForPosition(location);
	int x = point.x;
	int y = point.y;

	if ( _theGame-> MapMatrix[x][y] == fire)
	{
		time = 0;
	}	
	Rect Rect = CCRectMake(
		_mySprite->getPosition().x - (_mySprite->getContentSize().width *0.4),
		_mySprite->getPosition().y - (_mySprite->getContentSize().height*0.4),
		_mySprite->getContentSize().width*0.8,
		_mySprite->getContentSize().height*0.8);
	if (!(Rect.intersectsRect(_theGame->getChildByTag(player)->boundingBox()))&&_theGame-> MapMatrix[x][y]!=fire)
	{
		_theGame-> MapMatrix[x][y]=boom2;
	}
	if (time == 0)
	{
		boomfire();
	}
}
void Boom::boomfire()
{
	SoundGame::getInstance()->playEffect("explode.wav");
	Point location = _mySprite->getPosition();
	Point point = _theGame->tileCoordForPosition(location);
	int x = point.x;
	int y = point.y;

	/////// trai
	for (int i =0; i >=-range; i--)
	{
		if (_theGame-> MapMatrix[x + i][y] !=stone )
		{
			Point locationfire = _theGame->PositionFortileCoord(Vec2(x+i,y));
			_fire = Fire::nodeWithTheGame(_theGame, locationfire);
			_theGame->_foreground->removeTileAt(Vec2(x + i, y));
			//_theGame->_meta->removeTileAt(Vec2(x + i, y));
		}
		else
		{
			break;
		}
		if (_theGame-> MapMatrix[x + i][y] == brick)
		{
			break;
		}
	}
	////////phai
	for (int i = 1; i <= range ; i++)
	{
		if (_theGame-> MapMatrix[x + i][y] != stone)
		{
			Point locationfire = _theGame->PositionFortileCoord(Vec2(x + i, y));
			_fire = Fire::nodeWithTheGame(_theGame, locationfire);
			_theGame->_foreground->removeTileAt(Vec2(x + i, y));
			//_theGame->_meta->removeTileAt(Vec2(x + i, y));
		}
		else
		{
			break;
		}
		if (_theGame-> MapMatrix[x + i][y] == brick)
		{
			break;
		}
	}
	///////////duoi
	for (int i = -1; i >=- range; i--)
	{
		if (_theGame-> MapMatrix[x][y + i] != stone)
		{
			Point locationfire = _theGame->PositionFortileCoord(Vec2(x, y+i));
			_fire = Fire::nodeWithTheGame(_theGame, locationfire);
			_theGame->_foreground->removeTileAt(Vec2(x, y+i));
			//_theGame->_meta->removeTileAt(Vec2(x, y+i));
		}
		else
		{
			break;
		}
		if (_theGame-> MapMatrix[x][y + i] == brick)
		{
			break;
		}
	}
	//////////////tren
	for (int i = 1; i <= range; i++)
	{
		if (_theGame-> MapMatrix[x][y + i] != stone)
		{
			Point locationfire = _theGame->PositionFortileCoord(Vec2(x, y + i));
			_fire = Fire::nodeWithTheGame(_theGame, locationfire);
			_theGame->_foreground->removeTileAt(Vec2(x, y + i));
			//_theGame->_meta->removeTileAt(Vec2(x, y + i));
		}
		else
		{
			break;
		}
		if (_theGame-> MapMatrix[x][y + i] == brick)
		{
			break;
		}
	}
	_theGame->setNumBoom(_theGame->getNumBoom()+1);
	_theGame->arr_boom.eraseObject(this);
	_theGame->removeChild(this);
}
