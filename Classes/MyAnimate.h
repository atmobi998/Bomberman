#pragma  once
#include "cocos2d.h"
USING_NS_CC;

class MyAnimate
{
public:
	~MyAnimate();
	Animate* createAnimationFramCache(const char* nameFile, int beginIndex, int endIndex, float speed);
	Animate* createAnimation(const char* nameFile, int beginIndex, int endIndex, float speed);
	static MyAnimate* getInstance();
};