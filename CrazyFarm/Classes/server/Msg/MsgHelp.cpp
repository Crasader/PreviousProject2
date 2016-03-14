#include "MsgHelp.h"

Msg_Base*MsgHelp::getInfoByMsg(const char* msgId, const char* msgBody)
{
	Msg_Base* base = nullptr; 
	if (strcmp(msgId, "fire") == 0)
	{
	
	}
	if (strcmp(msgId, "conError") == 0)
	{
		//断开连接
	}
	if (strcmp(msgId, "init") == 0)
	{
		//客户端初始化
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		base = new Msg_onAdd();
		base->setBody(msgBody);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//某人离开
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		//鱼群下发

	}
	return base;
}
