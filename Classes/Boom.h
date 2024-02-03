#pragma once
#include "cocos2d.h"
#include "Fire.h"
#include "GameScene.h"
USING_NS_CC;
class GameScene;
class Fire;
class Boom : public Node
{
public:
	static Boom* nodeWithTheGame(GameScene* game,Point location);
	bool initWithTheGame(GameScene* game, Point location);
	void update(float dt);
	void updatetime(float dt);
	void boomfire();
	CC_SYNTHESIZE(int, time, Time);
	CC_SYNTHESIZE(GameScene*, _theGame, TheGame);
	CC_SYNTHESIZE(Sprite*, _mySprite, MySprite);
private:

	LabelTTF *time_lb;
	Fire *_fire;
	int range;	
};
