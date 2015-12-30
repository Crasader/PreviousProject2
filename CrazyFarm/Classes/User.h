#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

#include "config/ConfigVipLevel.h"

using namespace cocos2d;

class User{
public:
	static User* getInstance();
    
    char* getUserId();
    char* getUserName();
    
    const char* KEY_COINS = "KEY_COINS";
    const char* KEY_DIAMONDS = "KEY_DIAMONDS";
    const char* KEY_EXP = "KEY_EXP";
    const char* KEY_M_TURRENT = "KEY_M_TURRENT";
    
    const char* KEY_CHARGE_MONEY = "KEY_CHARGE_MONEY";

	int addCoins(int coins);
	int getCoins();
    
	int addDiamonds(int diamond);
	int getDiamonds();
    
    int getMaxTurrentLevel();
    bool setMaxTurrentLevel(int maxTurrentLevel);

    int getVipLevel();
    
    bool addChargeMoney(int money);
    int getChargeMoney();
    
    /**
     * return true, level up!! else, return false.
     */
    bool addExp(int exp);
    int getLevel();
    char* getLevelDesc();

private:
	User();
	void init();
	static User* _instance;

};

#endif
