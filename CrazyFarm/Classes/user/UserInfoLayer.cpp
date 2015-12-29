#include "user/UserInfoLayer.h"

bool UserInfoLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();




	return true;
}
