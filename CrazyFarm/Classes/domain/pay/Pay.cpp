#include "domain/pay/Pay.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#define PAYPOSTREQUEST "http://114.119.39.150:1701/mo/order/booking"

Pay* Pay::_instance = NULL;

Pay::Pay(){
    this->init();
}

void Pay::init(){
}

Pay* Pay::getInstance(){
    if(_instance == NULL){
        _instance = new Pay();
    }
    return _instance;
}
void Pay::sendRequestBeforePay(payData data)
{
	std::vector<std::string> vecs;
	/*vecs.push_back(NewAtoI(data.pay_event_vesion));
	vecs.push_back(NewAtoI(data.pay_event_id));
	vecs.push_back(NewAtoI(data.pay_point_id));
	vecs.push_back(NewAtoI(data.pay_type));
	vecs.push_back(NewAtoI(data.pay_result));
	vecs.push_back(NewAtoI(data.channel_id));
	vecs.push_back(NewAtoI(data.order_id));*/
	vecs.push_back("pay_and_event_version=100100");
	vecs.push_back("pay_event_id=1&");
	vecs.push_back("pay_point_id=1&");
	vecs.push_back("pay_type=0&");
	vecs.push_back("result=0&");
	vecs.push_back("channel_id=10000&");
	auto s = String::createWithFormat("session_id=%s&", User::getInstance()->getSessionid().c_str());
	vecs.push_back(s->getCString());
	vecs.push_back("order_id=0");
	/*auto str = SpliceDataForPostHttp(NewAtoI(data.pay_event_vesion), NewAtoI(data.pay_event_id), NewAtoI(data.pay_point_id), NewAtoI(data.pay_type), NewAtoI(data.pay_result), NewAtoI(data.channel_id), NewAtoI(data.order_id));*/
	auto str = SpliceDataForPostHttp(vecs);
	HttpClientUtill::getInstance()->onPostHttp(str, PAYPOSTREQUEST, CC_CALLBACK_2(Pay::onHttpRequestCompletedBeforePay, this));

}
void Pay::sendRequestAftetPay(payData data)
{
	std::vector<std::string> vecs;
	/*vecs.push_back(NewAtoI(data.pay_event_vesion));
	vecs.push_back(NewAtoI(data.pay_event_id));
	vecs.push_back(NewAtoI(data.pay_point_id));
	vecs.push_back(NewAtoI(data.pay_type));
	vecs.push_back(NewAtoI(data.pay_result));
	vecs.push_back(NewAtoI(data.channel_id));
	vecs.push_back(NewAtoI(data.order_id));*/
	vecs.push_back("pay_and_event_version=100100");
	vecs.push_back("pay_event_id=1&");
	vecs.push_back("pay_point_id=1&");
	auto s = String::createWithFormat("session_id=%s&", User::getInstance()->getSessionid().c_str());
	vecs.push_back(s->getCString());
	vecs.push_back("pay_type=1&");
	auto str = String::createWithFormat("result=%d&", data.pay_result);
	vecs.push_back(str->getCString());
	vecs.push_back("channel_id=10000&");
	str = String::createWithFormat("order_id=%d&", data.order_id);
	vecs.push_back(str->getCString());
	/*auto str = SpliceDataForPostHttp(NewAtoI(data.pay_event_vesion), NewAtoI(data.pay_event_id), NewAtoI(data.pay_point_id), NewAtoI(data.pay_type), NewAtoI(data.pay_result), NewAtoI(data.channel_id), NewAtoI(data.order_id));*/
	auto strs = SpliceDataForPostHttp(vecs);
	HttpClientUtill::getInstance()->onPostHttp(strs, PAYPOSTREQUEST, CC_CALLBACK_2(Pay::onHttpRequestCompletedAfterPay, this));
}
void Pay::onHttpRequestCompletedBeforePay(HttpClient *sender, HttpResponse *response)
{
	payData data;
	data.pay_type = 1;
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		data.pay_result = -100;
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	data.order_id = doc["order_id"].GetInt();
	data.pay_result = doc["errorcode"].GetInt();
	data.channel_id = 10000;
	data.pay_event_id = 1000;
	data.pay_point_id = 1000;
	data.pay_event_vesion = 10001000;
	data.pay_type = 1;
	sendRequestAftetPay(data);
}
void Pay::onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
}