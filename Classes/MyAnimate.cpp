#include "MyAnimate.h"
static MyAnimate *instance = nullptr;
MyAnimate* MyAnimate::getInstance()
{
	if (!instance)
	{
		instance = new MyAnimate();
	}

	return instance;
}

Animate* MyAnimate::createAnimationFramCache(const char* nameFile, int beginIndex, int endIndex, float speed)
{
	Animation* animation = Animation::create();
	SpriteFrame* sprite;
	for (int i = beginIndex; i <= endIndex; i++)
	{
		char szName[64] = {};
		sprintf(szName, "%s%d.png", nameFile, i);
		sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
		animation->addSpriteFrame(sprite);
	}
	animation->setDelayPerUnit(speed);
	Animate *animate = Animate::create(animation);
	return animate;
}

Animate* MyAnimate::createAnimation(const char* nameFile, int beginIndex, int endIndex, float speed)
{
	Animation* animation = Animation::create();
	for (int i = beginIndex; i <= endIndex; i++)
	{
		char szName[64] = {};
		sprintf(szName, "%s%d.png", nameFile, i);
		animation->addSpriteFrameWithFileName(szName);
	}
	animation->setDelayPerUnit(speed);
	Animate *animate = Animate::create(animation);
	return animate;
}

MyAnimate::~MyAnimate()
{
	CC_SAFE_DELETE(instance);
}
