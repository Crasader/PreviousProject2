#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"
#include "PayPointConfig.h"
using namespace cocos2d;

struct payRequest
{
	std::string sessionid;
	int pay_and_Event_version;
	int pay_event_id;
	int pay_point_id;
	std::string channel_id;
	std::string orderID;
};


class Pay:public Node {

public:
    static Pay* getInstance();


	void Overbooking(int paypoint, int eventPoint,Node*paynode);
	
	
	void pay(payRequest*data,  const char* orderid);//起支付插件
	void payCallBack(int code,  const char* msg);
	void update(float dt);
private:
	
	void OverbookingActual(int paypoint, int eventPoint);//下单
	PayPointInfo getInfoByPaypoint(int paypoint);
    Pay();
    bool init();
    static Pay* _instance;
	payRequest* nowData;
	

	bool isPaying = false;
	int payResult = -1;   //初始值-1,成功1，失败2'
	
};

#endif
