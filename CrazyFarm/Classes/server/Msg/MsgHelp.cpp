#include "MsgHelp.h"
Msg_Base*MsgHelp::getInfoByMsg(const char* msgId, const char* msgBody)
{
	Msg_Base* base = nullptr; 
	if (strcmp(msgId, "conError") == 0)
	{
		//断开连接
		base = new Msg_ConError();
		base->setBody(msgBody);
		base->setMsgId(MsgConError);
		
	}
	if (strcmp(msgId, "init") == 0)
	{
		//客户端初始化
		base = new Msg_onInit();
		base->setBody(msgBody);
		base->setMsgId(MsgInit);
		
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		//某人进来
		base = new Msg_onAdd();
		base->setBody(msgBody);
		base->setMsgId(MsgOnAdd);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//某人离开
		base = new Msg_onLeave();
		base->setBody(msgBody);
		base->setMsgId(MsgOnLeave);
		
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		
		//鱼群下发
		base = new Msg_OnFishes();
		base->setBody(msgBody);
		base->setMsgId(MsgOnFishes);

	}
	if (strcmp(msgId, "level_update") == 0)
	{
		//炮塔升级
		base = new Msg_OnUpdateTurrent();
		base->setBody(msgBody);
		base->setMsgId(MsgOnUpdateTurrent);

	}
	if (strcmp(msgId, "expUpdate") == 0)
	{
		//人物升级
		base = new Msg_OnExpUpdate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnExpUpdate);

	}
	if (strcmp(msgId, "useSkill") == 0)
	{
		//人物升级
		base = new Msg_UseSkill();
		base->setBody(msgBody);
		base->setMsgId(MsgUseSkill);

	}
	if (strcmp(msgId, "BonuspoolInfo") == 0)
	{
		//人物升级
		base = new Msg_OnGetBounsPool();
		base->setBody(msgBody);
		base->setMsgId(MsgOnGetBounsPool);

	}
	if (strcmp(msgId, "LuckDraw") == 0)
	{
		//人物升级
		base = new Msg_LuckDraw();
		base->setBody(msgBody);
		base->setMsgId(MsgLuckDraw);

	}
	if (strcmp(msgId, "magnate") == 0)
	{
		//人物升级
		base = new Msg_OnMagnate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMagnate);

	}
	return base;
}
