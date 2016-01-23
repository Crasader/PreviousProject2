#include "utill/Audio.h"
#include "SimpleAudioEngine.h"
#include "data/GameData.h"


Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);

}
void Audio::pauseBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Audio::playSound(char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName);
}
void Audio::setBGMValue(float value)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
}
void Audio::setEffectValue(float value)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(value);
}
void Audio::prepare(){

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGORUNDMUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(CATCHBOSS);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICK);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHBIG);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHMID);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHSMALL);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHGOLD);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SHOOT);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}