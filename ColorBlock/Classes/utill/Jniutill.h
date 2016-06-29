#pragma once
#include "cocos2d.h"

using namespace cocos2d;


#define MSG_PAYBASE "msg_paybase"
enum 
{
	PAYEVENT_1 = 1,						//�״ν�����Ϸ
	PAYEVENT_2 = 2,						//���������������齱ͼ��
	PAYEVENT_3 = 3,						//�����������������ͼ��
	PAYEVENT_4 = 4,						//�޸�����������
	PAYEVENT_5 = 5,						//�и�����������
	PAYEVENT_6 = 6,						//��Ϸ�е�����ӹ���
	PAYEVENT_7 = 7,						//��Ϸ�е��ħ��������
	PAYEVENT_8 = 8,						//�ȼ��ﵽ����
	PAYEVENT_9 = 9						//��������״���䵽����Ļ���Ϸ�һ��ط�ʱ
};







class Jniutill{
public:
	void showMoreGame();
	
	void quit();
	static Jniutill* getInstance();
	void requestEvent(int eventId);
	void getUipointByEventpoint(int eventid);
	const char* getJniPath();
	
private:
	std::string _jniPath;
	Jniutill();
	static Jniutill* _instance;
};

