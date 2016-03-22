#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;
#define URL_HEAD "http://106.75.135.78:1701"
#define URL_BASECONFIG  "/config/get/base"
#define URL_REGISTER  "/user/hello"
#define URL_LOGIN  "/user/login"
#define URL_PAY  "/mo/order/booking"
#define URL_CANCELORDER "/mo/order/cancel"
#define URL_SYNCINFO  "/player/info/sync/fortuneInfo"
#define URL_SETNAME  "/user/nickname"
#define URL_FEEDBACK "/help/feedback"
#define URL_LOGEVENTFISH "/statistics/data"
#define URL_DEMANDENTRY "/mr/order/result"
#define URL_BROKE "/bankrupt/broke"
#define URL_REBRITH "/bankrupt/rebirth"
#define URL_PLAYERINFO "/player/info/get"
#define URL_ITEMINFO "/player/info/bag/get/"
#define URL_BUYITEM "/player/info/bag/buy/"
struct setNameRequest
{
	const char* nickname;
	int gender;
};
class HttpMannger {

public:
	static HttpMannger* getInstance();
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//ע������
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char* hd_type, const char* hd_factory);//��¼����
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string pay_point_desc, int price, int result = 0, const char* orderid = "0", int paytype = 0);//�µ�
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int price,int result, const char* orderid, int paytype=1 );//�ϴ�������Ϣ
	void onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp,int maxTurretLevel,int PayRMB,int nobillityCount);//�ϴ�ͬ����Ϣ
	void onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestSetName(std::string sessionid,const  char* nickname, int gender);//�����ǳ�
	void onHttpRequestCompletedForSetName(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestFeedback(const  char* feedback);//�û�����	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestDemandEntry(std::string prepayid, int reqNum);//�û�֧������ѯ����	
	void onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCancelOrder(std::string orderid);//�رն�������	
	void onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetUserInfo(); //��ȡ�û���Ϣ
	void onHttpRequestCompletedForGetUserInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetItemInfo(); //��ȡ�û�������������
	void onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestToBuyItem(int itemid); //�����������
	void onHttpRequestCompletedForBuyItem(HttpClient *sender, HttpResponse *response);

	//�������
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1��Ⱥ2�Ʋ�3������4������ת5����6����ʹ��7��̨����	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);
private:
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


