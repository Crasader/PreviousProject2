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