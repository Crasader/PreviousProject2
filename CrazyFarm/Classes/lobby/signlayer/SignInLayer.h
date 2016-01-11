#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class SignInLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(SignInLayer);
	const char* KEY_LASTSIGNDAY = "KEY_LASTSIGNDAY";
	const char* KEY_SEQSIGNDAY = "KEY_SEQSIGNDAY";
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return false; };
private:
	int CalculateTheDayToSign();
	void gainRewardsCallback(Ref* psend);
	int nSeqSignDay = 0;
};


class SignCell : public Node
{
public:
	SignCell();
	virtual bool init(int day, int proptype, int propnum, int signtype);

	static SignCell* create(int day, int proptype, int propnum, int signtype);
	Sprite* bg;
	void SetBlind();

};

#endif