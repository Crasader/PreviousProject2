#include "MsgHelp.h"

Msg_Base*MsgHelp::getInfoByMsg(const char* msgId, const char* msgBody)
{
	Msg_Base* base = nullptr; 
	if (strcmp(msgId, "fire") == 0)
	{
	
	}
	if (strcmp(msgId, "conError") == 0)
	{
		//�Ͽ�����
	}
	if (strcmp(msgId, "init") == 0)
	{
		//�ͻ��˳�ʼ��
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		base = new Msg_onAdd();
		base->setBody(msgBody);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//ĳ���뿪
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		//��Ⱥ�·�

	}
	return base;
}
