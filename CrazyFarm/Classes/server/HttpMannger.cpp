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
	auto url = String::createWithFormat("%s%s", URL_HEAD_FIX, URL_REGISTER);
	auto requstData = String::createWithFormat("channel_id=%s&imei=%s&hd_type=%s&hd_factory=%s&game_version=%d", channelId.c_str(),imei, hd_type, hd_factory,DeviceInfo::getGameVersion());
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
		log("http back get login info: %s", temp.c_str());
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
			rewards.push_back(RewardValue(1012,2));
			for (unsigned int i = 0; i < NBRewards.Size(); i++)
			{
				rewards.push_back(RewardValue(NBRewards[i]["item_id"].GetInt(), NBRewards[i]["nums"].GetInt()));

			}
			value->rewards = rewards;
			value->username = doc["user_name"].GetString();
			auto str = String::createWithFormat("%s:%d", doc["app_address"].GetString(), doc["app_port"].GetInt());
			setCurUrl(str->getCString());

			setGameUrl(doc["game_address"].GetString());
			setGamePort(doc["game_port"].GetInt());
		}
		else if (result==310)
		{
			value->_downurl = doc["url"].GetString();
			value->_errormsg = doc["errormsg"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode,value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("firstRegister");
	}
	else
	{
		EventCustom event("firstRegister");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}


void HttpMannger::HttpToPostRequestRegisterForwardly(const char*nickname, const char* password, int gender, std::string channelId, const char* imei, const char* hd_type, const char* hd_factory)
{

	auto url = String::createWithFormat("%s%s", URL_HEAD_FIX, URL_REGISTERFORWARDLY);
	auto requstData = String::createWithFormat("channel_id=%s&imei=%s&hd_type=%s&hd_factory=%s&nick_name=%s&password=%s&gender=%d&game_version=%d", channelId.c_str(), imei, hd_type, hd_factory,nickname,password,gender,DeviceInfo::getGameVersion());
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
			auto str = String::createWithFormat("%s:%d", doc["app_address"].GetString(), doc["app_port"].GetInt());
			setCurUrl(str->getCString());

			setGameUrl(doc["game_address"].GetString());
			setGamePort(doc["game_port"].GetInt());

		}
		else if (result == 310)
		{
			value->_downurl = doc["url"].GetString();
			value->_errormsg = doc["errormsg"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("register");
	}
	else
	{
		EventCustom event("register");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}








void HttpMannger::HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char*  hd_type, const char*  hd_factory)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD_FIX, URL_LOGIN);
	auto requstData = String::createWithFormat("channel_id=%s&user_name=%s&imei=%s&hd_type=%s&hd_factory=%s&game_version=%d", channelId.c_str(),username.c_str(), imei, hd_type, hd_factory,DeviceInfo::getGameVersion());
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
			auto str = String::createWithFormat("%s:%d", doc["app_address"].GetString(), doc["app_port"].GetInt());
			setCurUrl(str->getCString());

			setGameUrl(doc["game_address"].GetString());
			setGamePort(doc["game_port"].GetInt());
		}
		else if (result == 310)
		{
			value->_downurl = doc["url"].GetString();
			value->_errormsg = doc["errormsg"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("login");
	}
	else
	{
		EventCustom event("login");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}



void HttpMannger::HttpToPostRequestLogInByName(const char*nickname, const char* password)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD_FIX, URL_BYNICKNAME);
	auto requstData = String::createWithFormat("nick_name=%s&password=%s&game_version=%d", nickname,password,DeviceInfo::getGameVersion());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogInByName, this));
}
void HttpMannger::onHttpRequestCompletedForLogInByName(HttpClient *sender, HttpResponse *response)
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
		log("http back get loginbynickname info: %s", temp.c_str());
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
			auto str = String::createWithFormat("%s:%d", doc["app_address"].GetString(), doc["app_port"].GetInt());
			setCurUrl(str->getCString());

			setGameUrl(doc["game_address"].GetString());
			setGamePort(doc["game_port"].GetInt());
		}
		else if (result == 310)
		{
			value->_downurl = doc["url"].GetString();
			value->_errormsg = doc["errormsg"].GetString();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("login");
	}
	else
	{
		EventCustom event("login");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}


void HttpMannger::HttpToPostRequestBeforePay(int paythirdtype,std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string  pay_point_desc, int price, int result, const char* orderid, int paytype)
{

	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PAY);
	auto requstData = String::createWithFormat("session_id=%s&pay_and_event_version=%d&pay_event_id=%d&pay_point_id=%d&channel_id=%s&price=%d&pay_type=%d&result=%d&order_id=%s&third_type=%d&pay_point_desc=%s",
		sessionid.c_str(), pay_and_Event_version, pay_event_id, pay_point_id, channel_id.c_str(), price, paytype, result, orderid, paythirdtype, pay_point_desc.c_str());

	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForBeforePay, this));



}
void HttpMannger::onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response)
{
	OverBookValue* value = new OverBookValue();
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
			const char* orderId = doc["order_id"].GetString();

			value->orderID = orderId;
			value->wx_prepayid = doc["wx_prepayid"].GetString();
			value->wx_sign = doc["wx_sign"].GetString();
			value->wx_timestamp = doc["wx_timestamp"].GetString();
			value->wx_nonceStr = doc["wx_nonce_str"].GetString();
			log("pay http errormsg = %s", doc["errormsg"].GetString());
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("Over_Book_Order");
	}
	else
	{
		EventCustom event("Over_Book_Order");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

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

	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("setname");
	}
	else
	{
		EventCustom event("setname");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	
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




void HttpMannger::onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response)
{
	return;
}


void HttpMannger::HttpToPostRequestCancelOrder(std::string orderid)
{
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_CANCELORDER);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForCancelOrder, this));
}
void HttpMannger::HttpToPostRequestDemandEntry(std::string prepayid, int reqNum)
{
	auto orderid = Pay::getInstance()->getOrderIdByprepayid(prepayid);
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_DEMANDENTRY);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());

	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForDemandEntry, this));
}
void HttpMannger::onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response)
{
	DemandOrderValue* value = new DemandOrderValue();
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
		log("http back DemandOrderValue cb  info: %s", temp.c_str());
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
			value->realprice = doc["realprice"].GetInt();
			auto &temp = doc["reward_lists"];
			for (unsigned int i = 0; i < temp.Size();i++)
			{
				value->rewards.push_back(RewardValue(temp[i]["item_id"].GetInt(), temp[i]["nums"].GetInt()));
			}
			value->_errormsg = "success";
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("DemandEntry");
	}
	else
	{
		EventCustom event("DemandEntry");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
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
			value->_coins = userinfo["coins"].GetInt64();
			value->_exps = userinfo["exps"].GetInt();
			value->_diamonds = userinfo["diamonds"].GetInt64();
			value->_maxTurrentLv = userinfo["turrent_level"].GetInt();
			value->_chargemoney= userinfo["mo"].GetInt();
			value->_chestLevel = userinfo["chest_level"].GetInt();
			value->mo_coins = userinfo["mo_coins"].GetInt();
			value->mo_first = userinfo["mo_first"].GetInt();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_user_info");
	}
	else
	{
		EventCustom event("get_user_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}


void HttpMannger::HttpToPostRequestToGetItemInfo()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_ITEMINFO);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetItemInfo, this));
}
void HttpMannger::onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response)
{
	BagItemValue* value = new BagItemValue();
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
		log("http back getiteminfo cb  info: %s", temp.c_str());
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
			auto &rewards = doc["item_lists"];
			for (unsigned int j = 0; j < rewards.Size(); j++)
			{
				value->itemLists.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
			}

		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_bagitem_info");
	}
	else
	{
		EventCustom event("get_bagitem_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
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

	BuyBagItemValue* value = new BuyBagItemValue();
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
			value->buyItemNum = doc["buy_nums"].GetInt();
			value->costDmNum = doc["diamonds_price"].GetInt();

		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("buyitem");
	}
	else
	{
		EventCustom event("buyitem");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}




void HttpMannger::HttpToPostRequestCDKey(std::string cdkey) 
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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("CDKEY");
	}
	else
	{
		EventCustom event("CDKEY");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("openBox");
	}
	else
	{
		EventCustom event("openBox");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}


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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_mission_info");
	}
	else
	{
		EventCustom event("get_mission_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_mission_rewards");
	}
	else
	{
		EventCustom event("get_mission_rewards");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_guizu_rewards");
	}
	else
	{
		EventCustom event("get_guizu_rewards");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

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
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("active");
	}
	else
	{
		EventCustom event("active");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}


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



void HttpMannger::HttpToPostRequestToGetAchieveInfo()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETACHIEVELIST);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForToGetAchieveInfo, this));
}
void HttpMannger::onHttpRequestCompletedForToGetAchieveInfo(HttpClient *sender, HttpResponse *response)
{
	AchieveListValue* value = new AchieveListValue();
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
		log("http back achieve cb  info: %s", temp.c_str());
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
			for (unsigned int i = 0; i < task_lists.Size(); i++)
			{
				auto &temp = task_lists[i];
				AchieveListItem item;
				item.mission_id = temp["achievement_task_id"].GetInt();
				item.current_nums = temp["current_nums"].GetInt();
				item.isReceive = (temp["user_get"].GetInt() != 0);
				item.require_nums = temp["task_require_nums"].GetInt();
				item.to_page = temp["to_page"].GetInt();
				item.task_content = temp["task_content"].GetString();
				item.tast_content_url_pic = temp["title_pic_url"].GetString();
				item.tast_icon_url_pic = temp["icon_pic_url"].GetString();
				item.current_level = temp["current_level"].GetInt();
				item.max_level = temp["max_level"].GetInt();
				auto &rewards = temp["reward_lists"];
				for (unsigned int j = 0; j < rewards.Size(); j++)
				{
					item.rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
				}
				
				value->AchieveItems.push_back(item);
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_achieve_info");
	}
	else
	{
		EventCustom event("get_achieve_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}


void HttpMannger::HttpToPostRequestGetAchieveReward(int missionid)
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETACHIEVEREWARD);
	auto requstData = String::createWithFormat("session_id=%s&achievement_task_id=%d", sessionid.c_str(), missionid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetAchieveReward, this));
}
void HttpMannger::onHttpRequestCompletedForGetAchieveReward(HttpClient *sender, HttpResponse *response)
{
	AchieveRewardValue* value = new AchieveRewardValue();
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
			auto &temp = doc["next_level"];
			if (temp.IsObject())
			{
				AchieveListItem item;
				item.mission_id = temp["achievement_task_id"].GetInt();
				item.current_nums = temp["current_nums"].GetInt();
				item.isReceive = (temp["user_get"].GetInt() != 0);
				item.require_nums = temp["task_require_nums"].GetInt();
				item.to_page = temp["to_page"].GetInt();
				item.task_content = temp["task_content"].GetString();
				item.tast_content_url_pic = temp["title_pic_url"].GetString();
				item.tast_icon_url_pic = temp["icon_pic_url"].GetString();
				item.current_level = temp["current_level"].GetInt();
				item.max_level = temp["max_level"].GetInt();
				auto &rewards = temp["reward_lists"];
				for (unsigned int j = 0; j < rewards.Size(); j++)
				{
					item.rewards.push_back(RewardValue(rewards[j]["item_id"].GetInt(), rewards[j]["nums"].GetInt()));
				}
				if (item.isReceive == true && item.current_level == item.max_level)
				{
					item.current_level = item.max_level + 1;
				}
				value->_new_task_item = item;
			}
			else
			{
				AchieveListItem item;
				item.tag = -1;
				value->_new_task_item = item;
			}
			
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_achieve_rewards");
	}
	else
	{
		EventCustom event("get_achieve_rewards");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}

void HttpMannger::HttpToPostRequestToGetRoomInfo()
{
	auto game_version = DeviceInfo::getGameVersion();

	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETROOMINFO);
	auto requstData = String::createWithFormat("game_version=%d", game_version);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForToGetRoomInfo, this));
}
void HttpMannger::onHttpRequestCompletedForToGetRoomInfo(HttpClient *sender, HttpResponse *response)
{
	RoomInfoValue* value = new RoomInfoValue();
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
		log("http back getroominfo cb  info: %s", temp.c_str());
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
			auto &room_lists = doc["room_lists"];
			for (unsigned int j = 0; j < room_lists.Size(); j++)
			{
				RoomItem item; 
				item.playerNum = room_lists[j]["player_nums"].GetInt();
				item.roomid = room_lists[j]["room_id"].GetInt();
				item.requireTurrentLv = room_lists[j]["require_turrent_level"].GetInt();
				value->_roomitems.push_back(item);
			}
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_room_info");
	}
	else
	{
		EventCustom event("get_room_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}

}


void HttpMannger::HttpToPostRequestToGetVipCoins()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETVIPCOINS);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForToGetVipCoins, this));
}
void HttpMannger::onHttpRequestCompletedForToGetVipCoins(HttpClient *sender, HttpResponse *response)
{
	GetVipCoinValue* value = new GetVipCoinValue();
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
		log("http back vipcoins cb  info: %s", temp.c_str());
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
			value->coins = doc["coins"].GetInt();
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_vip_coins");
	}
	else
	{
		EventCustom event("get_vip_coins");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}




void HttpMannger::HttpToPostRequestToChangeReward(int change_type,std::string phonenum)
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_CHANGEGFIT);
	auto requstData = String::createWithFormat("session_id=%s&&phone_nums=%s&change_type=%d", sessionid.c_str(), phonenum.c_str(), change_type);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForToChangeReward, this));
}
void HttpMannger::onHttpRequestCompletedForToChangeReward(HttpClient *sender, HttpResponse *response)
{
	changGiftValue* value = new changGiftValue();
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
		log("http back changegift cb  info: %s", temp.c_str());
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
			
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("change_gift");
	}
	else
	{
		EventCustom event("change_gift");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}

void HttpMannger::HttpToPostRequestToRecordGift()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid == "")
	{
		return;
	}
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_GETRECORDGFIT);
	auto requstData = String::createWithFormat("session_id=%s", sessionid.c_str());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForToRecordGift, this));
}
void HttpMannger::onHttpRequestCompletedForToRecordGift(HttpClient *sender, HttpResponse *response)
{
	RecordGiftValue* value = new RecordGiftValue();
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
		log("http back RecordGiftValue cb  info: %s", temp.c_str());
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
			auto &itemlist = doc["info_lists"];
			for (unsigned int i = 0; i < itemlist.Size();i++)
			{
				RecordGiftItem item;
				item.change_state = itemlist[i]["change_state"].GetString();
				item._date = itemlist[i]["date"].GetInt();
				item.reward_desc = itemlist[i]["reward_desc"].GetString();
				value->_items.push_back(item);
			}
		
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	if (checkIsRelogin(value->_errorcode, value->_errormsg))
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("record_gift_info");
	}
	else
	{
		EventCustom event("record_gift_info");
		event.setUserData(value);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}







bool HttpMannger::checkIsRelogin(int msgId, std::string msg)
{
	if (msgId == 311||msgId == 304)
	{
		ToolTipMannger::ShowReloginTip(msg);
		LoadingCircle::RemoveLoadingCircle();
		return true;
	}
	return false;
}