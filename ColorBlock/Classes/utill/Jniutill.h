#pragma once
#include "cocos2d.h"

using namespace cocos2d;


#define MSG_PAYBASE "msg_paybase"
enum 
{
	PAYEVENT_1 = 1,						//首次进入游戏
	PAYEVENT_2 = 2,						//玩家主动点击大厅抽奖图标
	PAYEVENT_3 = 3,						//玩家主动点击大厅红包图标
	PAYEVENT_4 = 4,						//无复活数量死亡
	PAYEVENT_5 = 5,						//有复活数量死亡
	PAYEVENT_6 = 6,						//游戏中点击锤子购买
	PAYEVENT_7 = 7,						//游戏中点击魔法棒购买
	PAYEVENT_8 = 8,						//等级达到三级
	PAYEVENT_9 = 9						//当长条形状下落到达屏幕最上方一格地方时
};







class Jniutill{
public:
	void showMoreGame();
	
	void quit();
	static Jniutill* getInstance();
	void requestEvent(int eventId);
	void getUipointByEventpoint(int eventid);
	const char* getJniPath();
	
private:
	std::string _jniPath;
	Jniutill();
	static Jniutill* _instance;
};

