#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Joystick : public Layer
{
public:

	virtual bool init();
	Point getVelocity() {return velocity;}
	CREATE_FUNC(Joystick);
	void setVelocity(Point point){ velocity = point;};
private:

	Point kCenter;
	Sprite *thumb;

	Sprite *controldown;
	Sprite *controlup;
	Sprite *controlleft;
	Sprite *controlright;

	bool isPressed;

	Point velocity;
	int idtouch;
	void updateVelocity(Point point);
	void resetJoystick();
	bool handleLastTouch();
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
};
