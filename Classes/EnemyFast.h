#pragma once
#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;
class EnemyFast:public Enemy
{
public:
	
	static EnemyFast* nodeWithTheGame(GameScene* game, Point location);
	bool initWithTheGame(GameScene* game, Point location);	
};
