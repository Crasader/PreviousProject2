#include "PxPayMannger.h"
#include "platform\android\jni\JniHelper.h"
#include "utill/Jniutill.h"
#include "UiToPayConfig.h"
#include "BasePayLayer.h"
#include "PayUiConfig.h"
PxPayMannger* PxPayMannger::_instance = 0;
PxPayMannger::PxPayMannger(){
}
PxPayMannger* PxPayMannger::getInstance(){
	if(_instance == 0){
		_instance = new PxPayMannger();
	}
	return _instance;
}

void PxPayMannger::requestEvent(int eventId){
	Jniutill::getInstance()->requestEvent(eventId);
}
void PxPayMannger::initConfig()
{
	UiToPayConfig::getInstance()->LoadConfig();
	PayUiConfig::getInstance()->LoadConfig();
}

int PxPayMannger::getUipointByEvent(int eventId)
{
	return 1;
}
void PxPayMannger::LaughPayLayer(int eventId, Node*parents, const std::function<void(EventCustom*)>& callback)
{
	int uipoint = getUipointByEvent(eventId);
	auto ui = PayUiConfig::getInstance()->getPayUiConfigByPoint(uipoint);
	auto layer = BasePayLayer::create(ui);
	layer->setEventId(eventId);
	layer->setPosition(0, 0);
	parents->addChild(layer, 35);

	auto msg = String::createWithFormat("%s%d", MSG_PAYBASE, eventId);
	EventListenerCustom* listener = EventListenerCustom::create(msg->getCString(), callback);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);


	log("laugh pay layer eventid = %d", eventId);
}

void PxPayMannger::cancelEvent(int eventId)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo methodInfo;
//	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/PayService");
//	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "pay", "(I)V");
//	jint pay_point = eventId;
//	//jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
//	if (isHave){
//		jobject jobj;
//		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, pay_point);
//	}
//#endif	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto msg = String::createWithFormat("%s%d", MSG_PAYBASE, eventId);
	EventCustom pevent(msg->getCString());
	bool *isPaySucess = new bool(false);
	pevent.setUserData(isPaySucess);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&pevent);
	CC_SAFE_DELETE(isPaySucess);
#endif	
}