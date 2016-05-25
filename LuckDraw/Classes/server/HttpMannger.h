#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;
//����
//#define URL_HEAD_FIX "http://172.23.1.54:1701" 
//#define URL_HEAD "http://172.23.1.54:1701" 
//#define TCPIDURL "172.23.1.54" 
//��ʽ
#define TCPIDURL HttpMannger::getInstance()->getGameUrl().c_str()
#define URL_HEAD_FIX "http://106.75.141.82:1701"
#define URL_HEAD  HttpMannger::getInstance()->getCurUrl().c_str()




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
#define URL_ITEMINFO "/player/info/bag/get"
#define URL_BUYITEM "/player/info/bag/buy"
#define URL_BIND "/user/nickname/bind/"
#define URL_BYNICKNAME "/user/nickname/login"
#define URL_REGISTERFORWARDLY "/user/register"
#define URL_CDKEY "/cdkey/get"
#define URL_OPENBOX "/bag/chest/get"
#define URL_GETMISSIONLIST "/gametask/everyday"
#define URL_GETMISSIONREWARD "/gametask/everyday/getreward"
#define URL_GETACHIEVELIST "/gametask/achievement"
#define URL_GETACHIEVEREWARD "/gametask/achievement/getreward"
#define URL_GETNACTIVEINFO "/activity/config"
#define URL_GETNOBILITYINFO "/nobility/surplus"
#define URL_GETNOBILITYREWARD "/nobility/today/reward"
#define URL_MARQUEE  "/marquee/config"
#define URL_GETROOMINFO  "/room/roominfo"
#define URL_GETVIPCOINS  "/vip/getrewards"
#define URL_CHANGEGFIT  "/change/getrewards"
#define URL_GETRECORDGFIT "/change/getrecord"
#define URL_GETEMAILLIST "/mailbox/info/list/get"
#define URL_GETEMAILREWARDSINGLE "/mailbox/info/reward/get"
#define URL_GETEMAILREWARDALL "/mailbox/info/reward/get/all"
#define URL_GETEMAILREWARDPLURAL "/mailbox/info/list/get"
#define URL_GETSENDPRESENT "/present/give"
#define URL_GETREDBAGKEY "/hongbao/get"
#define URL_GETWXSHAREDINFO "/hongbao/shareinfo/get"

class HttpMannger {

public:
	static HttpMannger* getInstance();
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//ע������
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestRegisterForwardly(const char*nickname, const char* password, int gender,std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//ע������
	void onHttpRequestCompletedForRegisterForwardly(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char* hd_type, const char* hd_factory);//��¼����
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestLogInByName(const char*nickname, const char* password);//�˺ŵ�¼
	void onHttpRequestCompletedForLogInByName(HttpClient *sender, HttpResponse *response);

	



	void HttpToPostRequestBindName(const  char* nickname, int gender,const char* password);//���˺�
	void onHttpRequestCompletedForBindName(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestFeedback(const  char* feedback);//�û�����	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);

//----------------------------------------PAY BEGIN--------------------------------------------------
	void HttpToPostRequestBeforePay(int paythirdtype,std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string pay_point_desc, int price, int result = 0, const char* orderid = "0", int paytype = 0);//�µ�
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestDemandEntry(std::string prepayid, int reqNum);//�û�֧������ѯ����	
	void onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCancelOrder(std::string orderid);//�رն�������	
	void onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response);
//----------------------------------------PAY END--------------------------------------------------




	void HttpToPostRequestToGetUserInfo(); //��ȡ�û���Ϣ
	void onHttpRequestCompletedForGetUserInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetItemInfo(); //��ȡ�û�������������
	void onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestToBuyItem(int itemid); //�����������
	void onHttpRequestCompletedForBuyItem(HttpClient *sender, HttpResponse *response);

	//�������
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1��Ⱥ2�Ʋ�3������4������ת5����6����ʹ��7��̨����	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCDKey(std::string cdkey); //�һ���
	void onHttpRequestCompletedForCDKey(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestRedpackKey(std::string redPackKey); //�������
	void onHttpRequestCompletedForRedpackKey(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestOpenBox(int itemid); //������
	void onHttpRequestCompletedForOpenBox(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetMissionList(); //��ȡ�����б�
	void onHttpRequestCompletedForGetMissionList(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestGetMissionReward(int missionId); //��ȡ������
	void onHttpRequestCompletedForGetMissionReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetNobilityInfo(); //��ȡ�û���������
	void onHttpRequestCompletedForGetNobilityInfo(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetNobilityReward(); //��ȡ���影��
	void onHttpRequestCompletedForGetNobilityReward(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetActiveInfo(); //��ȡ���Ϣ
	void onHttpRequestCompletedForGetActiveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetUrlImg(std::string url); //��ȡ����ͼƬ
	void onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetAchieveInfo(); //��ȡ�ɾ��б�
	void onHttpRequestCompletedForToGetAchieveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetAchieveReward(int missionId); //��ȡ������
	void onHttpRequestCompletedForGetAchieveReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetRoomInfo(); //��ȡ������Ϣ
	void onHttpRequestCompletedForToGetRoomInfo(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetVipCoins(); //��ȡVIP����
	void onHttpRequestCompletedForToGetVipCoins(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToChangeReward(int change_type,std::string phonenum); //�һ���Ʒ  1,����;2 ��ʯ; 3�˵�
	void onHttpRequestCompletedForToChangeReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToRecordGift(); 
	void onHttpRequestCompletedForToRecordGift(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestGetEmailList(); //��ȡ�����б�
	void onHttpRequestCompletedForGetEmailList(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetEmailReward(int emailId); //�Ķ�������
	void onHttpRequestCompletedForGetEmailReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetEmailRewardByAll(); //һ����ȡ
	void onHttpRequestCompletedForGetEmailRewardByAll(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestSendPresent(int item_id,std::string nickname); //��������
	void onHttpRequestCompletedForSendPresent(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetWxSharedInfo(); //���΢�ŷ�����Ϣ
	void onHttpRequestCompletedForGetWxSharedInfo(HttpClient *sender, HttpResponse *response);
private:
	bool checkIsRelogin(int msgId,std::string msg);///�ỰIDʧЧ�����µ�¼

	CC_SYNTHESIZE(std::string, _curUrl, CurUrl);

	CC_SYNTHESIZE(std::string, _gameUrl, GameUrl);
	CC_SYNTHESIZE(int, _gamePort, GamePort);
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


