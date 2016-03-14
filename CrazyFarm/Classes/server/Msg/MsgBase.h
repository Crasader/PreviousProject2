#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
using namespace cocos2d;

enum MsgId
{
	MsgConError = 0,	// 'conError' - connect error
	MsgInit,			// 'init' - client defined info ...
	MsgOnAdd,			// 'onAdd' - new user coming ...
	MsgOnLeave,		// 'onLeave' - user leave room ...
	MsgOnFishes		// 'onFishes' - broadcast fish info ...
};



class Msg_Base
{
public:
	virtual void setBody(const char* msgBody) = 0;
	CC_SYNTHESIZE(MsgId, msgId, MsgId);
};
