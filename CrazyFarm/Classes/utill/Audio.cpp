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

void Audio::playBGM(const char* soundName){
	CCLOG("play BGM %s", soundName);
	/*CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);*/

}
void Audio::pauseBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Audio::playSound(const char* soundName){
	/*CCLOG("play sound %s", soundName);*/
	/*CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName);*/
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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(GAMEBGM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(LOBBYBGM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FISHFLOCKBGM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BOSSBGM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SKILLBOOM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SKILLFREEZE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SKILLLASER);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SKILLSUMMON);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BOSSWARN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHGIRLFISH);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CATCHGOLD);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLEARFISH);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKCANCER);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKSURE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GAINBOX);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GAINCOIN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GAINDIAMOND);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GIRLAPPEAR);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GIRLMISSIONSUCCESS);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PROPINBOX);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SIGN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UPDATALEVEL);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(UPDATATURRET);


	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}

void Audio::playZhenrenVoice()
{
	//auto str = String::createWithFormat("game/audio/zhenren/voice_%d.ogg", rand() % 6 + 1);
	//playSound(str->getCString());
}

void Audio::playShootVoic()
{
	/*auto str = String::createWithFormat("game/audio/shoot_%d.ogg", 2);
	playSound(str->getCString());*/
}