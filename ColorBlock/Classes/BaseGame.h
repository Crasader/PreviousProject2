#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "MsgDefine.h"



class BaseGame : public Layer
{
protected:
	virtual void onExit();
	virtual void onEnter();
	
private:
	virtual void InitNotifications();                   //�����㲥֪ͨ
	virtual void removeNotifications();                 //�Ƴ��㲥֪ͨ
	virtual void onPause() = 0;
	virtual void onResum() = 0;
	virtual void onBackMainScene() = 0;
	virtual void onRebegin() = 0;
	virtual void onUseSkill(int skillid) = 0;
};

