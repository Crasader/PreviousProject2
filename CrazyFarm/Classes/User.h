#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

using namespace cocos2d;

class User{
public:
	static User* getInstance();
    
    const char* KEY_COINS = "KEY_COINS";
    const char* KEY_DIAMONDS = "KEY_DIAMONDS";
    const char* KEY_EXP = "KEY_EXP";

	int addCoins(int coins);
	int getCoins();
    
	int addDiamonds(int diamond);
	int getDiamonds();

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
