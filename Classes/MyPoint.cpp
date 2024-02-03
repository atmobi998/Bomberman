#include "MyPoint.h"
MyPoint * MyPoint::create()
{
	MyPoint * point= new MyPoint();
	if (point)
	{
		point->autorelease();
		return point;
	}
	CC_SAFE_DELETE(point);
	return NULL;
}

MyPoint::~MyPoint()
{
	
}
