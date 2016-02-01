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
	long int orderID;
};


class Pay {

public:
    static Pay* getInstance();
	void Overbooking(int paypoint, int eventPoint);//�µ�
	
	void pay(payRequest*data, long int orderid);//����֧���������ͬƽ�?
	void payCallBack(int code, const char* msg);
private:

	PayPointInfo getInfoByPaypoint(int paypoint);
    Pay();
    void init();
    static Pay* _instance;
	payRequest* nowData;
	
};

#endif
