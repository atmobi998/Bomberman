#pragma once
class SoundGame
{
public:
	static SoundGame* getInstance();
	 void playMusic(const char* file, bool loop = false);
	 void stopMusic();
	 void resumMusic();
	 unsigned int playEffect(const char* file, bool lool = false);
	 void stopAllEffects();
	 void stopEffect(unsigned int id);
};
