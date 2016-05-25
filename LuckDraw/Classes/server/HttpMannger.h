#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;
//内网
//#define URL_HEAD_FIX "http://172.23.1.54:1701" 
//#define URL_HEAD "http://172.23.1.54:1701" 
//#define TCPIDURL "172.23.1.54" 
//正式
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
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//注册请求
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestRegisterForwardly(const char*nickname, const char* password, int gender,std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//注册请求
	void onHttpRequestCompletedForRegisterForwardly(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char* hd_type, const char* hd_factory);//登录请求
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestLogInByName(const char*nickname, const char* password);//账号登录
	void onHttpRequestCompletedForLogInByName(HttpClient *sender, HttpResponse *response);

	



	void HttpToPostRequestBindName(const  char* nickname, int gender,const char* password);//绑定账号
	void onHttpRequestCompletedForBindName(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestFeedback(const  char* feedback);//用户反馈	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);

//----------------------------------------PAY BEGIN--------------------------------------------------
	void HttpToPostRequestBeforePay(int paythirdtype,std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string pay_point_desc, int price, int result = 0, const char* orderid = "0", int paytype = 0);//下单
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestDemandEntry(std::string prepayid, int reqNum);//用户支付完后查询订单	
	void onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCancelOrder(std::string orderid);//关闭订单订单	
	void onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response);
//----------------------------------------PAY END--------------------------------------------------




	void HttpToPostRequestToGetUserInfo(); //获取用户信息
	void onHttpRequestCompletedForGetUserInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetItemInfo(); //获取用户背包道具数量
	void onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestToBuyItem(int itemid); //背包购买道具
	void onHttpRequestCompletedForBuyItem(HttpClient *sender, HttpResponse *response);

	//数据埋点
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1鱼群2破产3美人鱼4界面跳转5赠送6技能使用7炮台升级	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCDKey(std::string cdkey); //兑换码
	void onHttpRequestCompletedForCDKey(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestRedpackKey(std::string redPackKey); //红包口令
	void onHttpRequestCompletedForRedpackKey(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestOpenBox(int itemid); //开宝箱
	void onHttpRequestCompletedForOpenBox(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetMissionList(); //获取任务列表
	void onHttpRequestCompletedForGetMissionList(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestGetMissionReward(int missionId); //领取任务奖励
	void onHttpRequestCompletedForGetMissionReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetNobilityInfo(); //获取用户贵族天数
	void onHttpRequestCompletedForGetNobilityInfo(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetNobilityReward(); //领取贵族奖励
	void onHttpRequestCompletedForGetNobilityReward(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetActiveInfo(); //获取活动信息
	void onHttpRequestCompletedForGetActiveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetUrlImg(std::string url); //获取网络图片
	void onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetAchieveInfo(); //获取成就列表
	void onHttpRequestCompletedForToGetAchieveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetAchieveReward(int missionId); //领取任务奖励
	void onHttpRequestCompletedForGetAchieveReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetRoomInfo(); //获取房间信息
	void onHttpRequestCompletedForToGetRoomInfo(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetVipCoins(); //获取VIP补足
	void onHttpRequestCompletedForToGetVipCoins(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToChangeReward(int change_type,std::string phonenum); //兑换奖品  1,话费;2 钻石; 3核弹
	void onHttpRequestCompletedForToChangeReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToRecordGift(); 
	void onHttpRequestCompletedForToRecordGift(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestGetEmailList(); //获取邮箱列表
	void onHttpRequestCompletedForGetEmailList(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetEmailReward(int emailId); //阅读邮箱信
	void onHttpRequestCompletedForGetEmailReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetEmailRewardByAll(); //一键领取
	void onHttpRequestCompletedForGetEmailRewardByAll(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestSendPresent(int item_id,std::string nickname); //赠送礼物
	void onHttpRequestCompletedForSendPresent(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetWxSharedInfo(); //获得微信分享信息
	void onHttpRequestCompletedForGetWxSharedInfo(HttpClient *sender, HttpResponse *response);
private:
	bool checkIsRelogin(int msgId,std::string msg);///会话ID失效，重新登录

	CC_SYNTHESIZE(std::string, _curUrl, CurUrl);

	CC_SYNTHESIZE(std::string, _gameUrl, GameUrl);
	CC_SYNTHESIZE(int, _gamePort, GamePort);
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


