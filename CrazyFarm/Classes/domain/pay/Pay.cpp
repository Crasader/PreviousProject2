#include "domain/pay/Pay.h"
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
void Pay::sendRequestBeforePay()
{

}
void Pay::sendRequestAftetPay()
{

}
void Pay::onHttpRequestCompletedBeforePay(HttpClient *sender, HttpResponse *response)
{

}
void Pay::onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response)
{

}