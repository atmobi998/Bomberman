#pragma once
#include "PointList.h"
#include "Enemy.h"
class EnemySmart : public Enemy
{
public:
	static EnemySmart* nodeWithTheGame(GameScene* game, Point location);
	bool initWithTheGame(GameScene* game, Point location);
	void findplayer();
	void update(float dt);		
	PointList *pointList;
private:	
	bool checkfindpath;	
};