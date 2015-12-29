#include "/User"
#include "cocos2d.h"
using namespace cocos2d;

User* User::_instance = 0;

User::User(){
	this->init();
}

void User::init(){
	this->level = 0;
	this->score = 0;
	this->lastClikTime = 0;
}

User* User::getInstance(){
	if(_instance == 0){
		_instance = new User();
	}
	return _instance;
}

void User::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool User::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void User::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool User::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}

int User::getScore(){
	return score;
}

void User::setScore(int score){
	this->score = score;
	auto record =UserDefault::getInstance()->getIntegerForKey("record",0);
	if(score>record){
		UserDefault::getInstance()->setIntegerForKey("record",score);
	}
}


int User::getLevel(){
	return level;
}
void User::setLevel(int level){
	this->level = level;
}



int  User::getReviveNum(){
	return UserDefault::getInstance()->getIntegerForKey("reviveNum",0);
}

void  User::setReviveNum(int num){
	UserDefault::getInstance()->setIntegerForKey("reviveNum",num);
}


int User::getLoginTimes(){
	return UserDefault::getInstance()->getIntegerForKey("loginTimes",0);
}


void User::setLoginTimes(){
	auto times = getLoginTimes()+1;
	UserDefault::getInstance()->setIntegerForKey("loginTimes",times);
}

int  User::getLastClikTime(){
	return lastClikTime;
}


void User::setLastClikTime(int clickTime){
	this->lastClikTime = clickTime;
}


long User::getCurrentTime()   
{    
	struct timeval tv;    
	gettimeofday(&tv,NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
}  

