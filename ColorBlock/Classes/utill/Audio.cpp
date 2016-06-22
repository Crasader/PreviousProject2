#include "utill/Audio.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

Audio::Audio()
{

}
Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(const char* soundName){
	CCLOG("play BGM %s", soundName);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);
}


void Audio::pauseBGM()
{
	CCLOG("pause BGM ");
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Audio::resumeBGM()
{
	CCLOG("resume BGM ");
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void Audio::playSound(const char* soundName){
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

}
