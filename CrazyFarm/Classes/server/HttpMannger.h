#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;


struct setNameRequest
{
	const char* nickname;
	int gender;
};
class HttpMannger {

public:
	static HttpMannger* getInstance();
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, int hd_type, int hd_factory);//注册请求
	void HttpToPostRequestLogInInfo(std::string channelId,std::string username,const char* imei, int hd_type, int hd_factory);//登录请求
	void HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result = 0, long int orderid = 0, int paytype = 0);//下单
	void HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result, long int orderid, int paytype=1 );//上传购买信息
	void HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp,int maxTurretLevel,int PayRMB,int nobillityCount);//上传同步信息
	void HttpToPostRequestSetName(std::string sessionid,const  char* nickname, int gender);//设置昵称
	void HttpToPostRequestFeedback(std::string sessionid, const  char* feedback);//用户反馈	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForSetName(HttpClient *sender, HttpResponse *response);

	//数据埋点
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1鱼群2破产3美人鱼4界面跳转5赠送6技能使用7炮台升级	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);
private:
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


