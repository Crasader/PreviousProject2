#include "server/HttpMannger.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#include "domain/user/DeviceInfo.h"
#include "domain/logevent/LogEventMannger.h"
#include "domain/pay/Pay.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "domain/pay/WaitCircle.h"
#include "lobby/signlayer/SignMannger.h"
#include "lobby/LobbyScene.h"
#include "domain/bag/BagManager.h"
#include "lobby/bag/bagLayer.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/login/LoginMannger.h"
#include "domain/login/LoginScene.h"
#include "domain/loading/LoadingScene.h"
HttpMannger* HttpMannger::_instance = NULL;

HttpMannger::HttpMannger(){
    this->init();
}

void HttpMannger::init(){
}

HttpMannger* HttpMannger::getInstance(){
    if(_instance == NULL){
		_instance = new HttpMannger();
    }
    return _instance;
}


void HttpMannger::HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory)
{
	/*ShowWaiting(Req_Register);*/
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_REGISTER);
	auto requstData = String::createWithFormat("channel_id=%s&imei=%s&hd_type=%s&hd_factory=%s", channelId.c_str(),imei, hd_type, hd_factory);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForRegisterInfo, this));
}
void HttpMannger::onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response)
{
	FirstRegisterValue* value = new FirstRegisterValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["error_code"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			value->_sesssionid = doc["session_id"].GetString();
			auto &NBRewards = doc["login_rewards"];
			std::vector<RewardValue> rewards;
			rewards.push_back(RewardValue(1012,2));
			for (unsigned int i = 0; i < NBRewards.Size(); i++)
			{
				rewards.push_back(RewardValue(NBRewards[i]["item_id"].GetInt(), NBRewards[i]["nums"].GetInt()));

			}
			value->rewards = rewards;
			value->username = doc["user_name"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){NotificationCenter::getInstance()->postNotification("firstRegister", value); });
}


void HttpMannger::HttpToPostRequestRegisterForwardly(const char*nickname, const char* password, int gender, std::string channelId, const char* imei, const char* hd_type, const char* hd_factory)
{

	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_REGISTERFORWARDLY);
	auto requstData = String::createWithFormat("channel_id=%s&imei=%s&hd_type=%s&hd_factory=%s&nick_name=%s&password=%s&gender=%d", channelId.c_str(), imei, hd_type, hd_factory,nickname,password,gender);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForRegisterForwardly, this));

}
void HttpMannger::onHttpRequestCompletedForRegisterForwardly(HttpClient *sender, HttpResponse *response)
{
	RegisterValue* value = new RegisterValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			value->_sesssionid = doc["session_id"].GetString();
			auto &NBRewards = doc["login_rewards"];
			std::vector<RewardValue> rewards;
			rewards.push_back(RewardValue(1012, 2));
			for (unsigned int i = 0; i < NBRewards.Size(); i++)
			{
				rewards.push_back(RewardValue(NBRewards[i]["item_id"].GetInt(), NBRewards[i]["nums"].GetInt()));

			}
			value->rewards = rewards;
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}

	NotificationCenter::getInstance()->postNotification("register", value);
}








void HttpMannger::HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char*  hd_type, const char*  hd_factory)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_LOGIN);
	auto requstData = String::createWithFormat("channel_id=%s&user_name=%s&imei=%s&hd_type=%s&hd_factory=%s", channelId.c_str(),username.c_str(), imei, hd_type, hd_factory);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogInInfo, this));
}
void HttpMannger::onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response)
{
	LoginValue* value = new LoginValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			value->_sesssionid = doc["session_id"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}

	NotificationCenter::getInstance()->postNotification("login", value);
}



void HttpMannger::HttpToPostRequestLogInByName(const char*nickname, const char* password)
{
	/*ShowWaiting(Req_LoginByName);*/
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_BYNICKNAME);
	auto requstData = String::createWithFormat("nick_name=%s&password=%s", nickname,password);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogInByName, this));
}
void HttpMannger::onHttpRequestCompletedForLogInByName(HttpClient *sender, HttpResponse *response)
{
	//RemoveWaiting(Req_LoginByName);
	LoginValue* value = new LoginValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			value->_sesssionid = doc["session_id"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){NotificationCenter::getInstance()->postNotification("login", value); });


}


void HttpMannger::HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string  pay_point_desc, int price, int result, const char* orderid, int paytype)
{

	payRequest* quest = new payRequest();
	quest->pay_and_Event_version = pay_and_Event_version;
	quest->channel_id = channel_id;
	quest->sessionid = sessionid;
	quest->pay_point_id = pay_point_id;
	quest->pay_event_id = pay_event_id;
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PAY);
	auto requstData = String::createWithFormat("session_id=%s&pay_and_event_version=%d&pay_event_id=%d&pay_point_id=%d&channel_id=%s&price=%d&pay_type=%d&result=%d&order_id=%s&third_type=%d&pay_point_desc=%s",
		quest->sessionid.c_str(), quest->pay_and_Event_version, quest->pay_event_id, quest->pay_point_id, quest->channel_id.c_str(),price, paytype,result,orderid,quest->third_payType,pay_point_desc.c_str());

	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForBeforePay, this), quest);



}
void HttpMannger::onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response)
{
	if (!response||!response->isSucceed())
	{
		log("http back  before pay info falied");
		Pay::getInstance()->setPayState(UnDoing);
		ToolTipMannger::ShowPayTimeoutTip();
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back  before pay info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	
	if (result == 0)
	{
		const char* orderId = doc["order_id"].GetString();

		auto userdata = (payRequest*)response->getHttpRequest()->getUserData();
		userdata->orderID = orderId;
		if (userdata->third_payType==1)
		{
			userdata->wx_prepayid = doc["wx_prepayid"].GetString();
			userdata->wx_sign = doc["wx_sign"].GetString();
			userdata->wx_timestamp = doc["wx_timestamp"].GetString();
			userdata->wx_nonceStr = doc["wx_nonce_str"].GetString();
			log("pay http errormsg = %s", doc["errormsg"].GetString());
		}
	
		Pay::getInstance()->pay(userdata);
	}
	else
	{
		Pay::getInstance()->setPayState(UnDoing);
		ToolTipMannger::ShowPayTimeoutTip();

	}
}
void HttpMannger::HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int price,int result, const char* orderid, int paytype )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return;
#endif

	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PAY);
	auto requstData = String::createWithFormat("session_id=%s&pay_and_event_version=%d&pay_event_id=%d&pay_point_id=%d&channel_id=%s&price=%d&pay_type=%d&result=%d&order_id=%s",
		sessionid.c_str(), pay_and_Event_version, pay_event_id, pay_point_id, channel_id.c_str(),price, paytype, result, orderid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForAfterPay, this));
}

void HttpMannger::onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back afterpay info: %s", temp.c_str());
}
void HttpMannger::onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back syncinfo  info: %s", temp.c_str());
}

void HttpMannger::HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp, int maxTurretLevel, int PayRMB, int nobillityCount)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return;
#endif
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_SYNCINFO);
	auto requstData = String::createWithFormat("session_id=%s&coins=%d&diamonds=%d&exp=%d&turrent_level=%d&mo=%d&nobility_time=%d", sessionid.c_str(), coin, diamond, exp, maxTurretLevel, PayRMB, nobillityCount);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForSyncInfo, this));
}


void HttpMannger::onHttpRequestCompletedForBindName(HttpClient *sender, HttpResponse *response)
{
	SetNameValue*value = new SetNameValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (value->_errorcode!=0)
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}

	NotificationCenter::getInstance()->postNotification("setname", value);

	
}

void HttpMannger::HttpToPostRequestBindName(const char* nickname, int gender,const char* password)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_BIND);
	auto requstData = String::createWithFormat("session_id=%s&nick_name=%s&gender=%d&password=%s",User::getInstance()->getSessionid().c_str(), nickname, gender,password);

	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForBindName, this));

}


void HttpMannger::onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response)
{

	if (!response)
	{
		log("http back feedback info: %ld", response->getResponseCode());
		return;
	}
	if (!response->isSucceed())
	{
		log("http back feedback info: %s", response->getErrorBuffer());
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back feedback info: %s", temp.c_str());
}

void HttpMannger::HttpToPostRequestFeedback(const char* feedback)
{
	if (strlen(feedback)<= 3)
	{
		return;

	}
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_FEEDBACK);
	auto requstData = String::createWithFormat("session_id=%s&info=%s", sessionid.c_str(), feedback);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForFeedback, this));
}


void HttpMannger::HttpToPostRequestDemandEntry(std::string prepayid, int reqNum)
{
	auto orderid = Pay::getInstance()->getOrderIdByprepayid(prepayid);
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_DEMANDENTRY);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());

	prepayidAndReqNum* reqData = new prepayidAndReqNum();
	reqData->reqnum = reqNum;
	reqData->prepayid = prepayid;
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForDemandEntry, this), reqData);
}

void HttpMannger::onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	auto data = response->getHttpRequest()->getUserData();
	std::string *reqdata = (std::string*)data;
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back cancelorder info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{	
		Pay::getInstance()->payCallBack(1, "", Pay::getInstance()->getPrepayIdByOrderid(*reqdata));
		
	}
	
	delete reqdata;
	return;
}


void HttpMannger::HttpToPostRequestCancelOrder(std::string orderid)
{
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_CANCELORDER);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());

	std::string* reqData = new std::string(orderid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForCancelOrder, this), reqData);
}

void HttpMannger::onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		Pay::getInstance()->payCallBack(1, "failed", "");
		return;
	}
	auto data = response->getHttpRequest()->getUserData();
	prepayidAndReqNum *reqdata = (prepayidAndReqNum*)data;
	if (!response->isSucceed())
	{
		Pay::getInstance()->payCallBack(1, "failed", reqdata->prepayid);
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back logevent info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		Pay::getInstance()->payCallBack(result, doc["success"].GetString(), reqdata->prepayid);
	}
	else
	{
		if (reqdata->reqnum >= 3)
		{
			Pay::getInstance()->payCallBack(1, "failed", reqdata->prepayid);
		}
		else
		{
			WaitCircle::sendRequestWaitCirCle(reqdata->prepayid);
		}
	}

	delete reqdata;
}


void HttpMannger::HttpToPostRequestLogEvent(std::string jsonString,int type)
{
	int *userdata = new int();
	*userdata = type;
	
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_LOGEVENTFISH);
	auto requstData = String::createWithFormat("session_id=%s&data_str=%s&game_version=%d", sessionid.c_str(), jsonString.c_str(),DeviceInfo::getVesion());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogEventCommon, this),userdata);
}
void HttpMannger::onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		auto userdata = (int*)response->getHttpRequest()->getUserData();
		LogEventMannger::getInstance()->clearData(*userdata);
		delete userdata;
	}
}


void HttpMannger::HttpToPostRequestToGetUserInfo()//获取用户信息
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid=="")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PLAYERINFO);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetUserInfo, this));
}
void HttpMannger::onHttpRequestCompletedForGetUserInfo(HttpClient *sender, HttpResponse *response)
{
	UserInfoValue* value = new UserInfoValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back userinfo cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			auto &userinfo = doc["user_info"];
			value->_coins = userinfo["coins"].GetUint64();
			value->_exps = userinfo["exps"].GetInt();
			value->_diamonds = userinfo["diamonds"].GetUint64();
			value->_maxTurrentLv = userinfo["turrent_level"].GetInt();
			value->_chargemoney= userinfo["mr"].GetInt();
			value->_chestLevel = userinfo["chest_level"].GetInt();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_user_info");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


void HttpMannger::HttpToPostRequestToGetItemInfo(bool isOpenBag)
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_ITEMINFO);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	bool *_isopen = new bool(isOpenBag);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetItemInfo, this), _isopen);
}
void HttpMannger::onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back get user item info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		auto &item_lists = doc["item_lists"];
		for (unsigned int i = 0; i < item_lists.Size();i++)
		{
			BagManager::getInstance()->setItemNum(item_lists[i]["item_id"].GetInt(), item_lists[i]["nums"].GetInt());
		}
		bool isopen = *((bool*)(response->getHttpRequest()->getUserData()));
		if (isopen)
		{
			Director::getInstance()->replaceScene(BagLayer::createScene());
		}
		
	}

}
void HttpMannger::HttpToPostRequestToBuyItem(int itemid) //背包购买道具
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_BUYITEM);
	auto requstData = String::createWithFormat("session_id=%s&item_id=%d", sessionid.c_str(),itemid);
	int *data = new int(itemid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForBuyItem, this), data);
}
void HttpMannger::onHttpRequestCompletedForBuyItem(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back get user item info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		ToolTipMannger::ShowPaySuccessTip();
		int itemid = *((int*)response->getHttpRequest()->getUserData());
		BagManager::getInstance()->addreward(itemid, doc["buy_nums"].GetInt());
		User::getInstance()->addDiamonds(-doc["diamonds_price"].GetInt());

		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(888);
		((BagLayer*)layer)->gettableview()->reloadData();
	}
}




void HttpMannger::HttpToPostRequestCDKey(std::string cdkey) //背包购买道具
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_CDKEY);
	auto requstData = String::createWithFormat("session_id=%s&cdkey=%s", sessionid.c_str(), cdkey.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForCDKey, this));
}
void HttpMannger::onHttpRequestCompletedForCDKey(HttpClient *sender, HttpResponse *response)
{
	CDkeyValue* value = new CDkeyValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back get cdkey info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			auto& rewards = doc["reward_lists"];
			for (unsigned int i = 0; i < rewards.Size(); i++)
			{
				value->_rewards.push_back(RewardValue(rewards[i]["item_id"].GetInt(), rewards[i]["nums"].GetInt()));
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){NotificationCenter::getInstance()->postNotification("CDKEY", value); });
	
}

void HttpMannger::HttpToPostRequestOpenBox(int itemid) //背包购买道具
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_OPENBOX);
	auto requstData = String::createWithFormat("session_id=%s&item_id=%d", sessionid.c_str(), itemid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForOpenBox, this));
}
void HttpMannger::onHttpRequestCompletedForOpenBox(HttpClient *sender, HttpResponse *response)
{
	OpenBoxValue* value = new OpenBoxValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back openbox cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			value->_chestLevel = doc["chest_level"].GetInt();
			value->_reward_coins = doc["reward_coins"].GetInt();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){NotificationCenter::getInstance()->postNotification("openBox", value); });

}

void HttpMannger::HttpToPostRequestGetMissionList()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETMISSIONLIST);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetMissionList, this));
}
void HttpMannger::onHttpRequestCompletedForGetMissionList(HttpClient *sender, HttpResponse *response)
{
	MissionListValue* value = new MissionListValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back openbox cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{

			auto &task_lists = doc["task_lists"];
			for (unsigned int i = 0; i < task_lists.Size();i++)
			{
				auto &temp = task_lists[i];
				MissionListItem item;
				item.mission_id = temp["every_task_id"].GetInt();
				item.current_nums = temp["current_nums"].GetInt();
				item.isReceive = (temp["user_get"].GetInt() != 0);
				item.require_nums = temp["task_require_nums"].GetInt();
				item.to_page = temp["to_page"].GetInt();
				item.task_content = temp["task_content"].GetString();
			/*	item.tast_content_url_pic = temp[" content_pic_url"].GetString();*/
				auto &rewards = temp["reward_lists"];
				for (unsigned int j = 0; j < rewards.Size();j++)
				{
					item.rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
				}
				value->MissionItems.push_back(item);
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_mission_info");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


void HttpMannger::HttpToPostRequestGetMissionReward(int missionid)
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETMISSIONREWARD);
	auto requstData = String::createWithFormat("session_id=%s&every_task_id=%d", sessionid.c_str(),missionid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetMissionReward, this));
}
void HttpMannger::onHttpRequestCompletedForGetMissionReward(HttpClient *sender, HttpResponse *response)
{
	MissionRewardValue* value = new MissionRewardValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back openbox cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			auto &rewards = doc["reward_lists"];
			for (unsigned int j = 0; j < rewards.Size(); j++)
			{
				value->rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_mission_rewards");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


void HttpMannger::HttpToPostRequestToGetNobilityInfo()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETNOBILITYINFO);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetNobilityInfo, this));
}
void HttpMannger::onHttpRequestCompletedForGetNobilityInfo(HttpClient *sender, HttpResponse *response)
{
	while (1)
	{
		if (!response)
		{
			break;
		}
		if (!response->isSucceed())
		{
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back getNobittyday cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			break;
		}

		int result = doc["errorcode"].GetInt();
		if (result == 0)
		{
			User::getInstance()->setNobilityDay(doc["surplus_day"].GetInt());
		}
		
		break;
	}

}



void HttpMannger::HttpToPostRequestToGetNobilityReward()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETNOBILITYREWARD);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetNobilityReward, this));
}
void HttpMannger::onHttpRequestCompletedForGetNobilityReward(HttpClient *sender, HttpResponse *response)
{
	GuizuRewardValue* value = new GuizuRewardValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back openbox cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			auto &rewards = doc["reward_lists"];
			for (unsigned int j = 0; j < rewards.Size(); j++)
			{
				value->rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_guizu_rewards");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}




void HttpMannger::HttpToPostRequestToGetActiveInfo()
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETNACTIVEINFO);
	HttpClientUtill::getInstance()->onGetHttp(url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetActiveInfo, this));
}
void HttpMannger::onHttpRequestCompletedForGetActiveInfo(HttpClient *sender, HttpResponse *response)
{
	GuizuRewardValue* value = new GuizuRewardValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = TIMEOUT;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back openbox cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = TIMEOUT;
			break;
		}

		int result = doc["errorcode"].GetInt();
		value->_errorcode = result;
		if (result == 0)
		{
			auto &rewards = doc["reward_lists"];
			for (unsigned int j = 0; j < rewards.Size(); j++)
			{
				value->rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_guizu_rewards");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void HttpMannger::HttpToPostRequestToGetUrlImg(std::string url) //获取网络图片
{
	HttpClientUtill::getInstance()->onGetHttp(url.c_str(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetUrlImg, this));
}
void HttpMannger::onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response)
{
	std::vector<char> *buffer;
	while (1)
	{
		if (!response)
		{
			return;
		}
		if (!response->isSucceed())
		{
			return;
		}
		long statusCode = response->getResponseCode();

		buffer = response->getResponseData();
		break;
	}
	EventCustom event(response->getHttpRequest()->getUrl());
	event.setUserData(buffer);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

}