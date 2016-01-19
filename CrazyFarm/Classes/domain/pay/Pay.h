#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

class Pay {

public:
    static Pay* getInstance();
	void sendRequestBeforePay(/*int pay_event_vesion,int */);
	void sendRequestAftetPay();
private:
	void onHttpRequestCompletedBeforePay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response);
    Pay();
    void init();
    static Pay* _instance;
};

#endif
