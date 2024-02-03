#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyPoint :public Node
{
public:
	~MyPoint();
	static MyPoint * create();
	int x;
	int y;	
};