#pragma once
#include "Enemy.h"
class EnemyThroughwall : public Enemy
{
public:	

	static EnemyThroughwall* nodeWithTheGame(GameScene* game, Point location);
	bool initWithTheGame(GameScene* game, Point location);
	void update(float dt);
};