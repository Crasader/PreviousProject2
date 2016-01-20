#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

struct payRequest
{
	std::string sessionid;
	int pay_and_Event_version;
	int pay_event_id;
	int pay_point_id; 
	std::string channel_id;
};
class HttpMannger {

public:
	static HttpMannger* getInstance();
	
	void HttpToPostRequestRegisterInfo(long imei, int hd_type, int hd_factory);//注册请求
	void HttpToPostRequestLogInInfo(std::string username,long imei, int hd_type, int hd_factory);//登录请求
	void HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result = 0, long int orderid = 0, int paytype = 0);//下单
	void HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result, long int orderid, int paytype=1 );//上传购买信息
	void HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp);//上传同步信息

	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response);
private:
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


