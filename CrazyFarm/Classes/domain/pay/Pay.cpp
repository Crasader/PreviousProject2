#include "domain/pay/Pay.h"
#include "utill/FunUtil.h"
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
	auto str = SpliceDataForPostHttp(NewAtoI(data.pay_event_vesion), NewAtoI(data.pay_event_id), NewAtoI(data.pay_point_id), NewAtoI(data.pay_type), NewAtoI(data.pay_result), NewAtoI(data.pay_type), NewAtoI(data.order_id));
	HttpClientUtill::getInstance()->onPostHttp(str, PAYPOSTREQUEST, CC_CALLBACK_2(Pay::onHttpRequestCompletedBeforePay, this));

}
void Pay::sendRequestAftetPay(payData data)
{
	auto str = SpliceDataForPostHttp(NewAtoI(data.pay_event_vesion), NewAtoI(data.pay_event_id), NewAtoI(data.pay_point_id), NewAtoI(data.pay_type), NewAtoI(data.pay_result), NewAtoI(data.pay_type), NewAtoI(data.order_id));
	HttpClientUtill::getInstance()->onPostHttp(str, PAYPOSTREQUEST, CC_CALLBACK_2(Pay::onHttpRequestCompletedAfterPay, this));
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
}
void Pay::onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response)
{

}