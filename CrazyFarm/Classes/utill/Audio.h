#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "game/audio/bgm_opening.mp3"
#define CLICK "game/audio/clickBtn.mp3"
#define CATCHBOSS "game/audio/catchBOSS.mp3"
#define CATCHBIG "game/audio/catchBig.mp3"
#define CATCHMID "game/audio/catchMid.mp3"
#define CATCHSMALL "game/audio/catchSmall.mp3"
#define CATCHGOLD "game/audio/catchGold.mp3"
#define SHOOT "game/audio/shoot.mp3"
class Audio{
public:
	static Audio* getInstance();
	void playBGM(char* soundName);
	void playSound(char* soundName);
	void pauseBGM();
	void prepare();
	void setBGMValue(float value);
	void setEffectValue(float value);
private:
	static Audio* m_instance;
};
#endif