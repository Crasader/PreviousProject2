#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

#include "config/ConfigExp.h"
#include "config/ConfigVipLevel.h"

using namespace cocos2d;

class User{
public:
	static User* getInstance();
    
	std::string getUserId();
	void setUserID(std::string userId);


	std::string getSession_id();
	void setSession_id(std::string userId);

    char* getUserName();
    
    const char* KEY_COINS = "KEY_COINS";
    const char* KEY_DIAMONDS = "KEY_DIAMONDS";
    const char* KEY_EXP = "KEY_EXP";
    const char* KEY_M_TURRENT = "KEY_M_TURRENT";
	const char* KEY_USER_ID = "KEY_USER_ID";

    const char* KEY_CHARGE_MONEY = "KEY_CHARGE_MONEY";

	int addCoins(int coins);
	int getCoins();
    
	int addDiamonds(int diamond);
	int getDiamonds();
    
    int getMaxTurrentLevel();


	///TODO :需要改成addMaxTurrentLevel
    bool setMaxTurrentLevel(int maxTurrentLevel);

    int getVipLevel();
    
    bool addChargeMoney(int money);
    int getChargeMoney();
    
    /**
     * return true, level up!! else, return false.
     */
    bool addExp(int exp);
    
    LevelData getLevelData();
    
    void resetInfo();

private:
	User();
	void init();
	static User* _instance;

};

#endif
