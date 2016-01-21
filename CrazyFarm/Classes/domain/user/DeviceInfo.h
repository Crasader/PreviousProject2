#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class DeviceInfo{
public:
	static DeviceInfo* getInstance();
	long getImei();
	std::string getChange_id();
	int getHd_type();
	int getHd_factory();
private:
	DeviceInfo();
	void init();
	static DeviceInfo* _instance;

};

