#include "domain/coinBox//CoinBox.h"
#include "utill/JniFunUtill.h"

CoinBox *CoinBox::_instance = NULL;

CoinBox::CoinBox(){
    this->init();
}

void CoinBox::init(){
}

CoinBox* CoinBox::getInstance(){
    if(_instance == NULL){
		_instance = new CoinBox();
    }
    return _instance;
}

void CoinBox::addCoinBox(int money)
{
	CoinBoxs.push_back(money);
}
int CoinBox::getPerCoinBox()
{
	auto endCoin = *CoinBoxs.end();
	CoinBoxs.pop_back();
	return endCoin;
}

BoxConfigInfo CoinBox::getBoxConfigInfoByItemID(int itemid)
{
	return ConfigBox::getInstance()->getBoxConfigInfoByItemId(itemid);
}

int CoinBox::useTimeByItemID(int itemid)
{
	auto str = String::createWithFormat("%s%d", USEITEM, itemid);
	return UserDefault::getInstance()->getIntegerForKey(str->getCString(), 0);
}

void CoinBox::addUseTimeByItemId(int itemid)
{
	auto str = String::createWithFormat("%s%d", USEITEM, itemid);
	UserDefault::getInstance()->setIntegerForKey(str->getCString(),UserDefault::getInstance()->getIntegerForKey(str->getCString()) + 1);
}