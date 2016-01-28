#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct EventPageChange
{
	int from_page;
	int to_page;
	int channel;
	int num;
};


class LogEventPageChange {

public:
	static LogEventPageChange* getInstance();
	void init();

	void addEventItems(int from_page, int to_page, int channel);
	void sendDataToServer();
private:
	LogEventPageChange();
	std::string getDataForJson();
	std::vector<EventPageChange> items;
	static LogEventPageChange* _instance;
};


