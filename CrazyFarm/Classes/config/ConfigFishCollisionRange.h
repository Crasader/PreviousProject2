#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include "utill/CCircle.h"
#include "utill/CMyrect.h"
USING_NS_CC;



class ConfigFishCollisionRange {
    
public:
	ConfigFishCollisionRange();
	static ConfigFishCollisionRange* getInstance();
    
	bool LoadConfig();

	std::vector<CFigure*>  getFishFigures(int uiId);



private:
	static ConfigFishCollisionRange* _instance;
	
	std::map<int, std::vector<CFigure*>> uiidToFigures;

};

