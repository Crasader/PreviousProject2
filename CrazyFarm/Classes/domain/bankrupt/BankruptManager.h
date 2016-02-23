#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#include "config/ConfigBankrupt.h"
using namespace cocos2d;
class BankruptManager {

public:
    static BankruptManager* getInstance();
    
    
    Bankrupt getBankrupt();
	Bankrupt getRobotBankrupt();
    void addTodayRequestTime();
private:
    BankruptManager();
    void init();
    static BankruptManager* _instance;
    
	CC_SYNTHESIZE(Node*, m_getRewardNode, getRewardNode);
    int getTodayRequestTimes(); //已经领过几次
	const char* BankruptData = "BankruptData";
	CC_SYNTHESIZELOCALINT(BankruptData, BankruptData, 0);
	//DAY 
	int getDayCnt(const char* key);
	void addDayCnt(const char* key);
	int  XygGetToday();

};

