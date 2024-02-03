#pragma once
#include "cocos2d.h"
#include "GameScene.h"
class GameScene;
USING_NS_CC;
class Fire : public Node
{
public:
	static Fire* nodeWithTheGame(GameScene* game, Point location);
	bool initWithTheGame(GameScene* game, Point location);	
	void removefire(Node *pSender);
	CC_SYNTHESIZE(GameScene*, _theGame, TheGame);
	CC_SYNTHESIZE(Sprite*, _mySprite, MySprite);
};