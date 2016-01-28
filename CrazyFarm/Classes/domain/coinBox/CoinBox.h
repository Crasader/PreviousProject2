#pragma once
#include "cocos2d.h"
#include "config/ConfigBox.h"
using namespace cocos2d;

class CoinBox {

public:
	static CoinBox* getInstance();

	BoxConfigInfo getBoxConfigInfoByItemID(int itemid);
	int useTimeByItemID(int itemid);
	void addUseTimeByItemId(int itemid);
	void addCoinBox(int money);
	int getPerCoinBox();
private:
	const char* USEITEM = "USEITEM";
	CoinBox();
    void init();
	static CoinBox* _instance;
	std::vector<int> CoinBoxs;
};

