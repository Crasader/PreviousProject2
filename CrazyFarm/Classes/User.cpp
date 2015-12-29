#include "User.h"
#include "ConfigExp.h"

User* User::_instance = NULL;

User::User(){
	this->init();
}

void User::init(){
    // TODO : first use init user name and id
}

User* User::getInstance(){
	if(_instance == NULL){
		_instance = new User();
	}
	return _instance;
}

char* User::getUserId() {
    // TODO : wait impl
    return "kj_20151229";
}

char* User::getUserName() {
    // TODO : wait impl
    return "weason_hu";
}

int User::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_COINS, 0);
}

int User::addCoins(int coins) {
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS,
            this->getCoins() + coins);
    if(this->getCoins() < 0 ) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, 0);
    }
    return this->getCoins();
}

int User::getDiamonds() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_DIAMONDS, 0);
}

int User::addDiamonds(int diamonds) {
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS,
            this->getDiamonds() + diamonds);
    if(this->getDiamonds() < 0 ) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, 0);
    }
    return this->getDiamonds();
}

int User::getMaxTurrentLevel() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_M_TURRENT, 1);
}

bool User::setMaxTurrentLevel(int maxTurrentLevel) {
    if(maxTurrentLevel > 0 && maxTurrentLevel > this->getMaxTurrentLevel()) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_M_TURRENT, maxTurrentLevel);
        return true;
    }
    return false;
    
}


bool User::addExp(int exp) {
    if(exp > 0) {
        int currentLevel = this->getLevel();
        UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP,
                UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) + exp);
        if(this->getLevel() > currentLevel) {
            return true;
        }
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



