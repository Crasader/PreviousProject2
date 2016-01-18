#include "domain/coinBox//CoinBox.h"


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