#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Msg_Base
{
	virtual void setBody(const char* msgBody) = 0;

};

class  Msg_onAdd :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
private:
	std::string username;
	unsigned long coins;
	unsigned long diamonds;
	int turrent_level;
	int vip_level;
	int box_level;
};

class MsgHelp
{
public:
	static Msg_Base*getInfoByMsg(const char* msgId, const char* msgBody);
};