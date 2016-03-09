#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"
#include "PayPointConfig.h"
using namespace cocos2d;

struct payRequest
{
	std::string sessionid;
	int pay_and_Event_version;
	int pay_event_id;
	int pay_point_id;
	std::string channel_id;
	std::string orderID;
	int third_payType =1; //0:˹��֧��1:֧���� 2:΢��
	//΢�Ų���
	std::string wx_nonceStr;//����ַ���
	std::string wx_prepayid;//΢�Ŷ�����
	std::string wx_sign;//΢��ǩ��
	std::string wx_timestamp;//΢��ʱ���
};

struct prepayidAndReqNum
{
	std::string prepayid;
	int reqnum;
};


class Pay:public Node {

public:
    static Pay* getInstance();


	void Overbooking(int paypoint, int eventPoint,Node*paynode);
	
	void setIsPaying(bool ispay){ isPaying = ispay; };
	
	void jniCallBack(int code, const char*msg, const char* prepayid);
	

	void pay(payRequest*data);//��֧�����
	void payCallBack(int code, const char* msg, std::string prepayid);
	void update(float dt);
	void DemandEntry(int reqNum,std::string prePayid);//�����������

	std::string getOrderIdByprepayid(std::string prepayid);
private:
	
	void OverbookingActual(int paypoint, int eventPoint);//�µ�
	PayPointInfo getInfoByPaypoint(int paypoint);
    Pay();
    bool init();
    static Pay* _instance;
	std::map<std::string, payRequest*>  prepayidToPayRequest;


	bool isPaying = false;
	int payResult = -1;   //��ʼֵ-1,�ɹ�1��ʧ��2'
	
};

#endif
