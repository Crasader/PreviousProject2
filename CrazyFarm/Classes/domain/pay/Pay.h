#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

struct payData 
{
	int pay_event_vesion;
	int pay_type;
	int pay_event_id;
	int pay_point_id;
	int pay_result;
	int channel_id;
	long int order_id;
};
class Pay {

public:
    static Pay* getInstance();
	void sendRequestBeforePay(payData data);//�¼���+�Ʒѵ�汾�ţ��¼��㣬�Ʒѵ㣬����������ţ�������
	void sendRequestAftetPay(payData data);
private:
	void onHttpRequestCompletedBeforePay(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response);
    Pay();
    void init();
    static Pay* _instance;
};

#endif
