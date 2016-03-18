#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "utill/FunUtil.h"
using namespace cocos2d;

enum MsgId
{
	MsgConError = 0,	// 'conError' - connect error
	MsgInit,			// 'init' - client defined info ...
	MsgOnAdd,			// 'onAdd' - new user coming ...
	MsgOnLeave,		// 'onLeave' - user leave room ...
	MsgOnFishes,	// 'onFishes' - broadcast fish info ...
	MsgOnUpdateTurrent		// 'MsgOnUpdateTurrent' - Update turrent ...
};


struct MsgFishInfo
{
	float time;
	int fish_ids;
	int fish_route;
};

struct MsgFishGourpInfo
{
	int group_type;//0:普通鱼群 1：鱼巢
	int sub_type; // 鱼巢几
	int seq;
	int seq_time;
	int randomSTC;//随机因子
	std::vector<MsgFishInfo> fishItems;
};

struct MsgFishesInfo
{
	int seq_id;
	int seq_interval;
	unsigned long seq_create_time;
	MsgFishGourpInfo fishGroupsItem;

};






class Msg_Base
{
public:
	virtual void setBody(const char* msgBody) = 0;
	CC_SYNTHESIZE(MsgId, msgId, MsgId);
};
