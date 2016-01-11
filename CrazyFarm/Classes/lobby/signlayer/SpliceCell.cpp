#include "SpliceCell.h"
SpliceCell* SpliceCell::create(std::vector<SignRewardItem> rewards)
{
	SpliceCell* bRet = new SpliceCell();
	if (bRet&&bRet->init(rewards))
	{
		bRet->autorelease();
		return bRet;
	}
	else
	{
		delete bRet;
		bRet = NULL;
		return NULL;
	}
}

bool SpliceCell::init(std::vector<SignRewardItem> rewards)
{
	Node::init();
	bool bRet = false;
	while (!bRet)
	{
		for (int i = 0; i < rewards.size();i++)
		 {
			 auto var = rewards[i];
			 auto cell = SignCell::create(var.propID, var.propNum);
			 cell->setPosition(0, (i - 1)*cell->getContentSize().height);
			 addChild(cell);
		 }
			

		scheduleUpdate();
		bRet = true;
	}
	return bRet;
}

void SpliceCell::update(float delta)
{
	if (nTumbleTime > 0){

		nTumbleTime--;

		//curValue += addValue;
		//if (curValue >= 250){//这个判断到尾 从头开始
		//	curValue = 0;
		//}
		//CCSprite * sprite1 = (CCSprite *)this->getChildByTag(10);
		//sprite1->setTextureRect(CCRectMake(0, curValue, 25, 28));

	}
}