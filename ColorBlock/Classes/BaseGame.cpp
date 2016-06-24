#include "BaseGame.h"




void BaseGame::onExit()
{
	Layer::onExit();
	removeNotifications();
}
void BaseGame::onEnter()
{
	Layer::onEnter();
	InitNotifications();
}

void BaseGame::InitNotifications()
{
	//游戏暂停
	EventListenerCustom* listener = EventListenerCustom::create(MSG_PAUSE, [=](EventCustom* event){onPause(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//游戏恢复
	listener = EventListenerCustom::create(MSG_RESUME, [=](EventCustom* event){onResum(); CCLOG("onResume"); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//重新开始
	listener = EventListenerCustom::create(MSG_REBEGIN, [=](EventCustom* event){onRebegin(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//返回大厅
	listener = EventListenerCustom::create(MSG_BACKMAINSCENE, [=](EventCustom* event){onBackMainScene(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//使用技能
	listener = EventListenerCustom::create(MSG_USESKILL, [=](EventCustom* event){int *skillid =((int*)event->getUserData()); onUseSkill(*skillid); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}
void BaseGame::removeNotifications()
{
	getEventDispatcher()->removeCustomEventListeners(MSG_PAUSE);
	getEventDispatcher()->removeCustomEventListeners(MSG_RESUME);
	getEventDispatcher()->removeCustomEventListeners(MSG_REBEGIN);
	getEventDispatcher()->removeCustomEventListeners(MSG_BACKMAINSCENE);
	getEventDispatcher()->removeCustomEventListeners(MSG_USESKILL);
}
