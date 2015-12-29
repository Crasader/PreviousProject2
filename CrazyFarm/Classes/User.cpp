#include "User.h"
#include "ConfigExp.h"

User* User::_instance = NULL;

User::User(){
	this->init();
}

void User::init(){

}

User* User::getInstance(){
	if(_instance == NULL){
		_instance = new User();
	}
	return _instance;
}

void User::addCoins(int coins) {
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, coins);
}

int User::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_COINS, 0);
}

void User::addDiamonds(int diamonds) {
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, diamonds);
}

int User::getDiamonds() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_DIAMONDS, 0);
}

bool User::addExp(int exp) {
    if(exp > 0) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP,
                UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) + exp);
        return true;
    }
    return false;
}

int User::getLevel() {
    return ConfigExp::getInstance()->getLevel(
            UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) );
}

char* User::getLevelDesc() {
    return ConfigExp::getInstance()->getLevelDesc( 
            UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) );
}



