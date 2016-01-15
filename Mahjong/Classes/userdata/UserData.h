#ifndef __USER_DATA_H__
#define __USER_DATA_H__
#include "cocos2d.h"
USING_NS_CC;

class UserData{
public:
	static UserData* getInstance();
private:
	UserData();
	static UserData* _instance;	
	void init();
};
#endif