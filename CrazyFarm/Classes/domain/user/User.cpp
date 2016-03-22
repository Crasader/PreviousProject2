#include "domain/user/User.h"
#include "server/HttpMannger.h"
#include "domain/Newbie/NewbieMannger.h"
#include "server/Server.h"
#include "domain/game/GameManage.h"
User* User::_instance = NULL;

User::User(){
	this->init();
}

void User::init(){
	setSessionid("");
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

int User::getUserGender() {
	return UserDefault::getInstance()->getIntegerForKey(User::KEY_USER_GENDER,0);
}

void User::setUserGender(int gender) {
	UserDefault::getInstance()->setIntegerForKey(User::KEY_USER_GENDER, gender);
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






unsigned long  User::getCoins() {
    return	_coins;
}

int User::addCoins(int coins) {
	LogEventConsume::getInstance()->addEventCoin(coins);
	_coins += (unsigned long)coins;
	if (_coins<0)
	{
		_coins = 0;
	}
	return _coins;
}


 unsigned long User::getDiamonds() {
	return _diamond;
}

int User::addDiamonds(int diamonds) {
	LogEventConsume::getInstance()->addEventDiamond(diamonds);
	_diamond += (unsigned long)diamonds;
	if (_diamond < 0)
	{
		_diamond = 0;
	}



	if (GameManage::getInstance()->getGuiLayer())
	{
		//每次获得钻石同步一次信息
	auto difCoins = User::getInstance()->getCoins() - User::getInstance()->getLastCoins();
	auto difDiamonds = User::getInstance()->getDiamonds() - User::getInstance()->getLastDiamonds();
	auto difExp = User::getInstance()->getExp() - User::getInstance()->getLastExp();
	if (difExp < 0)
	{
		return _diamond;
	}
	User::getInstance()->setLastCoins(User::getInstance()->getCoins());
	User::getInstance()->setLastExp(User::getInstance()->getExp());
	User::getInstance()->setLastDiamonds(User::getInstance()->getDiamonds());


	Server::getInstance()->sendUserInfoChange(difCoins, difDiamonds, difExp);
	}

	





	return _diamond;
}

int User::getMaxTurrentLevel() {
	return _maxTurrentLv;
}

bool User::setMaxTurrentLevel(int maxTurrentLevel) {
	_maxTurrentLv = maxTurrentLevel;
	return true;
}





bool User::addExp(int exp) {
    if(exp > 0) {
        int currentLevel = this->getLevelData().levelId;
		_exp+=exp;
        if(this->getLevelData().levelId > currentLevel) {
            return true;
        }
    }
    return false;
}

LevelData User::getLevelData() {
    return ConfigExp::getInstance()->getLevelData(
            getExp() );
}

int User::getVipLevel() {
    int chargeMoney = getChargeMoney();
    return ConfigVipLevel::getInstance()->getLevel(chargeMoney);
}

bool User::addChargeMoney(int money) {
	_chargeMoney += money;
	return true;
}

int User::getChargeMoney() {
    return _chargeMoney;
}
void User::setChargeMoney(int money)
{
	_chargeMoney = money;
}


void User::resetInfo() {

    setUserID("guest");
	UserDefault::getInstance()->setStringForKey(User::KEY_USER_NAME, "guest");
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, 200);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_M_TURRENT, 1);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHARGE_MONEY, 0);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_LASTSIGNDAY, -1);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_SEQSIGNDAY, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHEST_LEVEL, 0);
	UserDefault::getInstance()->setBoolForKey(User::KEY_ISHAVEFIRSTPAY, false);
	UserDefault::getInstance()->setBoolForKey(User::KEY_ISHAVESETNAME,false);
	NewbieMannger::getInstance()->resetInfo();

}
void User::syncInfo()
{
	//auto sessionid =getSessionid();
	//auto coin =getCoins();
	//auto diomad =getDiamonds();
	//auto exp =getExp();
	//auto lv = getMaxTurrentLevel();
	//auto mo = getChargeMoney()*100;
	//auto count = getNobillityCount();
	//HttpMannger::getInstance()->HttpToPostRequestSyncInfo(sessionid, coin, diomad, exp, lv, mo, count);
}

int User::getNobillityCount()
{
	return NobilityManager::getInstance()->RemainingNobilityday();
}