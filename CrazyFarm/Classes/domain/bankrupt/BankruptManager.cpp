#include "domain/bankrupt/BankruptManager.h"


BankruptManager* BankruptManager::_instance = NULL;

BankruptManager::BankruptManager(){
    this->init();
}


void BankruptManager::init(){
	setgetRewardNode(nullptr);
}

BankruptManager* BankruptManager::getInstance(){
    if(_instance == NULL){
        _instance = new BankruptManager();
    }
    return _instance;
}

Bankrupt BankruptManager::getBankrupt() {
    if( getTodayRequestTimes() < ConfigBankrupt::getInstance()->getBankrupts().size() ) {
        return ConfigBankrupt::getInstance()->getBankrupts().at( getTodayRequestTimes() );
    }else {
        Bankrupt bankrupt;
        bankrupt.coins = 0;
        bankrupt.wait_time = 0;
		return bankrupt;
    }
}
Bankrupt BankruptManager::getRobotBankrupt() {

		Bankrupt bankrupt;
		bankrupt.coins = rand()%2000;
		bankrupt.wait_time = rand()%60;
		return bankrupt;
}

int BankruptManager::getTodayRequestTimes() {

	return getDayCnt(BankruptData);
}

void BankruptManager::addTodayRequestTime()
{
	addDayCnt(BankruptData);
}


int  BankruptManager::XygGetToday()
{
	int day = 1900;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day += timeinfo->tm_year;
	day = day * 100 + timeinfo->tm_mon + 1;
	day = day * 100 + timeinfo->tm_mday;

	return day;
}


int BankruptManager::getDayCnt(const char* key)
{
	//保存格式为2015031202 20150312为年月日，02为使用次数
	int val = UserDefault::sharedUserDefault()->getIntegerForKey(key, 0);
	if (val <= 0)
	{
		return 0;
	}

	int day = XygGetToday();
	//不是今天
	if (val / 100 != day)
	{
		return 0;
	}
	else
	{
		return val % 100;
	}
}

void BankruptManager::addDayCnt(const char* key)
{
	int val = getDayCnt(key);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, XygGetToday() * 100 + val + 1);
	CCUserDefault::sharedUserDefault()->flush();
}