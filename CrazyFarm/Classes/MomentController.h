#pragma once
#include "cocos2d.h"
using namespace cocos2d;



struct  FishItemList
{

};
class MomentController {

public:
	virtual void initControllerByJson(char* filename) = 0;
protected:
	std::vector<FishItemList> items;
	
};
