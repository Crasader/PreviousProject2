#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;


struct MsgUpdateTurrentInfo
{
	int requireDiamonds;
	int rewards;
	int turrent_level;

};




class  Msg_OnUpdateTurrent :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);	
	MsgUpdateTurrentInfo _info;
	int errorcode;
};

