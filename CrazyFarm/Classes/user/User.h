#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

using namespace cocos2d;

class User{
public:
	static User* getInstance();

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

	int getLevel();
	void setLevel(int level);

	void setScore(int score);
	int  getScore();

	int  getReviveNum();//¸´»î´ÎÊý
	void  setReviveNum(int num);

	int  getLoginTimes();
	void setLoginTimes();

	int  getLastClikTime();
	void setLastClikTime(int clickTime);

	long getCurrentTime();

private:
	User();
	void init();
	static User* _instance;
	int score;
	int level;
	int lastClikTime;
};

#endif
