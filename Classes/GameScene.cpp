#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "common.h"
#include "Level.h"
#include "SoundGame.h"
#include "MainMenu.h"
#include "MyAnimate.h"

#include "AppDelegate.h"
#include "Enemy.h"
#include "EnemySmart.h"
#include "Boom.h"
#include "EnemyThroughwall.h"
#include "EnemyFast.h"

using namespace std;
CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();
	
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	
	if (!CCLayer::init())
	{
		return false;
	}
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("InGame.plist");
	this->setKeypadEnabled(true);
	layerui=CCLayer::create();
	pointbrick=PointArray::create(300);

	pointbrick->retain();
	isMoveUp = false;
	isMoveRight = false;
	isMoveDown = false;
	isMoveLeft = false;
	isKey=false;
	isDoor=false;
	///////gia tri ban dau cua player
	live = 3;
	range = UserDefault::getInstance()->getIntegerForKey(KEY_RANGE,1);
	speed = UserDefault::getInstance()->getIntegerForKey(KEY_SPEED,SPEEDPLAYER);
	
	numboom = UserDefault::getInstance()->getIntegerForKey(KEY_NUMBER_BOM,1);	
	//numboom = 3;
	isplayerdiedone=true;
	
	_joystick = Joystick::create();
	addChild(_joystick,10);
	_joystick->setPosition(ccp(-(this->getPositionX()),-48));
	levelselect = UserDefault::getInstance()->getIntegerForKey(KEY_SELECT_LEVEL,1);
	//////// tao map
	createmap(levelselect);
	
	/////////////giao dien
	Sprite * bannertop=Sprite::createWithSpriteFrameName("banner.png");
	bannertop->setPosition(ccp(0,660));
	bannertop->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(bannertop);
	Sprite * bannerbottom=Sprite::createWithSpriteFrameName("banner.png");
	bannerbottom->setPosition(ccp(0,-60));
	bannerbottom->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(bannerbottom);
	Sprite* liveicon=Sprite::createWithSpriteFrameName("br_stay.png");
	liveicon->setPosition(ccp(300,660));
	liveicon->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(liveicon);
	lb_live=CCLabelTTF::create("","arial",40);
	lb_live->setPosition(ccp(390,690));
	lb_live->setString(CCString::createWithFormat("%d", live)->getCString());
	layerui->addChild(lb_live);
	Sprite* boomicon=Sprite::createWithSpriteFrameName("icon_bom.png");
	boomicon->setPosition(ccp(420,660));
	boomicon->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(boomicon);
	lb_numboom=CCLabelTTF::create("","arial",40);
	lb_numboom->setPosition(ccp(510,690));
	layerui->addChild(lb_numboom);
	Sprite* rangeicon=Sprite::createWithSpriteFrameName("icon_fire.png");
	rangeicon->setPosition(ccp(540,660));
	rangeicon->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(rangeicon);
	lb_range=CCLabelTTF::create("","arial",40);
	lb_range->setPosition(ccp(630,690));
	layerui->addChild(lb_range);
	layerui->setAnchorPoint(Vec2::ZERO);
	this->addChild(layerui);
	Sprite* speedicon=Sprite::createWithSpriteFrameName("icon_speed.png");
	speedicon->setPosition(ccp(660,660));
	speedicon->setAnchorPoint(Vec2::ZERO);
	layerui->addChild(speedicon);
	lb_speed=CCLabelTTF::create("","arial",40);
	lb_speed->setPosition(ccp(780,690));
	layerui->addChild(lb_speed);
	///////////////
	ui_layer=Layout::create();
	this->addChild(ui_layer,10);
	controls_butt_a = Button::create();
	controls_butt_a->loadTextures("bt_A1.png", "bt_A2.png", "", UI_TEX_TYPE_LOCAL);
	controls_butt_a->setPosition(ccp(1000, 50));
	controls_butt_a->setOpacity(150);
	controls_butt_a->setTouchEnabled(true);
	controls_butt_a->setPressedActionEnabled(true);
	controls_butt_a->addTouchEventListener(this,toucheventselector(GameScene::Controls_Butt_A));
	ui_layer->addChild(controls_butt_a);

	controls_butt_b=Button::create();
	controls_butt_b->loadTextures("bt_B1.png", "bt_B2.png", "",UI_TEX_TYPE_LOCAL);
	controls_butt_b->setPosition(ccp(1190, 210));
	controls_butt_b->setOpacity(150);
	controls_butt_b->setTouchEnabled(true);
	controls_butt_b->setPressedActionEnabled(true);
	controls_butt_b->addTouchEventListener(this,toucheventselector(GameScene::Controls_Butt_B));
	ui_layer->addChild(controls_butt_b);

	btn_pause=Button::create();
	btn_pause->loadTextures("pause.png","pause1.png","",UI_TEX_TYPE_PLIST);
	btn_pause->setPosition(ccp(1150,610));
	btn_pause->setTouchEnabled(true);
	btn_pause->setOpacity(100);
	btn_pause->setPressedActionEnabled(true);
	btn_pause->addTouchEventListener(this,toucheventselector(GameScene::pausegame));
	ui_layer->addChild(btn_pause);

	this->schedule(schedule_selector(GameScene::update));
	this->schedule(schedule_selector(GameScene::updatesound),0.3);
	this->schedule(schedule_selector(GameScene::Move_Up));
	this->schedule(schedule_selector(GameScene::Move_Down));
	this->schedule(schedule_selector(GameScene::Move_Left));
	this->schedule(schedule_selector(GameScene::Move_Right));
	this->setViewPointCenter(_player->getPosition());	
	return true;
}
void GameScene::Controls_Butt_A(Ref *obj,TouchEventType type)
{
	if ( type == TOUCH_EVENT_BEGAN&&isplayerdie==false)
	{
		float xx = _player->getContentSize().width*0.5;
		float yy = _player->getContentSize().height*0.5;
		Point location1 = _player->getPosition();
		int x1 = location1.x / 60;
		int y1 = location1.y / 60;
		Point point = tileCoordForPosition(ccp(x1 * 60 + xx, y1 * 60 + yy));
		if ( MapMatrix[int(point.x)][int(point.y)]!=boom&& MapMatrix[int(point.x)][int(point.y)]!=boom2&&(arr_boom.size()-numboom)<0)
		{
			Boom *_boom = Boom::nodeWithTheGame(this, ccp(x1 * 60 + xx, y1 * 60 + yy));
			arr_boom.pushBack(_boom);			
		}
	}
}
void GameScene::Controls_Butt_B(Ref *obj,TouchEventType type)
{
	if ( type == TOUCH_EVENT_BEGAN&&isplayerdie==false)
	{
		Ref*it;
		int count = arr_boom.size();
		if (count>0)
		{
			arr_boom.at(0)->setTime(0);
		}
	}
}
void GameScene::Move_Up(float dt){
	Point point = _joystick->getVelocity() ;
	float x = point.x;
	float y = point.y;
	if (y>0&&x<0)
	{
		if (isMoveUp == false)
		{
			_player->stopActionByTag(actionmove);
			isMoveUp = true;			
			CCAnimate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("br_up",1,2,0.25f / 2.0f);
			CCAction *action=CCRepeatForever::create(actionanimation);
			_player->runAction(action);
			action->setTag(actionmove);
		}
	}
	else
	{
		isMoveUp = false;
	}
}
void GameScene::Move_Down(float dt){
	Point point = _joystick->getVelocity();
	float x = point.x;
	float y = point.y;
	if (y<0 && x>0)
	{
		if (isMoveDown == false)
		{
			_player->stopActionByTag(actionmove);
			isMoveDown = true;			
			CCAnimate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("br_down",1,2,0.25f / 2.0f);
			CCAction *action=CCRepeatForever::create(actionanimation);
			_player->runAction(action);
			action->setTag(actionmove);
		}
	}
	else
	{
		isMoveDown = false;
	}
}
void GameScene::Move_Left(float dt){
	Point point = _joystick->getVelocity();
	float x = point.x;
	float y = point.y;
	if (x<0 &&y<0)
	{
		if (isMoveLeft==false)
		{
			_player->stopActionByTag(actionmove);
			isMoveLeft = true;					
			CCAnimate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("br_left",1,2,0.25f / 2.0f);
			CCAction *action=CCRepeatForever::create(actionanimation);
			_player->runAction(action);
			action->setTag(actionmove);
		}
	}

	else
	{
		isMoveLeft = false;
	}
}
void GameScene::Move_Right(float dt){
	Point point = _joystick->getVelocity();
	float x = point.x;
	float y = point.y;
	if (x>0 && y>0)
	{
		if (isMoveRight==false)
		{
			_player->stopActionByTag(actionmove);
			isMoveRight = true;			
			CCAnimate* actionanimation = MyAnimate::getInstance()->createAnimationFramCache("br_right",1,2,0.25f / 2.0f);
			CCAction *action=CCRepeatForever::create(actionanimation);
			_player->runAction(action);
			action->setTag(actionmove);
		}
	}

	else
	{
		isMoveRight = false;
	}
}
bool GameScene::CheckCollision(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	if ( MapMatrix[int(tileCoord.x)][int(tileCoord.y)]!=empty) {
		return false;
	}
	else
	{
		return true;
	}
}
bool GameScene::CheckCollisionPlayer(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	if ( MapMatrix[int(tileCoord.x)][int(tileCoord.y)]!=empty&& MapMatrix[int(tileCoord.x)][int(tileCoord.y)]!=boom) {
		return false;
	}
	else
	{
		return true;
	}
}
bool GameScene::CheckCollisionThroughwall(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	if ( MapMatrix[int(tileCoord.x)][int(tileCoord.y)] != empty &&  MapMatrix[int(tileCoord.x)][int(tileCoord.y)] != brick&& MapMatrix[int(tileCoord.x)][int(tileCoord.y)]!=boom&& MapMatrix[int(tileCoord.x)][int(tileCoord.y)]!=boom2) {
		return false;
	}
	else
	{
		return true;
	}
}

Point GameScene::tileCoordForPosition(Point position)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}
Point GameScene::PositionFortileCoord(Point position)
{
	int x = position.x * _tileMap->getTileSize().width;
	int y =- position.y*_tileMap->getTileSize().height + _tileMap->getMapSize().height * _tileMap->getTileSize().height;
	return ccp(x, y);
}

void GameScene::update(float dt)
{
	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("InGame.plist");
	checkfiredoor();	
	lb_speed->setString(CCString::createWithFormat("x %.1f",float(speed)/float(SPEEDPLAYER))->getCString());
	lb_live->setString(CCString::createWithFormat("%d", live)->getCString());
	lb_numboom->setString(CCString::createWithFormat("%d", numboom)->getCString());
	lb_range->setString(CCString::createWithFormat("%d", range)->getCString());
	showitem();
	if (isplayerdie)
	{
		PlayerDie();
	}
	else
	{
		playercollision();
		float s = speed * dt;
		float xx =_player->getContentSize().width*0.5;
		float yy = _player->getContentSize().height*0.5;
		Point location = _player->getPosition();

		if (_joystick->getVelocity().x == 0 || _joystick->getVelocity().y == 0)
		{
			_player->stopActionByTag(actionmove);
		}
		if (isMoveUp&&CheckCollisionPlayer(ccp(location.x, location.y + s + yy)))
		{
			FixpositionOfPlayerX();
			Point location = _player->getPosition();
			_player->setPosition(ccp(location.x, location.y + s));
		}
		if (isMoveDown&&CheckCollisionPlayer(ccp(location.x, location.y - s - yy)))
		{
			FixpositionOfPlayerX();
			Point location = _player->getPosition();
			_player->setPosition(ccp(location.x, location.y - s));
		}
		if (isMoveLeft&&CheckCollisionPlayer(ccp(location.x - s - xx, location.y)))
		{
			FixpositionOfPlayerY();
			Point location = _player->getPosition();
			_player->setPosition(ccp(location.x - s, location.y));
		}
		if (isMoveRight&&CheckCollisionPlayer(ccp(location.x + s + xx, location.y)))
		{
			FixpositionOfPlayerY();
			Point location = _player->getPosition();
			_player->setPosition(ccp(location.x + s, location.y));
		}
	}
	this->setViewPointCenter(_player->getPosition());
	_joystick->setPosition(ccp(-(this->getPositionX()),-48));
	ui_layer->setPositionX(-this->getPositionX());
	layerui->setPositionX(-this->getPositionX());
	if (live<1)
	{
		GameOver();
	}
	/*if (isKey&&isDoor&&numenemy<1)
	{
	}*/
}
void GameScene::FixpositionOfPlayerY()
{
	float xx = _player->getContentSize().width*0.5;
	float yy = _player->getContentSize().height*0.5;
	float h = _tileMap->getTileSize().height;
	Point location1 = _player->getPosition();
	float x1 = location1.x;
	int y1 = location1.y /h;
	_player->setPosition(ccp(x1, y1 * h + yy));
}
void GameScene::FixpositionOfPlayerX()
{
	float xx = _player->getContentSize().width*0.5;
	float yy = _player->getContentSize().height*0.5;
	float w = _tileMap->getTileSize().width;
	Point location1 = _player->getPosition();
	int x1 = location1.x / w;
	float y1 = location1.y;
	_player->setPosition(ccp(x1 * w + xx, y1));
}
void GameScene::PlayerDie()
{
	Point point = _player->getPosition();
	if (getIsPlayerDieDone())
	{
		rip = Sprite::createWithSpriteFrameName("rip_icon.png");
		rip->setPosition(point);
		this->addChild(rip,4);
		setIsPlayerDieDone(false);
		CCAction*action = CCSequence::create(CCDelayTime::create(1.0f), CCCallFuncN::create(this, callfuncN_selector(GameScene::PlayerDieDone)),CCDelayTime::create(5.0f), CCCallFuncN::create(this, callfuncN_selector(GameScene::ThenPlayerDieDone)), NULL);
		this->runAction(action);
	}
}

void GameScene::PlayerDieDone(Node *pSender)
{
	this->removeChild(rip);
	_player->setPosition(_startpoint);
	if (levelselect<=10)
	{
		range=1;
	}
	else if (levelselect>10&&levelselect<=20)
	{
		range=2;
	}
	else if (levelselect>20&&levelselect<=30)
	{
		range=3;
	}
	else
	{
		range=4;
	}
	live -= 1;
	numboom = 1;
	speed = SPEEDPLAYER;
	isplayerdie = false;
	CCActionInterval *blink=CCBlink::create(5,15);
	_player->runAction(blink);
	_player->setOpacity(150);
}
void GameScene::playercollision()
{
	Point location1 = _player->getPosition();
	Point point1 = tileCoordForPosition(location1);
	int x1 = point1.x;
	int y1 = point1.y;
	if ( MapMatrix[x1][y1] == fire&&isplayerdiedone)
	{
		isplayerdie=true;
	}
	if (this->getChildByTag(bonusboom))
	{
		if (bonus_boom->boundingBox().containsPoint(location1))
		{
			numboom+=1;
			this->removeChild(bonus_boom);
		}
	}
	if (this->getChildByTag(bonusrange))
	{
		if (bonus_range->boundingBox().containsPoint(location1))
		{
			range+=1;
			this->removeChild(bonus_range);
		}
	}
	if (this->getChildByTag(bonusspeed))
	{
		if (bonus_speed->boundingBox().containsPoint(location1))
		{
			speed+=50;
			this->removeChild(bonus_speed);
		}
	}
	if (this->getChildByTag(itemkey))
	{
		if (_key->boundingBox().containsPoint(location1))
		{
			isKey=true;
			this->removeChild(_key);
		}
	}
	if (this->getChildByTag(itemdoor))
	{
		if (_door->boundingBox().containsPoint(location1)&&isKey&&numenemy<1)
		{
			LevelComplete();
		}
	}
}
void GameScene::ThenPlayerDieDone(Node *pSender)
{
	setIsPlayerDieDone(true);
	_player->setOpacity(255);
}

void GameScene::additemboom()
{
	int numpoint=pointbrick->count();
	int diem;
	srand(time(0));
	diem = rand() % numpoint;
	// CCLog("aaaaaaaaaa=%d",diem);
	Point point=pointbrick->getControlPointAtIndex(diem);
	pointbrick->removeControlPointAtIndex(diem);
	bonus_boom = Sprite::createWithSpriteFrameName("icon_bom.png");
	bonus_boom->setPosition(point);
	bonus_boom->setAnchorPoint(ccp(0,1));
	this->addChild(bonus_boom,1,bonusboom);
	bonus_boom->setVisible(false);
}

void GameScene::additemspeed()
{
	int numpoint=pointbrick->count();
	int diem;
	srand(time(0));
	diem = rand() % numpoint;
	Point point=pointbrick->getControlPointAtIndex(diem);
	pointbrick->removeControlPointAtIndex(diem);
	bonus_speed = Sprite::createWithSpriteFrameName("icon_speed.png");
	bonus_speed->setPosition(point);
	bonus_speed->setAnchorPoint(ccp(0,1));
	this->addChild(bonus_speed,1,bonusspeed);
	bonus_speed->setVisible(false);
}

void GameScene::additemdoor()
{
	int numpoint=pointbrick->count();
	int diem;
	srand(time(0));
	diem = rand() % numpoint;
	Point point=pointbrick->getControlPointAtIndex(diem);
	pointbrick->removeControlPointAtIndex(diem);
	_door = Sprite::createWithSpriteFrameName("door.png");
	_door->setPosition(point);
	_door->setAnchorPoint(ccp(0,1));
	this->addChild(_door,1,itemdoor);
	_door->setVisible(false);
}

void GameScene::additemkey()
{
	int numpoint=pointbrick->count();
	int diem;
	srand(time(0));
	diem = rand() % numpoint;
	Point point=pointbrick->getControlPointAtIndex(diem);
	pointbrick->removeControlPointAtIndex(diem);
	_key = Sprite::createWithSpriteFrameName("key.png");
	_key->setPosition(point);
	_key->setAnchorPoint(ccp(0,1));
	this->addChild(_key,1,itemkey);
	_key->setVisible(false);
}

void GameScene::additemrange()
{
	int numpoint=pointbrick->count();
	int diem;
	srand(time(0));
	diem = rand() % numpoint;
	Point point=pointbrick->getControlPointAtIndex(diem);
	pointbrick->removeControlPointAtIndex(diem);
	bonus_range = Sprite::createWithSpriteFrameName("icon_fire.png");
	bonus_range->setPosition(point);
	bonus_range->setAnchorPoint(ccp(0,1));
	this->addChild(bonus_range,1,bonusrange);
	bonus_range->setVisible(false);
}

void GameScene::showitem()
{
	if (this->getChildByTag(itemdoor))
	{
		Point point1=tileCoordForPosition(_door->getPosition());
		if ( MapMatrix[int(point1.x)][int(point1.y)]==empty)
		{
			_door->setVisible(true);
		}
	}

	if (this->getChildByTag(itemkey))
	{
		Point point2=tileCoordForPosition(_key->getPosition());
		if ( MapMatrix[int(point2.x)][int(point2.y)]==empty)
		{
			_key->setVisible(true);
		}
	}

	if (this->getChildByTag(bonusboom))
	{
		Point point3=tileCoordForPosition(bonus_boom->getPosition());
		if ( MapMatrix[int(point3.x)][int(point3.y)]==empty)
		{
			bonus_boom->setVisible(true);
		}
	}
	if (this->getChildByTag(bonusrange))
	{
		Point point4=tileCoordForPosition(bonus_range->getPosition());
		if ( MapMatrix[int(point4.x)][int(point4.y)]==empty)
		{
			bonus_range->setVisible(true);
		}
	}
	if (this->getChildByTag(bonusspeed))
	{
		Point point5=tileCoordForPosition(bonus_speed->getPosition());
		if ( MapMatrix[int(point5.x)][int(point5.y)]==empty)
		{
			bonus_speed->setVisible(true);
		}
	}
}

void GameScene::createmap(int level)
{
	///////////tao map
	char map[20];
	sprintf(map, "mymap%d.tmx", level);
	_tileMap = TMXTiledMap::create(map);
	_foreground = _tileMap->layerNamed("Foreground");
	_nondestructive = _tileMap->layerNamed("NonDestructive");
	_meta = _tileMap->layerNamed("Meta");
	_meta->setVisible(false);
	this->addChild(_tileMap);
	objectGroup = _tileMap->objectGroupNamed("Objects");
	int mapsize_w = _tileMap->getMapSize().width;
	int mapsize_h = _tileMap->getMapSize().height;


	MapMatrix.resize(mapsize_w);
	for (int i = 0; i < mapsize_w; ++i)
		MapMatrix[i].resize(mapsize_h);

	for (int i = 0; i < mapsize_w; i++)
	{
		for (int j = 0; j < mapsize_h; j++)
		{
			 MapMatrix[i][j]=empty;
		}
	}
	for (int i = 0; i < mapsize_w; i++)
	{
		for (int j = 0; j < mapsize_h; j++)
		{
			int tileGid = _meta->tileGIDAt(ccp(i, j));
			if (tileGid) {
				auto properties = _tileMap->propertiesForGID(tileGid).asValueMap();
				if (!properties.empty()) {
					
					auto blast = properties["Blastable"].asString();
					auto collision = properties["Collidable"].asString();
					if (((collision=="True")) && ((blast=="True")))
					{
						 MapMatrix[i][j]= brick;
						pointbrick->addControlPoint(PositionFortileCoord(ccp(i,j)));
					}
					if (((collision=="True")) && ((blast!="True")))
					{
						 MapMatrix[i][j]= stone;
					}
				}
			}
		}
	}
	//////vi tri player
	auto startpoint = objectGroup->objectNamed("StartPoint");
	_startpoint.x = startpoint["x"].asInt();
	_startpoint.y = startpoint["y"].asInt();
	_player = Sprite::createWithSpriteFrameName("br_stay.png");
	_player->setPosition(_startpoint);
	this->addChild(_player,3);
	_player->setTag(player);

	/////////////////////////////////////
	isplayerdie = false;	
	auto arr_enemy = objectGroup->getObjects();
	numenemy=arr_enemy.size()-1;
	
	for (auto&pObj:arr_enemy)
	{
		auto dict = pObj.asValueMap();
		if(dict.empty())
			break;
		const char* key = "x";
		int x = dict[key].asInt();
		key = "y";
		int y = dict[key].asInt();
		key = "name";
		auto typeenemy = dict[key].asString();
		if (typeenemy=="enemy")
		{
			Enemy *_enemy = Enemy::nodeWithTheGame(this, ccp(x, y));
		}
		if (typeenemy=="smart")
		{
			EnemySmart *_enemysmart = EnemySmart::nodeWithTheGame(this, ccp(x, y));
		}
		if (typeenemy=="fast")
		{
			EnemyFast *_enemyfast = EnemyFast::nodeWithTheGame(this, ccp(x, y));
		}
		if (typeenemy=="wall")
		{
			EnemyThroughwall *_enemythroughwall = EnemyThroughwall::nodeWithTheGame(this, ccp(x, y));
		}
	}

	size = _tileMap->getTileSize().width;
	sqrt_of_2 = 1 / sqrt(2);
	///////////////////add item
	additemrange();
	additemspeed();
	additemboom();
	additemdoor();
	additemkey();
}
void GameScene::setViewPointCenter(Point position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int x = MAX(position.x, winSize.width/2);
	int y = MAX(position.y, winSize.height/2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
	Point actualPosition = ccp(x, y);
	Point centerOfView = ccp(winSize.width/2, winSize.height/2);
	Point viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(ccp(viewPoint.x,48));
}

void GameScene::checkfiredoor()
{
	if (_door->isVisible())
	{
		Point location =_door->getPosition();
		Point point = tileCoordForPosition(location);
		if ( MapMatrix[int(point.x)][int(point.y)]==fire)
		{
			 MapMatrix[int(point.x)][int(point.y)]=empty;
			for (int i = 0; i < 10; i++)
			{
				EnemyFast *_enemyfast=EnemyFast::nodeWithTheGame(this,ccp(location.x+30,location.y-30));
			}
			numenemy=numenemy+10;
		}
	}
}

void GameScene::pausegame(Ref *obj,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		CCDirector::sharedDirector()->pause();

		ui_layerpause=Layout::create();
		ui_layerpause->setPositionX(-this->getPositionX());
		ui_layerpause=(Layout*)(GUIReader::getInstance()->widgetFromJsonFile("PauseGame_Canvas.json"));
		this->addChild(ui_layerpause,10);
		Button *btnreplay=(Button*)(Helper::seekWidgetByName(ui_layerpause,"Button_Replay"));
		btnreplay->setPressedActionEnabled(true);
		btnreplay->addTouchEventListener((Ref*)this,toucheventselector(GameScene::restart));
		Button *btnmenu=(Button*)(Helper::seekWidgetByName(ui_layerpause,"Button_Menu"));
		btnmenu->setPressedActionEnabled(true);
		btnmenu->addTouchEventListener((Ref*)this,toucheventselector(GameScene::backmenu));
		Button *btnresume=(Button*)(Helper::seekWidgetByName(ui_layerpause,"Button_Resume"));
		btnresume->setPressedActionEnabled(true);
		btnresume->addTouchEventListener((Ref*)this,toucheventselector(GameScene::resume));
	}
}

void GameScene::resume(Ref *obj,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		CCDirector::sharedDirector()->resume();
		this->removeChild(ui_layerpause);
	}
}

void GameScene::restart(Ref *obj,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		if (levelselect<=10)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,1);
		}
		else if (levelselect>10&&levelselect<=20)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,2);
		}
		else if (levelselect>20&&levelselect<=30)
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,3);
		}
		else
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,4);
		}
		UserDefault::getInstance()->setIntegerForKey(KEY_NUMBER_BOM,1);
		UserDefault::getInstance()->setIntegerForKey(KEY_SELECT_LEVEL,levelselect);
		UserDefault::getInstance()->setIntegerForKey(KEY_SPEED,SPEEDPLAYER);
		UserDefault::getInstance()->flush();
		//CCScene *pscene =CCTransitionProgressRadialCW::create(1, GameScene::scene());
		CCScene *pscene =GameScene::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
		CCDirector::sharedDirector()->resume();
	}
}

void GameScene::backmenu(Ref *obj,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		//CCScene *pscene =CCTransitionSlideInL::create(0.5, Level::scene());
		CCScene *pscene =Level::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
		CCDirector::sharedDirector()->resume();		
	}
}

void GameScene::nextlevel(Ref *obj,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		SoundGame::getInstance()->playEffect("click.wav");
	}
	else if ( type == TOUCH_EVENT_ENDED)
	{
		UserDefault::getInstance()->setIntegerForKey(KEY_NUMBER_BOM,numboom);
		UserDefault::getInstance()->setIntegerForKey(KEY_RANGE,range);
		UserDefault::getInstance()->setIntegerForKey(KEY_SELECT_LEVEL,levelselect+1);
		UserDefault::getInstance()->setIntegerForKey(KEY_SPEED,speed);
		UserDefault::getInstance()->flush();
		//CCScene *pscene =CCTransitionSlideInR::create(0.5, GameScene::scene());
		CCScene *pscene =GameScene::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
		CCDirector::sharedDirector()->resume();		
	}
}

void GameScene::GameOver()
{
	CCDirector::sharedDirector()->pause();
	this->unscheduleAllSelectors();
	SoundGame::getInstance()->playEffect("gameover_bgm.wav");
	ui_layergameover = Layout::create();
	ui_layergameover->setPositionX(-this->getPositionX());
	ui_layergameover=(Layout*)(GUIReader::getInstance()->widgetFromJsonFile("GameOver_Canvas.json"));
	this->addChild(ui_layergameover,10);
	Button *btnreplay=(Button*)(Helper::seekWidgetByName(ui_layergameover,"Button_Replay"));
	btnreplay->setPressedActionEnabled(true);
	btnreplay->addTouchEventListener(this,toucheventselector(GameScene::restart));
	Button *btnmenu=(Button*)(Helper::seekWidgetByName(ui_layergameover,"Button_Menu"));
	btnmenu->setPressedActionEnabled(true);
	btnmenu->addTouchEventListener(this,toucheventselector(GameScene::backmenu));	
}

void GameScene::LevelComplete()
{
	CCDirector::sharedDirector()->pause();
	this->unscheduleAllSelectors();
	SoundGame::getInstance()->playEffect("level_up.wav");
	int levelopen=UserDefault::getInstance()->getIntegerForKey(KEY_LEVEL_OPEN,1);
	if (levelselect==levelopen)
	{
		UserDefault::getInstance()->setIntegerForKey(KEY_LEVEL_OPEN,levelselect+1);
		UserDefault::getInstance()->flush();
	}
	char strStar[20];
	sprintf(strStar, "star4Level%d", levelselect);
	UserDefault::getInstance()->setIntegerForKey(strStar,live);
	UserDefault::getInstance()->flush();
	ui_layerwin = Layout::create();
	ui_layerwin->setPositionX(-this->getPositionX());
	ui_layerwin=(Layout*)(GUIReader::getInstance()->widgetFromJsonFile("PlayerWin_CanVas.json"));
	this->addChild(ui_layerwin,10);
	Button *btnnextlevel=(Button*)(Helper::seekWidgetByName(ui_layerwin,"Button_NextLevel"));
	btnnextlevel->setPressedActionEnabled(true);
	btnnextlevel->addTouchEventListener((Ref*)this,toucheventselector(GameScene::nextlevel));
	Button *btnmenu=(Button*)(Helper::seekWidgetByName(ui_layerwin,"Button_Menu"));
	btnmenu->setPressedActionEnabled(true);
	btnmenu->addTouchEventListener((Ref*)this,toucheventselector(GameScene::backmenu));
	ImageView *ui_image=(ImageView*)(Helper::seekWidgetByName(ui_layerwin,"Star"));
	switch (live)
	{
	case  1:
		ui_image->loadTexture("win1.png",UI_TEX_TYPE_LOCAL);
		break;
	case 2:
		ui_image->loadTexture("win2.png",UI_TEX_TYPE_LOCAL);
		break;
	case 3:
		ui_image->loadTexture("win3.png",UI_TEX_TYPE_LOCAL);
		break;
	default:
		break;
	}	
}

void GameScene::updatesound(float dt)
{
	if (_player->getActionByTag(actionmove))
	{
		SoundGame::getInstance()->playEffect("move.wav");
	}
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode ==EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//CCScene *pscene =CCTransitionSlideInL::create(0.5, Level::scene());
		CCScene *pscene = Level::scene();
		CCDirector::sharedDirector()->replaceScene(pscene);
		CCDirector::sharedDirector()->resume();
	}
}
