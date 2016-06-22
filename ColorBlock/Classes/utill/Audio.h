#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
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
private:
	static Audio* m_instance;
	Audio();
};
#endif