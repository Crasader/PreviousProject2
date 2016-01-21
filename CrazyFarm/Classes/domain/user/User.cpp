#include "domain/user/User.h"
#include "server/HttpMannger.h"

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

std::string User::getUserId() {
	return UserDefault::getInstance()->getStringForKey(User::KEY_USER_ID, "guest");
}

void User::setUserID(std::string userId) {
	UserDefault::getInstance()->setStringForKey(User::KEY_USER_ID, userId);
}

std::string User::getUserName() {
    std::string name = UserDefault::getInstance()->getStringForKey(User::KEY_USER_NAME, "guest");
    if( name.compare("guest") == 0) {
        return getUserId();
    }
     log("guest != guest");
    return name;
}

bool User::setUserName(std::string newUserName) {
    std::string name = UserDefault::getInstance()->getStringForKey(User::KEY_USER_NAME, "guest");
    if(name == "guest") {
        UserDefault::getInstance()->setStringForKey(User::KEY_USER_NAME, newUserName);
        return true;
    }
    return false;
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

//int User::getNobillityCount() {
//	return UserDefault::getInstance()->getIntegerForKey(User::KEY_NOBILLITYS, 0);
//}
//
//int User::addNobillityCount(int counts) {
//	UserDefault::getInstance()->setIntegerForKey(User::KEY_NOBILLITYS,
//		this->getNobillityCount() + counts);
//	if (this->getNobillityCount() < 0) {
//		UserDefault::getInstance()->setIntegerForKey(User::KEY_NOBILLITYS, 0);
//	}
//	return this->getNobillityCount();
//}

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
        int currentLevel = this->getLevelData().levelId;
        UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP,
                UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) + exp);
        if(this->getLevelData().levelId > currentLevel) {
            return true;
        }
    }
    return false;
}

LevelData User::getLevelData() {
    return ConfigExp::getInstance()->getLevelData(
            UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) );
}

int User::getVipLevel() {
    int chargeMoney = getChargeMoney();
    return ConfigVipLevel::getInstance()->getLevel(chargeMoney);
}

bool User::addChargeMoney(int money) {
    if(money > 0) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_CHARGE_MONEY, getChargeMoney() + money);
        return true;
    }
    return false;
}

int User::getChargeMoney() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_CHARGE_MONEY, 0);
}

int User::getChestLevel() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_CHEST_LEVEL, 0);
}

bool User::setChestLevel(int chestLevel) {
    if(chestLevel > 0 && chestLevel > getChestLevel()) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_CHEST_LEVEL,chestLevel);
        return true;
    }
    return false;
    
}

void User::resetInfo() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    setUserID("guest");
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP, 200);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_M_TURRENT, 1);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHARGE_MONEY, 0);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_LASTSIGNDAY, -1);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_SEQSIGNDAY, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHEST_LEVEL, 0);
#endif
}
void User::syncInfo()
{
	auto sessionid =getSessionid();
	auto coin =getCoins();
	auto diomad =getDiamonds();
	auto exp =getExp();
	auto lv = getMaxTurrentLevel();
	auto mo = getChargeMoney();
	auto count = getNobillityCount();
	HttpMannger::getInstance()->HttpToPostRequestSyncInfo(sessionid, coin, diomad, exp, lv, mo, count);
}

int User::getNobillityCount()
{
	return NobilityManager::getInstance()->RemainingNobilityday();
}