#include "Joystick.h"

#define JOYSTICK_OFFSET_X 10.0f
#define JOYSTICK_OFFSET_Y 10.0f

#define JOYSTICK_RADIUS 150.0f

#define THUMB_RADIUS 70.0f

static Point convertCoordinate(Point point){
	return CCDirector::sharedDirector()->convertToGL(point);
}

static bool isPointInCircle(Point point, Point center, float radius){
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);
	return (radius >= sqrt((dx*dx)+(dy*dy)));
}

bool Joystick::init()
{
	bool bRet = false;
	do
	{
		kCenter=Point(JOYSTICK_RADIUS + JOYSTICK_OFFSET_X,
			JOYSTICK_RADIUS + JOYSTICK_OFFSET_Y);
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(!CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
		listener->onTouchesCancelled = CC_CALLBACK_2(Joystick::onTouchesCancelled, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		velocity = Vec2::ZERO;

		Sprite *bg = Sprite::create("control2.png");
		bg->setPosition(kCenter);
		bg->setOpacity(150);
		this->addChild(bg,0);
		thumb = Sprite::create("control1.png");
		thumb->setPosition(kCenter);
		thumb->setOpacity(150);
		this->addChild(thumb,1);

		controlup = Sprite::create("control-up.png");
		controlup->setPosition(Vec2(150,250));
		bg->addChild(controlup);
		controlup->setVisible(false);

		controldown = Sprite::create("control-down.png");
		controldown->setPosition(Vec2(150,50));
		bg->addChild(controldown);
		controldown->setVisible(false);

		controlleft = Sprite::create("control-left.png");
		controlleft->setPosition(Vec2(50, 150));
		bg->addChild(controlleft);
		controlleft->setVisible(false);

		controlright = Sprite::create("control-right.png");
		controlright->setPosition(Vec2(250, 150));
		bg->addChild(controlright);
		controlright->setVisible(false);

		idtouch=0;
		bRet=true;
	} while(0);

	return bRet;
}

void Joystick::updateVelocity(Point point)
{
	// calculate Angle and length
	float dx = point.x - kCenter.x;
	float dy = point.y - kCenter.y;

	float distance = sqrt(dx*dx + dy*dy);
	float angle = atan2(dy,dx); // in radians

	if (distance > JOYSTICK_RADIUS)
	{
		dx = cos(angle) * JOYSTICK_RADIUS;
		dy = sin(angle) * JOYSTICK_RADIUS;
	}

	velocity = CCPointMake(dx/JOYSTICK_RADIUS, dy/JOYSTICK_RADIUS);
	Point vlc = this->getVelocity();
	float sqrt_of_2 = 1 / sqrt(2);
	float x = vlc.x*sqrt_of_2 - vlc.y*sqrt_of_2;
	float y = vlc.y*sqrt_of_2 + vlc.x*sqrt_of_2;
	velocity = CCPointMake(x, y);
	if (y>0 && x<0)
	{
		///move up
		controlup->setVisible(true);
	}
	else
	{
		controlup->setVisible(false);
	}

	if (y < 0 && x>0)
	{

		///move down
		controldown->setVisible(true);
	}
	else
	{
		controldown->setVisible(false);
	}

	if (x < 0 && y < 0)
	{
		//move left
		controlleft->setVisible(true);
	}
	else
	{
		controlleft->setVisible(false);
	}
	if (x>0 && y > 0)
	{
		//move right
		controlright->setVisible(true);
	}
	else
	{
		controlright->setVisible(false);
	}
	if(distance>THUMB_RADIUS)
	{
		point.x = kCenter.x + cos(angle) * THUMB_RADIUS;
		point.y = kCenter.y + sin(angle) * THUMB_RADIUS;
	}

	thumb->setPosition(point);
}

void Joystick::resetJoystick()
{
	this->updateVelocity(kCenter);
}

bool Joystick::handleLastTouch()
{
	bool wasPressed = isPressed;
	if (wasPressed)
	{
		this->resetJoystick();
		isPressed = false;
	}
	return (wasPressed ? true : false);
}

void Joystick::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto &touch:touches)
	{	
	Point point = touch->getLocationInView();
	point = convertCoordinate(point);

	if (isPointInCircle(point,kCenter,JOYSTICK_RADIUS))
	{
		isPressed = true;
		this->updateVelocity(point);
	}
	}
}

void Joystick::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	if (isPressed)
	{
		for (auto&touch:touches)
		{
		
		if (touch->getID()==idtouch)
		{
			Point point = touch->getLocationInView();
			point = convertCoordinate(point);
			this->updateVelocity(point);
		}
	}
	}
}

void Joystick::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
	this->handleLastTouch();
}

void Joystick::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	this->handleLastTouch();	
}