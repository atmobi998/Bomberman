#include "Fire.h"
#include "common.h"

Fire* Fire::nodeWithTheGame(GameScene* game, Point location)
{
	Fire *pRet = new Fire();
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

bool Fire::initWithTheGame(GameScene* game, Point location)
{
	bool bRet = false;
	do
	{
		_mySprite = Sprite::createWithSpriteFrameName("1.png");
		this->addChild(_mySprite);
		_mySprite->setTag(enemysmart);
		_mySprite->setPosition(location);
		_mySprite->setAnchorPoint(ccp(0, 0.8));
		_theGame = game;
		_theGame->addChild(this,2);
		Point point = _theGame->tileCoordForPosition(location);
		int x = point.x;
		int y = point.y;
		//_theGame-> MapMatrix[x][y] = fire;
		if (_theGame-> MapMatrix[x][y] != stone&&_theGame-> MapMatrix[x][y] != brick)
		{
			_theGame-> MapMatrix[x][y] = fire;
		}
		//this->setTag(fire);
		
		Animate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("",1,6,0.5f / 6.0f);
		Action*action = Sequence::create(actionanimation, CallFuncN::create(this, callfuncN_selector(Fire::removefire)),NULL);
		_mySprite->runAction(action);
		
		bRet = true;
	} while (0);

	return bRet;
}
void Fire::removefire(Node *pSender)
{
	Point location = pSender->getPosition();
	Point point = _theGame->tileCoordForPosition(location);
	int x = point.x;
	int y = point.y;
	_theGame-> MapMatrix[x][y] = empty;
	_theGame->removeChild(this);
}