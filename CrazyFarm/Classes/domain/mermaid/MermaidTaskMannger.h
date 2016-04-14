#pragma once
#include "cocos2d.h"
#include "MaridTaskPlane.h"
using namespace cocos2d;

class MermaidTaskMannger {

public:
	static MermaidTaskMannger* getInstence();
	bool isSendInfoToServer(int fishid);
	void onSuccessTask(unsigned int coins);
private:
	MermaidTaskMannger();
	static MermaidTaskMannger*_instance;
	CC_SYNTHESIZE(maridTaskPlane*, _taskPlane, TaskPlane);
};

