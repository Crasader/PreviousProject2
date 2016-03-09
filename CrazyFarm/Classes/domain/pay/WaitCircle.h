#include "cocos2d.h"
using namespace cocos2d;


class WaitCircle :public Sprite {

public:

	static void ShowPayWaitCircle();
	static void RemovePayWaitCircle();
	static void sendRequestWaitCirCle();
	CREATE_FUNC(WaitCircle);
	void DemandEntry();
private:

	
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	bool init();
	float nNowTime = 0;
};

