#include "BaseLayer.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"
bool BaseLayer::init()
{
	Layer::init();
	

	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);
	colorlayer->setVisible(false);
	setScale(0);
	runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), CallFunc::create([=]{colorlayer->setVisible(true); }), nullptr));


	//showRandonBubbleAni();
	

	return true;
}
void BaseLayer::showRandonBubbleAni()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto aniNode = Sprite::create();
	aniNode->setPosition(getRand() % ((int)(visibleSize.width-150))+75, getRand() % ((int)(visibleSize.height / 2))+30);
	addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniBubble"), RemoveSelf::create(1), nullptr));
	int k = getRand() % 30 + 50;
	float nexttime = ((float)k) / 10;
	runAction(Sequence::create(DelayTime::create(nexttime), CallFunc::create(CC_CALLBACK_0(BaseLayer::showRandonBubbleAni, this)), nullptr));
}