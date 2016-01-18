#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"

using namespace cocos2d;

class CoinBox {

public:
	static CoinBox* getInstance();
	void addCoinBox(int money);
	int getPerCoinBox();
private:
	CoinBox();
    void init();
	static CoinBox* _instance;
	std::vector<int> CoinBoxs;
};

#endif
