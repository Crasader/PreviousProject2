#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct Magnatecell
{
	int itemID;
	int itemNum;
};

class LogEventMagnate {
public:
	static LogEventMagnate* getInstance();
	void init();
	
	void addMagnateNum(int itemid, int num);
	void sendDataToServer();
private:
	LogEventMagnate();
	std::string getDataForJson();
	std::vector<Magnatecell> items;
	static LogEventMagnate* _instance;
};


