#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class DeviceInfo{
public:
	static const char* getImei();
	static std::string getChannel_id();
	static int getHd_type();
	static int getHd_factory();
	static int getVesion();

};

