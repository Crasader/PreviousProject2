#include "MenuScenePayHandler.h"
#include "Sqlite/DBManager.h"
#include "utill/Jniutill.h"
#include "cocos2d.h"
USING_NS_CC;
static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}

void  MenuScenePayHandler::dealRewardProp(int propId, int propNum){
	DBManager::GetInstance()->ChangeSkillNum(propId,  propNum);
}
void  MenuScenePayHandler::dealEventClose(int eventId){
	auto keyMsg = String::createWithFormat("%s%d", MSG_PAYBASE, eventId);
	bool *result = new bool(false);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(keyMsg->getCString(),result);
	CC_SAFE_DELETE(result);
}
void MenuScenePayHandler::dealEventSuccess(int eventId, int propIds[], int propNums[], int count){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventSuccess eventId=%d", eventId);
#endif
	for (int i = 0; i < count;i++)
	{
		CCLog("addprop propId=%d,propnum=%d", propIds[i], propNums[i]);
		dealRewardProp(propIds[i], propNums[i]);
	}


	auto keyMsg = String::createWithFormat("%s%d", MSG_PAYBASE, eventId);
	bool *result = new bool(true);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(keyMsg->getCString(), result);
	CC_SAFE_DELETE(result);
}


void MenuScenePayHandler::dealEventFail(int eventId){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventFail eventId=%d",eventId);
#endif
	auto keyMsg = String::createWithFormat("%s%d", MSG_PAYBASE, eventId);
	bool *result = new bool(false);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(keyMsg->getCString(), result);
	CC_SAFE_DELETE(result);
}
