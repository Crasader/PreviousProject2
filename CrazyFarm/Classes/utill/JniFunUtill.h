#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class JniFunUtill{
public:
	static JniFunUtill* getInstance();
	const char * getSDcardpath();
private:
	JniFunUtill();
	static JniFunUtill* _instance;
};

