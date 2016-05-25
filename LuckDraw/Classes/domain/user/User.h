#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

using namespace cocos2d;

class User{
public:
	static User* getInstance();
   
private:
	User();
	static User* _instance;
 
};

#endif
