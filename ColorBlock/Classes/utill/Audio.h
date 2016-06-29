#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define AUDIO_BGMDROPMODE		"game/raw/Bgm_Dropmode.mp3"
#define AUDIO_BLOCKCUTLINE		"game/raw/Block_CutLine.mp3"
#define AUDIO_BLOCKFALLDOWN     "game/raw/Block_Falldown.mp3"
#define AUDIO_BLOCKROTATE       "game/raw/Block_Rotate.mp3"
#define AUDIO_GAMEFAILED        "game/raw/GameFailed.mp3"
#define AUDIO_PROPFILL          "game/raw/Prop_Fill.mp3"
#define AUDIO_PROPKNOCK			"game/raw/Prop_Knock.mp3"
class Audio{
public:
	static Audio* getInstance();
	void playBGM(const char* soundName);
	void playSound(const char* soundName);
	void pauseBGM();
	void resumeBGM();
	void prepare();
	void setBGMValue(float value);
	void setEffectValue(float value);
	void playBGMByLevel(int level);
private:
	static Audio* m_instance;
	Audio();
};
#endif