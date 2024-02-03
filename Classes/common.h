#pragma  once 
#include "MyAnimate.h"
enum
{
	empty,
	brick,
	stone,
	boom,
	boom2,
	player,
	enemy,
	enemysmart,
	fire,
	actionmove,
	bonusboom,
	bonusspeed,
	bonusrange,
	itemkey,
	itemdoor,
};

const static char* KEY_LEVEL_OPEN = "keylevelOpen";
const static char* KEY_SOUND = "keySound";
const static char* KEY_SELECT_LEVEL= "selectlevel";
const static char* KEY_RANGE="range";
const static char* KEY_NUMBER_BOM="numberbom";
const static char* KEY_SPEED="speed";
#define  SPEEDPLAYER 120
 