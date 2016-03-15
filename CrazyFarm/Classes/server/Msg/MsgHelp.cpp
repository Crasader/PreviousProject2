#include "MsgHelp.h"
Msg_Base*MsgHelp::getInfoByMsg(const char* msgId, const char* msgBody)
{
	Msg_Base* base = nullptr; 
	if (strcmp(msgId, "conError") == 0)
	{
		//�Ͽ�����
		base = new Msg_ConError();
		base->setBody(msgBody);
		base->setMsgId(MsgConError);
		
	}
	if (strcmp(msgId, "init") == 0)
	{
		//�ͻ��˳�ʼ��
		base = new Msg_onInit();
		base->setBody(msgBody);
		base->setMsgId(MsgInit);
		
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		//ĳ�˽���
		base = new Msg_onAdd();
		base->setBody(msgBody);
		base->setMsgId(MsgOnAdd);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//ĳ���뿪
		base = new Msg_onLeave();
		base->setBody(msgBody);
		base->setMsgId(MsgOnLeave);
		
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		
		//��Ⱥ�·�
		base = new Msg_OnFishes();
		base->setBody(msgBody);
		base->setMsgId(MsgOnFishes);

	}
	return base;
}
