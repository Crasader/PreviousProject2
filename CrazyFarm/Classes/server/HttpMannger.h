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
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, int hd_type, int hd_factory);//ע������
	void HttpToPostRequestLogInInfo(std::string channelId,std::string username,const char* imei, int hd_type, int hd_factory);//��¼����
	void HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result = 0, long int orderid = 0, int paytype = 0);//�µ�
	void HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int result, long int orderid, int paytype=1 );//�ϴ�������Ϣ
	void HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp,int maxTurretLevel,int PayRMB,int nobillityCount);//�ϴ�ͬ����Ϣ
	void HttpToPostRequestSetName(std::string sessionid,const  char* nickname, int gender);//�����ǳ�
	void HttpToPostRequestFeedback(std::string sessionid, const  char* feedback);//�û�����	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForSetName(HttpClient *sender, HttpResponse *response);

	//�������
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1��Ⱥ2�Ʋ�3������4������ת5����6����ʹ��7��̨����	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);
private:
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


