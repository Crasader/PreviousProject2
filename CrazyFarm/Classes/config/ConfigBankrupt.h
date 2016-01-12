#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct Bankrupt  {
    int coins;
    int wait_time;
};


class ConfigBankrupt {
    
public:
	ConfigBankrupt();
	static ConfigBankrupt* getInstance();
    
	bool LoadConfig();
    
    std::vector<Bankrupt> getBankrupts();
private:
	static ConfigBankrupt* _instance;
	
    std::vector<Bankrupt> bankrupts;
};

