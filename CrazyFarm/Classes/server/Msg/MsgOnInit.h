#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;

class  Msg_onInit :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
private:
	int roomPos;//¾ø¶ÔÎ»ÖÃ
};

