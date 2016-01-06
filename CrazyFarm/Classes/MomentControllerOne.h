#pragma once
#include "cocos2d.h"
#include "MomentController.h"
using namespace cocos2d;

class MomentControllerOne	:	public MomentController {

public:
	virtual void initControllerByJson(char* filename);
protected:
	std::vector<FishItemList> items;
	
};
