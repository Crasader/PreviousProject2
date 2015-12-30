#include "BagManager.h"

BagManager* BagManager::_instance = NULL;

BagManager::BagManager(){
    this->init();
}

void BagManager::init(){
    // TODO
}

BagManager* BagManager::getInstance(){
    if(_instance == NULL){
        _instance = new BagManager();
    }
    return _instance;
}

bool BagManager::changeItemCount(int itemId, int num) {
    int currentCount = getItemNum(itemId);
    auto key = String::createWithFormat("%s%d", BagManager::KEY_ITEMID_HEAD, itemId);
    UserDefault::getInstance()->setIntegerForKey(key->getCString(), currentCount+num);
    if(getItemNum(itemId) < 0) {
        UserDefault::getInstance()->setIntegerForKey(key->getCString(), 0);
    }
    if( currentCount == getItemNum(itemId) ) {
        return false;
    }
    return true;
    
}

int BagManager::getItemNum(int itemId) {
    auto key = String::createWithFormat("%s%d", BagManager::KEY_ITEMID_HEAD, itemId);
    return UserDefault::getInstance()->getIntegerForKey(key->getCString(), 0);
}

std::vector<BagItem> BagManager::getBagList() {
    std::vector<BagItem> items;
    for(int i=1001; i<=1005;i++) {  // TODO : 1005 need update by config
        int num = getItemNum(i);
        if(num > 0) {
            BagItem item;
            item.itemId = i;
            item.num = num;
            items.push_back(item);
        }
    }
    return items;
}

