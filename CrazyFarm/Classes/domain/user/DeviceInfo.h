#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class DeviceInfo{
public:
	static long getImei();
	static std::string getChange_id();
	static int getHd_type();
	static int getHd_factory();


};

