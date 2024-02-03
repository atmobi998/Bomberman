#include "SoundGame.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "common.h"

USING_NS_CC;
using namespace CocosDenshion;
static SoundGame *instance = nullptr;
void SoundGame::playMusic(const char* file, bool loop) {
	if(UserDefault::getInstance()->getBoolForKey(KEY_SOUND, true)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(file, loop);
	}
}

void SoundGame::stopMusic() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

unsigned int SoundGame::playEffect(const char* file, bool loop) {
	if(UserDefault::getInstance()->getBoolForKey(KEY_SOUND, true)) {
		return SimpleAudioEngine::getInstance()->playEffect(file, loop);
	} else {
		return -1;
	}
}

void SoundGame::stopAllEffects() {
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundGame::stopEffect(unsigned int id ) {
	SimpleAudioEngine::getInstance()->stopEffect(id);
}

void SoundGame::resumMusic()
{
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

SoundGame* SoundGame::getInstance()
{
	if (!instance)
	{
		instance = new SoundGame();
	}
	return instance;
}
