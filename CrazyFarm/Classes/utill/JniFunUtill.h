#pragma once
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"
#endif

using namespace cocos2d;

class JniFunUtill{
public:
	static JniFunUtill* getInstance();
	const char * getSDcardpath();

	const char* getImei();
	const char* getHdFactory();
	const char* getHdType();


	void pay(int price, const char* orderid);
private:
	JniFunUtill();
	static JniFunUtill* _instance;
};

