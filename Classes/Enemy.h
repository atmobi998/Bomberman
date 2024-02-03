#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Enemy : public Node
{
public:	
	static Enemy* nodeWithTheGame(GameScene* game, Point location);
	virtual bool initWithTheGame(GameScene* game, Point location);
	virtual void checkfire();
	virtual void checkcollistionplayer();
	virtual void update(float dt);
	CC_SYNTHESIZE(GameScene*, _theGame, TheGame);
	CC_SYNTHESIZE(Sprite*, _mySprite, MySprite);
protected:
	int speed; 
	int creep;	
};