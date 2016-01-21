#pragma once
#include "cocos2d.h"

#include "config/ConfigBankrupt.h"

using namespace cocos2d;

class BankruptManager {

public:
    static BankruptManager* getInstance();
    
    
    Bankrupt getBankrupt();
    
private:
    BankruptManager();
    void init();
    static BankruptManager* _instance;
    
    int getTodayRequestTimes();
    void addTodayRequestTime();
};

