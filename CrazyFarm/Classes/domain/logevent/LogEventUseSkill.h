#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct EventSkillCell
{
	int skillID;
	int type;
	int prices;
	int nums;
};


class LogEventUseSkill {

public:
	static LogEventUseSkill* getInstance();
	void init();

	void addUseSkillData(int skillID, int type, int prices);
	void sendDataToServer();
private:
	LogEventUseSkill();
	std::string getDataForJson();
	std::vector<EventSkillCell> items;
	static LogEventUseSkill* _instance;
};


