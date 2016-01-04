#ifndef __HEAD_PORTRAIT__
#define __HEAD_PORTRAIT__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class HeadPortrait
{
public:
	HeadPortrait();
	~HeadPortrait();
	CC_SYNTHESIZE(Point, pos, Position);
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(string, nickName, Nickname);
	CC_SYNTHESIZE(int, money, Money);
};
#endif