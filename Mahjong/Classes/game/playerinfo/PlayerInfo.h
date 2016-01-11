#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class PlayerInfo
{
public:
	PlayerInfo();
	~PlayerInfo();
	CC_SYNTHESIZE(Point, pos, Position);
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(string, nickName, Nickname);
	CC_SYNTHESIZE(int, money, Money);
};
#endif