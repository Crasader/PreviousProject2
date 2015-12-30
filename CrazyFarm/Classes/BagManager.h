#ifndef _BAGMANAGER_H_
#define _BAGMANAGER_H_
#include "cocos2d.h"
#include "BagItem.h"

using namespace cocos2d;

class BagManager {
public :
	static BagManager* getInstance();

    const char* KEY_ITEMID_HEAD = "KEY_ITEMID_HEAD_";
    
    bool changeItemCount(int itemId, int num);
    int getItemNum(int itemId);
    
    std::vector<BagItem> getBagList();
    
private :
	BagManager();
	void init();
	static BagManager* _instance;

};

#endif
