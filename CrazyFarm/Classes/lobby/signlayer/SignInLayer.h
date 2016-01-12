#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"
#include "SpliceCell.h"
USING_NS_CC;

class SignInLayer : public Layer
{
public:
	virtual bool init(int seqday);
	static SignInLayer * createLayer(int seqday);
	const char* KEY_LASTSIGNDAY = "KEY_LASTSIGNDAY";
	const char* KEY_SEQSIGNDAY = "KEY_SEQSIGNDAY";
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void updata(float dt);
private:
	void gainRewardsCallback(Ref* psend);
	SignRewardItem getRewardInVectorByProbability(std::vector<SignRewardItem>);
	int nSeqSignDay = 0;
	Vector<SpliceCell*> cells;
};






#endif