#include "utill/Audio.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

Audio::Audio()
{

}
Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if (m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(const char* soundName){
	log("play BGM %s", soundName);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName, true);
}


void Audio::pauseBGM()
{
	log("pause BGM ");
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Audio::resumeBGM()
{
	log("resume BGM ");
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void Audio::playSound(const char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName);
}
void Audio::setBGMValue(float value)
{
	log("setBGMValue:%f", value);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
}
void Audio::setEffectValue(float value)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(value);
}
void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BGMDROPMODE);
	for (int i = 0; i < 5; i++)
	{
		auto path = String::createWithFormat("game/raw/Bgm_Level_%d", i);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(path->getCString());
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BLOCKCUTLINE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BLOCKFALLDOWN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BLOCKROTATE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_GAMEFAILED);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PROPFILL);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PROPKNOCK);

}
void Audio::playBGMByLevel(int level)
{
	auto path = String::createWithFormat("game/raw/Bgm_Level_%d.mp3", level);
	playBGM(path->getCString());
}