#pragma once
#include "cocos2d.h"
#include "Joystick.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Boom.h"
USING_NS_CC;
using namespace cocostudio;
using namespace std;
using namespace ui;
class Boom;
class GameScene : public Layer
{
private:
	CC_SYNTHESIZE(Point, _startpoint, StartPoint);
	CC_SYNTHESIZE(Sprite*,_player,Player);
	CC_SYNTHESIZE(int, live, Live);
	CC_SYNTHESIZE(int,range,Range);
	CC_SYNTHESIZE(int,speed,Speed);
	CC_SYNTHESIZE(int,numboom,NumBoom);
	CC_SYNTHESIZE(bool, isplayerdie, IsPlayerDie);
	CC_SYNTHESIZE(bool, isplayerdiedone, IsPlayerDieDone);
	CC_SYNTHESIZE(int,numenemy,NumEnemy);
	Sprite*_door;
	Sprite*_key;
	Sprite*bonus_boom;
	Sprite*bonus_speed;
	Sprite*bonus_range;	
	Sprite* rip;
	
	Button *controls_butt_a;
	Button *controls_butt_b;
	Button *btn_pause;

	Layout *ui_layerpause;
	Layout *ui_layergameover;
	Layout *ui_layerwin;

	LabelTTF *lb_live;
	LabelTTF *lb_numboom;
	LabelTTF *lb_range;
	LabelTTF *lb_speed;
	PointArray *pointbrick;
	bool isMoveUp;
	bool isMoveDown;
	bool isMoveLeft;
	bool isMoveRight;
	bool isKey;
	bool isDoor;
	float sqrt_of_2;
	int levelselect;
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	
	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	static Scene* scene();
	bool CheckCollision(Point position);
	bool CheckCollisionPlayer(Point position);
	bool CheckCollisionThroughwall(Point position);
	void FixpositionOfPlayerX();
	void FixpositionOfPlayerY();
	void PlayerDie();
	void GameOver();
	void LevelComplete();
	void setViewPointCenter(Point position);
	void update(float dt);
	void updatesound(float dt);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	Point tileCoordForPosition(Point position);
	Point PositionFortileCoord(Point position);
	int size;
	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(GameScene);
	Joystick *_joystick;
	void Controls_Butt_A(Ref *obj, TouchEventType type);
	void Controls_Butt_B(Ref *obj,TouchEventType type);
	void pausegame(Ref *obj,TouchEventType type);
	void resume(Ref *obj,TouchEventType type);
	void restart(Ref *obj,TouchEventType type);
	void backmenu(Ref *obj,TouchEventType type);
	void nextlevel(Ref *obj,TouchEventType type);
	void Move_Up(float dt);
	void Move_Down(float dt);
	void Move_Left(float dt);
	void Move_Right(float dt);
	void playercollision();
	vector<vector<int> > MapMatrix;
	void PlayerDieDone(Node *pSender);
	void ThenPlayerDieDone(Node *pSender);
	void additemboom();
	void additemspeed();
	void additemdoor();
	void additemkey();
	void additemrange();
	void showitem();
	void checkfiredoor();
	void createmap(int level);
	Layer *layerui;
	TMXTiledMap *_tileMap;
	TMXLayer *_background;
	TMXObjectGroup *objectGroup;
	TMXLayer *_meta;
	TMXLayer *_foreground;
	TMXLayer *_nondestructive;	
	Vector<Boom*>arr_boom;
	Layout *ui_layer;
};
