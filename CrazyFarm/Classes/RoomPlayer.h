#ifndef _ROOMPLAYER_H_
#define _ROOMPLAYER_H_
#include "cocos2d.h"

using namespace cocos2d;

class RoomPlayer{

public:
    RoomPlayer();
    /**
     * **3**************2**
     * *                  *
     * *                  *
     * **0**************1**
     *
     * postion like up view ... ...
     */
    CC_SYNTHESIZE(int, roomPosition, RoomPosition);
    
    static const int PLAYERSTATE_NEW = 0;
    static const int PLAYERSTATE_STANDUP = 1;
    static const int PLAYERSTATE_KEEP = 2;
    
    /**
     * 0 - new player add
     * 1 - player stand up
     * 2 - player keep on the desk
     */
    CC_SYNTHESIZE(int, playerState, PlayerState);
    
    CC_SYNTHESIZE(int, coins, Coins);
    CC_SYNTHESIZE(int, diamonds, Diamonds);
    
    CC_SYNTHESIZE(char*, userName, UserName);
    CC_SYNTHESIZE(int, level, Level);
    CC_SYNTHESIZE(int, turretLevel, TurretLevel);


private:
    
};

#endif
