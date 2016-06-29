#pragma once
#include "cocos2d.h"
#include "utill/Jniutill.h"
using namespace cocos2d;
class PxPayMannger{
public:
	static PxPayMannger* getInstance();
	void requestEvent(int eventId);	
	void cancelEvent(int eventId);
	void initConfig();
	void LaughPayLayer(int eventId, Node* parents, const std::function<void(EventCustom*)>& callback);
private:
	PxPayMannger();
	int getUipointByEvent(int eventId);
	static PxPayMannger* _instance;
};

	